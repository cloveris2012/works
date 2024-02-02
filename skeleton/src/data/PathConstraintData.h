#ifndef Skel_PathConstraintData_h
#define Skel_PathConstraintData_h

#include "config/PositionMode.h"
#include "config/SpacingMode.h"
#include "config/RotateMode.h"
#include "common/Vector.h"
#include "common/SkelObject.h"
#include "common/SkelString.h"
#include "data/ConstraintData.h"

namespace skel {
	class BoneData;
	class SlotData;

	class SK_API PathConstraintData : public ConstraintData {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		friend class PathConstraint;
		friend class Skeleton;
		friend class PathConstraintMixTimeline;
		friend class PathConstraintPositionTimeline;
		friend class PathConstraintSpacingTimeline;

	public:
		explicit PathConstraintData(const String& name);

		Vector<BoneData*>& getBones();

		SlotData* getTarget();
		void setTarget(SlotData* inValue);

		PositionMode getPositionMode();
		void setPositionMode(PositionMode inValue);

		SpacingMode getSpacingMode();
		void setSpacingMode(SpacingMode inValue);

		RotateMode getRotateMode();
		void setRotateMode(RotateMode inValue);

		float getOffsetRotation();
		void setOffsetRotation(float inValue);

		float getPosition();
		void setPosition(float inValue);

		float getSpacing();
		void setSpacing(float inValue);

		float getRotateMix();
		void setRotateMix(float inValue);

		float getTranslateMix();
		void setTranslateMix(float inValue);

	private:
		Vector<BoneData*> _bones;
		SlotData* _target;
		PositionMode _positionMode;
		SpacingMode _spacingMode;
		RotateMode _rotateMode;
		float _offsetRotation;
		float _position, _spacing, _rotateMix, _translateMix;
	};
}

#endif /* Skel_PathConstraintData_h */
