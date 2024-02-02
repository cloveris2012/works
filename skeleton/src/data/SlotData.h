#ifndef Skel_SlotData_h
#define Skel_SlotData_h

#include "config/BlendMode.h"
#include "common/SkelObject.h"
#include "common/SkelString.h"
#include "common/Color.h"

namespace skel {
class BoneData;

class SK_API SlotData : public SkelObject {
	friend class SkeletonBinary;

	friend class SkeletonJson;

	friend class AttachmentTimeline;

	friend class ColorTimeline;

	friend class DeformTimeline;

	friend class DrawOrderTimeline;

	friend class EventTimeline;

	friend class IkConstraintTimeline;

	friend class PathConstraintMixTimeline;

	friend class PathConstraintPositionTimeline;

	friend class PathConstraintSpacingTimeline;

	friend class ScaleTimeline;

	friend class ShearTimeline;

	friend class TransformConstraintTimeline;

	friend class TranslateTimeline;

	friend class TwoColorTimeline;

public:
	SlotData(int index, const String &name, BoneData &boneData);

	int getIndex();

	const String &getName();

	BoneData &getBoneData();

	Color &getColor();

	Color &getDarkColor();

	bool hasDarkColor();

	void setHasDarkColor(bool inValue);

	/// May be empty.
	const String &getAttachmentName();

	void setAttachmentName(const String &inValue);

	BlendMode getBlendMode();

	void setBlendMode(BlendMode inValue);

	int _index;
	String _name;

private:

	BoneData &_boneData;
	Color _color;
	Color _darkColor;

	bool _hasDarkColor;
	String _attachmentName;
	BlendMode _blendMode;
};
}

#endif /* Skel_SlotData_h */
