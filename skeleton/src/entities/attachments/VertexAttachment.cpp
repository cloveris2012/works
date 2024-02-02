#include "VertexAttachment.h"

#include "../Slot.h"
#include "entities/Bone.h"
#include "../../Skeleton.h"

using namespace skel;

RTTI_IMPL(VertexAttachment, Attachment)

VertexAttachment::VertexAttachment(const String &name) : Attachment(name), _worldVerticesLength(0), _deformAttachment(this), _id(getNextID()) {
}

VertexAttachment::~VertexAttachment() {
}

void VertexAttachment::computeWorldVertices(Slot &slot, Vector<float> &worldVertices) {
	computeWorldVertices(slot, 0, _worldVerticesLength, worldVertices, 0);
}

void VertexAttachment::computeWorldVertices(Slot &slot, float *worldVertices) {
	computeWorldVertices(slot, 0, _worldVerticesLength, worldVertices, 0);
}

void VertexAttachment::computeWorldVertices(Slot &slot, size_t start, size_t count, Vector<float> &worldVertices, size_t offset, size_t stride) {
	computeWorldVertices(slot, start, count, worldVertices.buffer(), offset, stride);
}

void VertexAttachment::computeWorldVertices(Slot &slot, size_t start, size_t count, float *worldVertices, size_t offset, size_t stride) {
	count = offset + (count >> 1) * stride;
	Skeleton &skeleton = slot._bone._skeleton;
	Vector<float> *deformArray = &slot.getDeform();
	Vector<float> *vertices = &_vertices;
	Vector<size_t> &bones = _bones;
	if (bones.size() == 0) {
		if (deformArray->size() > 0) vertices = deformArray;

		Bone &bone = slot._bone;
		float x = bone._worldX;
		float y = bone._worldY;
		float a = bone._a, b = bone._b, c = bone._c, d = bone._d;
		for (size_t vv = start, w = offset; w < count; vv += 2, w += stride) {
			float vx = (*vertices)[vv];
			float vy = (*vertices)[vv + 1];
			worldVertices[w] = vx * a + vy * b + x;
			worldVertices[w + 1] = vx * c + vy * d + y;
		}
		return;
	}

	int v = 0, skip = 0;
	for (size_t i = 0; i < start; i += 2) {
		int n = bones[v];
		v += n + 1;
		skip += n;
	}

	Vector<Bone *> &skeletonBones = skeleton.getBones();
	if (deformArray->size() == 0) {
		for (size_t w = offset, b = skip * 3; w < count; w += stride) {
			float wx = 0, wy = 0;
			int n = bones[v++];
			n += v;
			for (; v < n; v++, b += 3) {
				Bone *boneP = skeletonBones[bones[v]];
				Bone &bone = *boneP;
				float vx = (*vertices)[b];
				float vy = (*vertices)[b + 1];
				float weight = (*vertices)[b + 2];
				wx += (vx * bone._a + vy * bone._b + bone._worldX) * weight;
				wy += (vx * bone._c + vy * bone._d + bone._worldY) * weight;
			}
			worldVertices[w] = wx;
			worldVertices[w + 1] = wy;
		}
	} else {
		for (size_t w = offset, b = skip * 3, f = skip << 1; w < count; w += stride) {
			float wx = 0, wy = 0;
			int n = bones[v++];
			n += v;
			for (; v < n; v++, b += 3, f += 2) {
				Bone *boneP = skeletonBones[bones[v]];
				Bone &bone = *boneP;
				float vx = (*vertices)[b] + (*deformArray)[f];
				float vy = (*vertices)[b + 1] + (*deformArray)[f + 1];
				float weight = (*vertices)[b + 2];
				wx += (vx * bone._a + vy * bone._b + bone._worldX) * weight;
				wy += (vx * bone._c + vy * bone._d + bone._worldY) * weight;
			}
			worldVertices[w] = wx;
			worldVertices[w + 1] = wy;
		}
	}
}

void VertexAttachment::computeVertices(Slot &slot, size_t start, size_t count, float *vertices, size_t offset, size_t stride) {
	Skeleton &skeleton = slot._bone._skeleton;
	Vector<float> *deformArray = &slot.getDeform();
	Vector<float> *selfVertices = &_vertices;
	Vector<size_t> &bones = _bones;
	if (bones.size() == 0) {
		if (deformArray->size() > 0) selfVertices = deformArray;

		Bone &bone = slot._bone;
		for (size_t vv = start, w = offset; w < count; vv += 2, w += stride) {
			float vx = (*selfVertices)[vv];
			float vy = (*selfVertices)[vv + 1];
			vertices[w] = vx;
			vertices[w + 1] = 0;
			vertices[w + 2] = 0;
			vertices[w + 3] = 0;

			vertices[w + 4] = vy;
			vertices[w + 5] = 0;
			vertices[w + 6] = 0;
			vertices[w + 7] = 0;

			// four index data
			vertices[w + 8] = bone.getIndex() + 0.1f;
			vertices[w + 9] = -1;
			vertices[w + 10] = -1;
			vertices[w + 11] = -1;
		}
		return;
	}

	int v = 0, skip = 0;
	for (size_t i = 0; i < start; i += 2) {
		int n = bones[v];
		v += n + 1;
		skip += n;
	}

	Vector<Bone *> &skeletonBones = skeleton.getBones();
	if (deformArray->size() == 0) {
		for (size_t w = offset, b = skip * 3; w < count; w += stride) {
			int n = bones[v++];
			n += v;
			int i = 0;
			for (; v < n; v++, b += 3, i++) {
				if (i < 4) {
					Bone *boneP = skeletonBones[bones[v]];
					Bone &bone = *boneP;
					float vx = (*selfVertices)[b];
					float vy = (*selfVertices)[b + 1];
					float weight = (*selfVertices)[b + 2];
					vertices[w + i] = vx;
					vertices[w + i + 4] = vy;
					vertices[w + i + 8] = bone.getIndex() + weight / 10.0f;
				}
			}
			for (; i < 4; ++i) {
				vertices[w + i] = 0;
				vertices[w + i + 4] = 0;
				vertices[w + i + 8] = -1;
			}
		}
	}
	else {
		for (size_t w = offset, b = skip * 3, f = skip << 1; w < count; w += stride) {
			float wx = 0, wy = 0;
			int n = bones[v++];
			n += v;
			int i = 0;
			for (; v < n; v++, b += 3, f += 2, i ++) {
				if (i < 4) {
					Bone *boneP = skeletonBones[bones[v]];
					Bone &bone = *boneP;
					float vx = (*selfVertices)[b] + (*deformArray)[f];
					float vy = (*selfVertices)[b + 1] + (*deformArray)[f + 1];
					float weight = (*selfVertices)[b + 2];
					vertices[w + i] = vx;
					vertices[w + i + 4] = vy;
					vertices[w + i + 8] = bone.getIndex() + weight / 10.0f;
				}
			}
			for (; i < 4; ++i) {
				vertices[w + i] = 0;
				vertices[w + i + 4] = 0;
				vertices[w + i + 8] = -1;
			}
		}
	}
}

int VertexAttachment::getId() {
	return _id;
}

Vector<size_t> &VertexAttachment::getBones() {
	return _bones;
}

Vector<float> &VertexAttachment::getVertices() {
	return _vertices;
}

size_t VertexAttachment::getWorldVerticesLength() {
	return _worldVerticesLength;
}

void VertexAttachment::setWorldVerticesLength(size_t inValue) {
	_worldVerticesLength = inValue;
}

VertexAttachment* VertexAttachment::getDeformAttachment() {
	return _deformAttachment;
}

void VertexAttachment::setDeformAttachment(VertexAttachment* attachment) {
	_deformAttachment = attachment;
}

int VertexAttachment::getNextID() {
	static int nextID = 0;

	return (nextID++ & 65535) << 11;
}

void VertexAttachment::copyTo(VertexAttachment* other) {
	other->_bones.clearAndAddAll(this->_bones);
	other->_vertices.clearAndAddAll(this->_vertices);
	other->_worldVerticesLength = this->_worldVerticesLength;
	other->_deformAttachment = this->_deformAttachment;
}
