#ifndef Skel_IkConstraint_h
#define Skel_IkConstraint_h

#include "common/Vector.h"
#include "../data/ConstraintData.h"

namespace skel {
class IkConstraintData;

class Skeleton;

class Bone;

class SK_API IkConstraint : public Updatable {
	friend class Skeleton;

	friend class IkConstraintTimeline;

RTTI_DECL

public:
	/// Adjusts the bone rotation so the tip is as close to the target position as possible. The target is specified
	/// in the world coordinate system.
	static void apply(Bone &bone, float targetX, float targetY, bool compress, bool stretch, bool uniform, float alpha);

	/// Adjusts the parent and child bone rotations so the tip of the child is as close to the target position as
	/// possible. The target is specified in the world coordinate system.
	/// @param child A direct descendant of the parent bone.
	static void apply(Bone &parent, Bone &child, float targetX, float targetY, int bendDir, bool stretch, float softness, float alpha);

	IkConstraint(IkConstraintData &data, Skeleton &skeleton);

	/// Applies the constraint to the constrained bones.
	void apply();

	virtual void update();

	virtual int getOrder();

	IkConstraintData &getData();

	Vector<Bone *> &getBones();

	Bone *getTarget();

	void setTarget(Bone *inValue);

	int getBendDirection();

	void setBendDirection(int inValue);

	bool getCompress();

	void setCompress(bool inValue);

	bool getStretch();

	void setStretch(bool inValue);

	float getMix();

	void setMix(float inValue);

	float getSoftness();

	void setSoftness(float inValue);

	bool isActive();

	void setActive(bool inValue);

private:
	IkConstraintData &_data;
	Vector<Bone *> _bones;
	int _bendDirection;
	bool _compress;
	bool _stretch;
	float _mix;
	float _softness;
	Bone *_target;
	bool _active;
};
}

#endif /* Skel_IkConstraint_h */
