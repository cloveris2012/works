#include "DeformTimelineWrapper.h"
#include <iostream>
using namespace skel;

DeformTimelineWrapper::DeformTimelineWrapper(int frameCount) : DeformTimeline(frameCount) {
	_origionalOffsets.ensureCapacity(frameCount);
	_origionalVertices.ensureCapacity(frameCount);

	_origionalOffsets.setSize(frameCount, 0);

	for (int i = 0; i < frameCount; ++i) {
		Vector<float> vec;
		_origionalVertices.add(vec);
	}
}

Vector<Vector<float> > &DeformTimelineWrapper::getOrigionalVertices() {
	return _origionalVertices;
}

Vector<int> &DeformTimelineWrapper::getOrigionalOffsets() {
	return _origionalOffsets;
}

void DeformTimelineWrapper::setStepped(size_t frameIndex) {
	data.setStepped(frameIndex);
	DeformTimeline::setStepped(frameIndex);
}

void DeformTimelineWrapper::setCurve(size_t frameIndex, float cx1, float cy1, float cx2, float cy2) {
	data.setCurve(frameIndex, cx1, cy1, cx2, cy2);
	DeformTimeline::setCurve(frameIndex, cx1, cy1, cx2, cy2);
}

size_t DeformTimelineWrapper::getFrameCount() {
	return _frames.size();
}

LuaIntf::LuaRef DeformTimelineWrapper::getFrameData(lua_State* L, size_t frameIndex)
{

	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef ref(L, -1);
	LS.pop();

	data.fillCurveData(frameIndex, ref);

	ref.set<std::string, float>("time", _frames[frameIndex]);
	ref.set<std::string, int>("offset", _origionalOffsets[frameIndex]);

	LS.newTable();
	LuaIntf::LuaRef vRef(L, -1);
	LS.pop();

	auto &vertices = _origionalVertices[frameIndex];
	for (size_t i = 0; i < vertices.size(); i++) {
		vRef.set<size_t, float>(i + 1, vertices[i]);
	}
	ref.set<std::string, LuaIntf::LuaRef>("vertices", vRef);

	return ref;
}

int DeformTimelineWrapper::getSlotIndex() {
	return _slotIndex;
}

void DeformTimelineWrapper::setSlotIndex(int index) {
	_slotIndex = index;
}

std::string DeformTimelineWrapper::getAttachmentName() {
	return _attachment->getName().buffer();
}

void DeformTimelineWrapper::setToSetupPose(LuaIntf::LuaRef &data) {
	int frameCount = data.len();
	_frames.ensureCapacity(frameCount);
	_frames.setSize(frameCount, 0);
	_frameVertices.ensureCapacity(frameCount);
	for (int i = 0; i < frameCount; ++i) {
		Vector<float> vec;
		_frameVertices.add(vec);
	}

	bool weighted = _attachment->getBones().size() != 0;
	Vector<float> &verts = _attachment->getVertices();
	int deformLength = weighted ? verts.size() / 3 * 2 : verts.size();
	size_t frameIndex = 0;
	for (auto beg = data.begin(), end = data.end(); beg != end; ++beg, ++frameIndex) {
		float scale = 1;
		Vector<float> deformed;
		if (!beg.value().has("vertices")) {
			if (weighted) {
				deformed.setSize(deformLength, 0);
			}
			else {
				deformed.clearAndAddAll(_attachment->getVertices());
			}
		}
		else {
			int start = beg.value().get("offset").toValue<int>();
			deformed.setSize(deformLength, 0);
			int i = start;
			auto vertices = beg.value().get("vertices");
			for (auto beg2 = vertices.begin(), end2 = vertices.end(); beg2 != end2; ++beg2, ++i) {
				deformed[i] = beg2.value().toValue<float>() * scale;
			}
			if (!weighted) {
				Vector<float> &verticesAttachment = _attachment->getVertices();
				for (int v = 0; v < deformLength; ++v) {
					deformed[v] += verticesAttachment[v];
				}
			}
		}
		setFrame(frameIndex, beg.value().get("time").toValue<float>(), deformed);
	}
}