#ifndef Skel_TransformConstraintData_h
#define Skel_TransformConstraintData_h

#include "common/Vector.h"
#include "common/SkelObject.h"
#include "common/SkelString.h"
#include "data/ConstraintData.h"

namespace skel {
	class BoneData;

	class SK_API TransformConstraintData : public ConstraintData {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		friend class TransformConstraint;
		friend class Skeleton;
		friend class TransformConstraintTimeline;

	public:
		explicit TransformConstraintData(const String& name);

		Vector<BoneData*>& getBones();
		BoneData* getTarget();
		float getRotateMix();
		float getTranslateMix();
		float getScaleMix();
		float getShearMix();

		float getOffsetRotation();
		float getOffsetX();
		float getOffsetY();
		float getOffsetScaleX();
		float getOffsetScaleY();
		float getOffsetShearY();

		bool isRelative();
		bool isLocal();

	protected:
		Vector<BoneData*> _bones;
		BoneData* _target;
		float _rotateMix, _translateMix, _scaleMix, _shearMix;
		float _offsetRotation, _offsetX, _offsetY, _offsetScaleX, _offsetScaleY, _offsetShearY;
		bool _relative, _local;
	};
}

#endif /* Skel_TransformConstraintData_h */
