#ifndef Skel_Slot_h
#define Skel_Slot_h

#include "common/Vector.h"
#include "common/Color.h"
#include "common/SkelObject.h"

namespace skel {
class SlotData;

class Bone;

class Skeleton;

class Attachment;

class SK_API Slot : public SkelObject {
	friend class VertexAttachment;

	friend class Skeleton;

	friend class SkeletonBounds;

	friend class SkeletonClipping;

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
	Slot(SlotData &data, Bone &bone);

	void setToSetupPose();

	SlotData &getData();

	Bone &getBone();

	Skeleton &getSkeleton();

	Color &getColor();

	Color &getDarkColor();

	bool hasDarkColor();

	/// May be NULL.
	Attachment *getAttachment();

	void setAttachment(Attachment *inValue);

	int getAttachmentState();

	void setAttachmentState(int state);

	float getAttachmentTime();

	void setAttachmentTime(float inValue);

	Vector<float> &getDeform();

private:
	SlotData &_data;
	Bone &_bone;
	Skeleton &_skeleton;
	Color _color;
	Color _darkColor;
	bool _hasDarkColor;
	Attachment *_attachment;
	int _attachmentState;
	float _attachmentTime;
	Vector<float> _deform;
};
}

#endif /* Skel_Slot_h */
