#ifndef Skel_IkConstraintData_h
#define Skel_IkConstraintData_h

#include "common/Vector.h"
#include "common/SkelObject.h"
#include "common/SkelString.h"
#include "data/ConstraintData.h"

namespace skel {
	class BoneData;

	class SK_API IkConstraintData : public ConstraintData {
		friend class SkeletonBinary;
		friend class SkeletonJson;
		friend class IkConstraint;
		friend class Skeleton;
		friend class IkConstraintTimeline;

	public:
		explicit IkConstraintData(const String& name);

		/// The bones that are constrained by this IK Constraint.
		Vector<BoneData*>& getBones();

		/// The bone that is the IK target.
		BoneData* getTarget();
		void setTarget(BoneData* inValue);

		/// Controls the bend direction of the IK bones, either 1 or -1.
		int getBendDirection();
		void setBendDirection(int inValue);

		bool getCompress();
		void setCompress(bool inValue);

		bool getStretch();
		void setStretch(bool inValue);

		bool getUniform();
		void setUniform(bool inValue);

		float getMix();
		void setMix(float inValue);

		float getSoftness();
		void setSoftness(float inValue);

	protected:
		Vector<BoneData*> _bones;
		BoneData* _target;
		int _bendDirection;
		bool _compress;
		bool _stretch;
		bool _uniform;
		float _mix;
		float _softness;
	};
}

#endif /* Skel_IkConstraintData_h */
