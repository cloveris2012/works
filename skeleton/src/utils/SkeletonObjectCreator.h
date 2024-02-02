#ifndef Skel_SkeletonObjectCreator_h
#define Skel_SkeletonObjectCreator_h
#include "common/skel.h"

namespace skel {

	class SK_API SkeletonObjectCreator {
	public:
		SkeletonObjectCreator();

		virtual ~SkeletonObjectCreator();

		virtual SkeletonData *createSkeletonData();
		virtual BoneData *createBoneData(int index, const String &name, BoneData *parent, Json *map);
		virtual SlotData *createSlotData(int index, const String &name, BoneData &boneData);
		virtual IkConstraintData *createIkConstraintData(const String &name);
		virtual TransformConstraintData *createTransformConstraintData(const String &name);
		virtual PathConstraintData *createPathConstraintData(const String& name);
		virtual EventData *createEventData(const skel::String &name);
		virtual AnimationStateData *createAnimationStateData(SkeletonData *skeletonData);

		virtual SkeletonExtend *createSkeleton(SkeletonData *skeletonData);
		virtual AnimationStateExtend *createAnimationState(AnimationStateData *data);
		virtual Bone *createBone(BoneData &data, Skeleton &skeleton, Bone *parent);
		virtual Slot *createSlot(SlotData &data, Bone &bone);
		virtual IkConstraint *createIkConstraint(IkConstraintData &data, Skeleton &skeleton);
		virtual TransformConstraint *createTransformConstraint(TransformConstraintData &data, Skeleton &skeleton);
		virtual PathConstraint *createPathConstraint(PathConstraintData &data, Skeleton &skeleton);
		
		virtual Skin* createSkin(const String &name);
		virtual LinkedMesh* createLinkedMesh(MeshAttachment *mesh, const String &skin, size_t slotIndex, const String &parent, bool inheritDeform);
		virtual Event* createEvent(float time, const skel::EventData &data);

		virtual RegionAttachment *createRegionAttachment(const String &name);
		virtual MeshAttachment *createMeshAttachment(const String &name);
		virtual BoundingBoxAttachment *createBoundingBoxAttachment(const String &name);
		virtual PathAttachment *createPathAttachment(const String &name);
		virtual PointAttachment *createPointAttachment(const String &name);
		virtual ClippingAttachment *createClippingAttachment(const String &name);

		virtual Animation *createAnimation(const String &name, Vector<Timeline *> &timelines, float duration);
		virtual AttachmentTimeline *createAttachmentTimeline(int frameCount, Json *map);
		virtual ColorTimeline *createColorTimeline(int frameCount, Json *map);
		virtual TwoColorTimeline *createTwoColorTimeline(int frameCount, Json *map);
		virtual RotateTimeline *createRotateTimeline(int frameCount, Json *map);
		virtual ScaleTimeline *createScaleTimeline(int frameCount, Json *map);
		virtual TranslateTimeline *createTranslateTimeline(int frameCount, Json *map);
		virtual ShearTimeline *createShearTimeline(int frameCount, Json *map);
		virtual IkConstraintTimeline *createIkConstraintTimeline(int frameCount, Json *map);
		virtual TransformConstraintTimeline *createTransformConstraintTimeline(int frameCount, Json *map);
		virtual PathConstraintSpacingTimeline *createPathConstraintSpacingTimeline(int frameCount, Json *map);
		virtual PathConstraintPositionTimeline *createPathConstraintPositionTimeline(int frameCount, Json *map);
		virtual PathConstraintMixTimeline *createPathConstraintMixTimeline(int frameCount, Json *map);
		virtual DeformTimeline *createDeformTimeline(int frameCount, Json *map);
		virtual DrawOrderTimeline *createDrawOrderTimeline(int frameCount, Json *map);
		virtual EventTimeline *createEventTimeline(int frameCount, Json *map);
		
	};
}

#endif /* Skel_SkeletonObjectCreator_h */
