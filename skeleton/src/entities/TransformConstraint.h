#ifndef Skel_TransformConstraint_h
#define Skel_TransformConstraint_h

#include "common/Vector.h"
#include "../data/ConstraintData.h"

namespace skel {
	class TransformConstraintData;
	class Skeleton;
	class Bone;

	class SK_API TransformConstraint : public Updatable {
		friend class Skeleton;
		friend class TransformConstraintTimeline;

		RTTI_DECL

	public:
		TransformConstraint(TransformConstraintData& data, Skeleton& skeleton);

		void apply();

		virtual void update();

		virtual int getOrder();

		TransformConstraintData& getData();

		Vector<Bone*>& getBones();

		Bone* getTarget();
		void setTarget(Bone* inValue);

		float getRotateMix();
		void setRotateMix(float inValue);

		float getTranslateMix();
		void setTranslateMix(float inValue);

		float getScaleMix();
		void setScaleMix(float inValue);

		float getShearMix();
		void setShearMix(float inValue);

		bool isActive();

		void setActive(bool inValue);

	private:
		TransformConstraintData& _data;
		Vector<Bone*> _bones;
		Bone* _target;
		float _rotateMix, _translateMix, _scaleMix, _shearMix;
		bool _active;

		void applyAbsoluteWorld();

		void applyRelativeWorld();

		void applyAbsoluteLocal();

		void applyRelativeLocal();
	};
}

#endif /* Skel_TransformConstraint_h */
