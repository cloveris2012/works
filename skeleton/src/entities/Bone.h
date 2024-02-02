#ifndef Skel_Bone_h
#define Skel_Bone_h

#include "common/SkelObject.h"
#include "common/Vector.h"
#include "Updatable.h"

namespace skel {
class BoneData;

class Skeleton;

/// Stores a bone's current pose.
///
/// A bone has a local transform which is used to compute its world transform. A bone also has an applied transform, which is a
/// local transform that can be applied to compute the world transform. The local transform and applied transform may differ if a
/// constraint or application code modifies the world transform after it was computed from the local transform.
class SK_API Bone : public Updatable {
	friend class AnimationState;

	friend class RotateTimeline;

	friend class IkConstraint;

	friend class TransformConstraint;

	friend class VertexAttachment;

	friend class PathConstraint;

	friend class Skeleton;

	friend class RegionAttachment;

	friend class PointAttachment;

	friend class ScaleTimeline;

	friend class ShearTimeline;

	friend class TranslateTimeline;

RTTI_DECL

public:
	static void setYDown(bool inValue);

	static bool isYDown();

	/// @param parent May be NULL.
	Bone(BoneData &data, Skeleton &skeleton, Bone *parent = NULL);

	/// Same as updateWorldTransform. This method exists for Bone to implement SKEL::Updatable.
	virtual void update();

	/// Computes the world transform using the parent bone and this bone's local transform.
	void updateWorldTransform();

	/// Computes the world transform using the parent bone and the specified local transform.
	void updateWorldTransform(float x, float y, float rotation, float scaleX, float scaleY, float shearX, float shearY);

	void setToSetupPose();

	void worldToLocal(float worldX, float worldY, float &outLocalX, float &outLocalY);

	void localToWorld(float localX, float localY, float &outWorldX, float &outWorldY);

	float localToWorldX(float localX, float localY);
    
	float localToWorldY(float localX, float localY);

	float worldToLocalRotation(float worldRotation);

	float localToWorldRotation(float localRotation);

	/// Rotates the world transform the specified amount and sets isAppliedValid to false.
	/// @param degrees Degrees.
	void rotateWorld(float degrees);

	float getWorldToLocalRotationX();

	float getWorldToLocalRotationY();

	BoneData &getData();

	Skeleton &getSkeleton();

	Bone *getParent();

	Vector<Bone *> &getChildren();

	/// The local X translation.
	float getX();

	void setX(float inValue);

	/// The local Y translation.
	float getY();

	void setY(float inValue);

	/// The local rotation.
	float getRotation();

	void setRotation(float inValue);

	/// The local scaleX.
	float getScaleX();

	void setScaleX(float inValue);

	/// The local scaleY.
	float getScaleY();

	void setScaleY(float inValue);

	/// The local shearX.
	float getShearX();

	void setShearX(float inValue);

	/// The local shearY.
	float getShearY();

	void setShearY(float inValue);

	/// The rotation, as calculated by any constraints.
	float getAppliedRotation();

	void setAppliedRotation(float inValue);

	/// The applied local x translation.
	float getAX();

	void setAX(float inValue);

	/// The applied local y translation.
	float getAY();

	void setAY(float inValue);

	/// The applied local scaleX.
	float getAScaleX();

	void setAScaleX(float inValue);

	/// The applied local scaleY.
	float getAScaleY();

	void setAScaleY(float inValue);

	/// The applied local shearX.
	float getAShearX();

	void setAShearX(float inValue);

	/// The applied local shearY.
	float getAShearY();

	void setAShearY(float inValue);

	float getA();

	void setA(float inValue);

	float getB();

	void setB(float inValue);

	float getC();

	void setC(float inValue);

	float getD();

	void setD(float inValue);

	float getWorldX();

	void setWorldX(float inValue);

	float getWorldY();

	void setWorldY(float inValue);

	float getWorldRotationX();

	float getWorldRotationY();

	/// Returns the magnitide (always positive) of the world scale X.
	float getWorldScaleX();

	/// Returns the magnitide (always positive) of the world scale Y.
	float getWorldScaleY();

	bool isAppliedValid();
	void setAppliedValid(bool valid);

	bool isActive();

	void setActive(bool inValue);

	int getIndex();

	void setIndex(int inValue);

	void updateAppliedTransform();

protected:
	static bool yDown;

	BoneData &_data;
	Skeleton &_skeleton;
	Bone *_parent;
	Vector<Bone *> _children;
	float _x, _y, _rotation, _scaleX, _scaleY, _shearX, _shearY;
	float _ax, _ay, _arotation, _ascaleX, _ascaleY, _ashearX, _ashearY;
	bool _appliedValid;
	float _a, _b, _worldX;
	float _c, _d, _worldY;
	bool _sorted;
	bool _active;
	int _index;

	/// Computes the individual applied transform values from the world transform. This can be useful to perform processing using
	/// the applied transform after the world transform has been modified directly (eg, by a constraint)..
	///
	/// Some information is ambiguous in the world transform, such as -1,-1 scale versus 180 rotation.
	
};
}

#endif /* Skel_Bone_h */
