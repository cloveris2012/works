#ifndef Skel_BoneData_h
#define Skel_BoneData_h

#include "config/TransformMode.h"
#include "common/SkelObject.h"
#include "common/SkelString.h"

namespace skel {
class SK_API BoneData : public SkelObject {
	friend class SkeletonBinary;

	friend class SkeletonJson;

	friend class AnimationState;

	friend class RotateTimeline;

	friend class ScaleTimeline;

	friend class ShearTimeline;

	friend class TranslateTimeline;

public:
	BoneData(int index, const String &name, BoneData *parent = NULL);

	/// The index of the bone in Skeleton.Bones
	int getIndex();

	/// The name of the bone, which is unique within the skeleton.
	const String &getName();

	/// May be NULL.
	BoneData *getParent();
	void setParent(BoneData *parent);

	float getLength();

	void setLength(float inValue);

	/// Local X translation.
	float getX();

	void setX(float inValue);

	/// Local Y translation.
	float getY();

	void setY(float inValue);

	/// Local rotation.
	float getRotation();

	void setRotation(float inValue);

	/// Local scaleX.
	float getScaleX();

	void setScaleX(float inValue);

	/// Local scaleY.
	float getScaleY();

	void setScaleY(float inValue);

	/// Local shearX.
	float getShearX();

	void setShearX(float inValue);

	/// Local shearY.
	float getShearY();

	void setShearY(float inValue);

	/// The transform mode for how parent world transforms affect this bone.
	TransformMode getTransformMode();

	void setTransformMode(TransformMode inValue);

	bool isSkinRequired();
	void setSkinRequired(bool inValue);

	int _index;
	String _name;
private:

	BoneData *_parent;
	float _length;
	float _x, _y, _rotation, _scaleX, _scaleY, _shearX, _shearY;
	TransformMode _transformMode;
	bool _skinRequired;
};
}

#endif /* Skel_BoneData_h */
