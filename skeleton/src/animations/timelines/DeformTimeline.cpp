#include "DeformTimeline.h"

#include "../../Skeleton.h"
#include "../../entities/Event.h"

#include "../../entities/attachments/VertexAttachment.h"

#include "../Animation.h"
#include "../../entities/Bone.h"
#include "../../config/TimelineType.h"
#include "../../entities/Slot.h"
#include "../../data/SlotData.h"

using namespace skel;

RTTI_IMPL(DeformTimeline, CurveTimeline)

DeformTimeline::DeformTimeline(int frameCount) : CurveTimeline(frameCount), _slotIndex(0), _attachment(NULL) {
	_frames.ensureCapacity(frameCount);
	_frameVertices.ensureCapacity(frameCount);

	_frames.setSize(frameCount, 0);

	for (int i = 0; i < frameCount; ++i) {
		Vector<float> vec;
		_frameVertices.add(vec);
	}
}

void DeformTimeline::apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents, float alpha,
	MixBlend blend, MixDirection direction
) {
	SP_UNUSED(lastTime);
	SP_UNUSED(pEvents);
	SP_UNUSED(direction);

	Slot *slotP = skeleton._slots[_slotIndex];
	Slot &slot = *slotP;
	if (!slot._bone.isActive()) return;

	Attachment *slotAttachment = slot.getAttachment();
	if (slotAttachment == NULL || !slotAttachment->getRTTI().instanceOf(VertexAttachment::rtti)) {
		return;
	}

	VertexAttachment *attachment = static_cast<VertexAttachment *>(slotAttachment);
	if (attachment->_deformAttachment != _attachment) {
		return;
	}

	Vector<float> &deformArray = slot._deform;
	if (deformArray.size() == 0) {
		blend = MixBlend_Setup;
	}

	Vector< Vector<float> > &frameVertices = _frameVertices;
	size_t vertexCount = frameVertices[0].size();

	Vector<float> &frames = _frames;
	if (time < _frames[0]) {
		switch (blend) {
		case MixBlend_Setup:
			deformArray.clear();
			return;
		case MixBlend_First: {
			if (alpha == 1) {
				deformArray.clear();
				return;
			}
			deformArray.setSize(vertexCount, 0);
			Vector<float> &deformInner = deformArray;
			if (attachment->getBones().size() == 0) {
				// Unweighted vertex positions.
				Vector<float> &setupVertices = attachment->getVertices();
				for (size_t i = 0; i < vertexCount; i++)
					deformInner[i] += (setupVertices[i] - deformInner[i]) * alpha;
			} else {
				// Weighted deform offsets.
				alpha = 1 - alpha;
				for (size_t i = 0; i < vertexCount; i++)
					deformInner[i] *= alpha;
			}
		}
		case MixBlend_Replace:
		case MixBlend_Add:
			return;
		}
	}

	deformArray.setSize(vertexCount, 0);
	Vector<float> &deform = deformArray;

	if (time >= frames[frames.size() - 1]) { // Time is after last frame.
		Vector<float> &lastVertices = frameVertices[frames.size() - 1];
		if (alpha == 1) {
			if (blend == MixBlend_Add) {
				VertexAttachment *vertexAttachment = static_cast<VertexAttachment*>(slotAttachment);
				if (vertexAttachment->getBones().size() == 0) {
					// Unweighted vertex positions, no alpha.
					Vector<float> &setupVertices = vertexAttachment->getVertices();
					for (size_t i = 0; i < vertexCount; i++)
						deform[i] += lastVertices[i] - setupVertices[i];
				} else {
					// Weighted deform offsets, no alpha.
					for (size_t i = 0; i < vertexCount; i++)
						deform[i] += lastVertices[i];
				}
			} else {
				// Vertex positions or deform offsets, no alpha.
				memcpy(deform.buffer(), lastVertices.buffer(), vertexCount * sizeof(float));
			}
		} else {
			switch (blend) {
			case MixBlend_Setup: {
				VertexAttachment *vertexAttachment = static_cast<VertexAttachment *>(slotAttachment);
				if (vertexAttachment->getBones().size() == 0) {
					// Unweighted vertex positions, with alpha.
					Vector<float> &setupVertices = vertexAttachment->getVertices();
					for (size_t i = 0; i < vertexCount; i++) {
						float setup = setupVertices[i];
						deform[i] = setup + (lastVertices[i] - setup) * alpha;
					}
				} else {
					// Weighted deform offsets, with alpha.
					for (size_t i = 0; i < vertexCount; i++)
						deform[i] = lastVertices[i] * alpha;
				}
				break;
			}
			case MixBlend_First:
			case MixBlend_Replace:
				// Vertex positions or deform offsets, with alpha.
				for (size_t i = 0; i < vertexCount; i++)
					deform[i] += (lastVertices[i] - deform[i]) * alpha;
				break;
			case MixBlend_Add:
				VertexAttachment *vertexAttachment = static_cast<VertexAttachment *>(slotAttachment);
				if (vertexAttachment->getBones().size() == 0) {
					// Unweighted vertex positions, no alpha.
					Vector<float> &setupVertices = vertexAttachment->getVertices();
					for (size_t i = 0; i < vertexCount; i++)
						deform[i] += (lastVertices[i] - setupVertices[i]) * alpha;
				} else {
					// Weighted deform offsets, alpha.
					for (size_t i = 0; i < vertexCount; i++)
						deform[i] += lastVertices[i] * alpha;
				}
			}
		}
		return;
	}

	// Interpolate between the previous frame and the current frame.
	int frame = Animation::binarySearch(frames, time);
	Vector<float> &prevVertices = frameVertices[frame - 1];
	Vector<float> &nextVertices = frameVertices[frame];
	float frameTime = frames[frame];
	float percent = getCurvePercent(frame - 1, 1 - (time - frameTime) / (frames[frame - 1] - frameTime));

	if (alpha == 1) {
		if (blend == MixBlend_Add) {
			VertexAttachment *vertexAttachment = static_cast<VertexAttachment *>(slotAttachment);
			if (vertexAttachment->getBones().size() == 0) {
				// Unweighted vertex positions, no alpha.
				Vector<float> &setupVertices = vertexAttachment->getVertices();
				for (size_t i = 0; i < vertexCount; i++) {
					float prev = prevVertices[i];
					deform[i] += prev + (nextVertices[i] - prev) * percent - setupVertices[i];
				}
			} else {
				// Weighted deform offsets, no alpha.
				for (size_t i = 0; i < vertexCount; i++) {
					float prev = prevVertices[i];
					deform[i] += prev + (nextVertices[i] - prev) * percent;
				}
			}
		} else {
			// Vertex positions or deform offsets, no alpha.
			for (size_t i = 0; i < vertexCount; i++) {
				float prev = prevVertices[i];
				deform[i] = prev + (nextVertices[i] - prev) * percent;
			}
		}
	} else {
		switch (blend) {
		case MixBlend_Setup: {
			VertexAttachment *vertexAttachment = static_cast<VertexAttachment *>(slotAttachment);
			if (vertexAttachment->getBones().size() == 0) {
				// Unweighted vertex positions, with alpha.
				Vector<float> &setupVertices = vertexAttachment->getVertices();
				for (size_t i = 0; i < vertexCount; i++) {
					float prev = prevVertices[i], setup = setupVertices[i];
					deform[i] = setup + (prev + (nextVertices[i] - prev) * percent - setup) * alpha;
				}
			} else {
				// Weighted deform offsets, with alpha.
				for (size_t i = 0; i < vertexCount; i++) {
					float prev = prevVertices[i];
					deform[i] = (prev + (nextVertices[i] - prev) * percent) * alpha;
				}
			}
			break;
		}
		case MixBlend_First:
		case MixBlend_Replace:
			// Vertex positions or deform offsets, with alpha.
			for (size_t i = 0; i < vertexCount; i++) {
				float prev = prevVertices[i];
				deform[i] += (prev + (nextVertices[i] - prev) * percent - deform[i]) * alpha;
			}
			break;
		case MixBlend_Add:
			VertexAttachment *vertexAttachment = static_cast<VertexAttachment *>(slotAttachment);
			if (vertexAttachment->getBones().size() == 0) {
				// Unweighted vertex positions, with alpha.
				Vector<float> &setupVertices = vertexAttachment->getVertices();
				for (size_t i = 0; i < vertexCount; i++) {
					float prev = prevVertices[i];
					deform[i] += (prev + (nextVertices[i] - prev) * percent - setupVertices[i]) * alpha;
				}
			} else {
				// Weighted deform offsets, with alpha.
				for (size_t i = 0; i < vertexCount; i++) {
					float prev = prevVertices[i];
					deform[i] += (prev + (nextVertices[i] - prev) * percent) * alpha;
				}
			}
		}
	}
}

int DeformTimeline::getPropertyId() {
	assert(_attachment != NULL);
	return ((int) TimelineType_Deform << 24) + _attachment->_id + _slotIndex;
}

void DeformTimeline::setFrame(int frameIndex, float time, Vector<float> &vertices) {
	_frames[frameIndex] = time;
	_frameVertices[frameIndex].clear();
	_frameVertices[frameIndex].addAll(vertices);
}

int DeformTimeline::getSlotIndex() {
	return _slotIndex;
}

void DeformTimeline::setSlotIndex(int inValue) {
	_slotIndex = inValue;
}

Vector<float> &DeformTimeline::getFrames() {
	return _frames;
}

Vector<Vector<float> > &DeformTimeline::getVertices() {
	return _frameVertices;
}

VertexAttachment *DeformTimeline::getAttachment() {
	return _attachment;
}

void DeformTimeline::setAttachment(VertexAttachment *inValue) {
	_attachment = inValue;
}
