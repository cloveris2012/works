#include "ColorTimeline.h"

#include "../../Skeleton.h"
#include "../../entities/Event.h"
#include "../Animation.h"
#include "../../entities/Bone.h"
#include "../../config/TimelineType.h"
#include "../../entities/Slot.h"
#include "../../data/SlotData.h"

using namespace skel;

RTTI_IMPL(ColorTimeline, CurveTimeline)

const int ColorTimeline::ENTRIES = 5;
const int ColorTimeline::PREV_TIME = -5;
const int ColorTimeline::PREV_R = -4;
const int ColorTimeline::PREV_G = -3;
const int ColorTimeline::PREV_B = -2;
const int ColorTimeline::PREV_A = -1;
const int ColorTimeline::R = 1;
const int ColorTimeline::G = 2;
const int ColorTimeline::B = 3;
const int ColorTimeline::A = 4;

ColorTimeline::ColorTimeline(int frameCount) : CurveTimeline(frameCount), _slotIndex(0) {
	_frames.setSize(frameCount * ENTRIES, 0);
}

void ColorTimeline::apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents, float alpha,
	MixBlend blend, MixDirection direction
) {
	SP_UNUSED(lastTime);
	SP_UNUSED(pEvents);
	SP_UNUSED(direction);

	Slot *slotP = skeleton._slots[_slotIndex];
	Slot &slot = *slotP;
	if (!slot._bone.isActive()) return;
	if (time < _frames[0]) {
		switch (blend) {
		case MixBlend_Setup:
			slot._color.set(slot._data._color);
			return;
		case MixBlend_First: {
			Color &color = slot._color, setup = slot._data._color;
			color.add((setup.r - color.r) * alpha, (setup.g - color.g) * alpha, (setup.b - color.b) * alpha,
				(setup.a - color.a) * alpha);
		}
		default: ;
		}
		return;
	}

	float r, g, b, a;
	if (time >= _frames[_frames.size() - ENTRIES]) {
		// Time is after last frame.
		size_t i = _frames.size();
		r = _frames[i + PREV_R];
		g = _frames[i + PREV_G];
		b = _frames[i + PREV_B];
		a = _frames[i + PREV_A];
	} else {
		// Interpolate between the previous frame and the current frame.
		size_t frame = (size_t)Animation::binarySearch(_frames, time, ENTRIES);
		r = _frames[frame + PREV_R];
		g = _frames[frame + PREV_G];
		b = _frames[frame + PREV_B];
		a = _frames[frame + PREV_A];
		float frameTime = _frames[frame];
		float percent = getCurvePercent(frame / ENTRIES - 1, 1 - (time - frameTime) / (_frames[frame + PREV_TIME] - frameTime));

		r += (_frames[frame + R] - r) * percent;
		g += (_frames[frame + G] - g) * percent;
		b += (_frames[frame + B] - b) * percent;
		a += (_frames[frame + A] - a) * percent;
	}

	if (alpha == 1) {
		slot.getColor().set(r, g, b, a);
	} else {
		Color &color = slot.getColor();
		if (blend == MixBlend_Setup) color.set(slot.getData().getColor());
		color.add((r - color.r) * alpha, (g - color.g) * alpha, (b - color.b) * alpha, (a - color.a) * alpha);
	}
}

int ColorTimeline::getPropertyId() {
	return ((int) TimelineType_Color << 24) + _slotIndex;
}

void ColorTimeline::setFrame(int frameIndex, float time, float r, float g, float b, float a) {
	frameIndex *= ENTRIES;
	_frames[frameIndex] = time;
	_frames[frameIndex + R] = r;
	_frames[frameIndex + G] = g;
	_frames[frameIndex + B] = b;
	_frames[frameIndex + A] = a;
}

int ColorTimeline::getSlotIndex() {
	return _slotIndex;
}

void ColorTimeline::setSlotIndex(int inValue) {
	_slotIndex = inValue;
}

Vector<float> &ColorTimeline::getFrames() {
	return _frames;
}
