#ifndef Skel_SkeletonWrapperCreator_h
#define Skel_SkeletonWrapperCreator_h

#include "SkeletonObjectCreator.h"

namespace skel {

	class SK_API SkeletonWrapperCreator : public SkeletonObjectCreator {
	public:
		SkeletonWrapperCreator();

		~SkeletonWrapperCreator();

		SkeletonData *createSkeletonData() override;
		BoneData *createBoneData(int index, const String &name, BoneData *parent, Json *map) override;
		SlotData *createSlotData(int index, const String &name, BoneData &boneData) override;
		EventData *createEventData(const skel::String &name) override;

		IkConstraintData *createIkConstraintData(const String &name) override;
		TransformConstraintData *createTransformConstraintData(const String &name) override;
		PathConstraintData *createPathConstraintData(const String& name) override;
		//EventData *createEventData(const skel::String &name) override;
		AnimationStateData *createAnimationStateData(SkeletonData *skeletonData)override;

		SkeletonExtend *createSkeleton(SkeletonData *skeletonData) override;
		AnimationStateExtend *createAnimationState(AnimationStateData *data) override;
		Bone *createBone(BoneData &data, Skeleton &skeleton, Bone *parent) override;
		Slot *createSlot(SlotData &data, Bone &bone) override;

		RegionAttachment *createRegionAttachment(const String &name) override;
		MeshAttachment *createMeshAttachment(const String &name) override;

		Skin* createSkin(const String &name) override;

		Animation *createAnimation(const String &name, Vector<Timeline *> &timelines, float duration) override;

		AttachmentTimeline *createAttachmentTimeline(int frameCount, Json *map) override;
		ColorTimeline *createColorTimeline(int frameCount, Json *map) override;
		TwoColorTimeline *createTwoColorTimeline(int frameCount, Json *map) override;
		RotateTimeline *createRotateTimeline(int frameCount, Json *map) override;
		ScaleTimeline *createScaleTimeline(int frameCount, Json *map) override;
		TranslateTimeline *createTranslateTimeline(int frameCount, Json *map) override;
		ShearTimeline *createShearTimeline(int frameCount, Json *map) override;
		IkConstraintTimeline *createIkConstraintTimeline(int frameCount, Json *map) override;
		TransformConstraintTimeline *createTransformConstraintTimeline(int frameCount, Json *map) override;
		PathConstraintSpacingTimeline *createPathConstraintSpacingTimeline(int frameCount, Json *map) override;
		PathConstraintPositionTimeline *createPathConstraintPositionTimeline(int frameCount, Json *map) override;
		PathConstraintMixTimeline *createPathConstraintMixTimeline(int frameCount, Json *map) override;
		DeformTimeline *createDeformTimeline(int frameCount, Json *map) override;
		DrawOrderTimeline *createDrawOrderTimeline(int frameCount, Json *map) override;
		EventTimeline *createEventTimeline(int frameCount, Json *map) override;
	};
}

#endif /* Skel_SkeletonWrapperCreator_h */
