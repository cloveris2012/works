#ifndef Skel_SkeletonData_h
#define Skel_SkeletonData_h

#include "common/Vector.h"
#include "common/SkelString.h"

namespace skel {
class BoneData;

class SlotData;

class Skin;

class EventData;

class Animation;

class IkConstraintData;

class TransformConstraintData;

class PathConstraintData;

/// Stores the setup pose and all of the stateless data for a skeleton.
class SK_API SkeletonData : public SkelObject {

	friend class SkeletonBinary;

	friend class SkeletonJson;

	friend class Skeleton;

public:
	SkeletonData();

	~SkeletonData();

	/// Finds a bone by comparing each bone's name.
	/// It is more efficient to cache the results of this method than to call it multiple times.
	/// @return May be NULL.
	BoneData *findBone(const String &boneName);

	/// @return -1 if the bone was not found.
	int findBoneIndex(const String &boneName);

	/// @return May be NULL.
	SlotData *findSlot(const String &slotName);

	/// @return -1 if the slot was not found.
	int findSlotIndex(const String &slotName);

	/// @return May be NULL.
	Skin *findSkin(const String &skinName);

	/// @return May be NULL.
	skel::EventData *findEvent(const String &eventDataName);

	/// @return May be NULL.
	Animation *findAnimation(const String &animationName);

	/// @return May be NULL.
	IkConstraintData *findIkConstraint(const String &constraintName);

	/// @return May be NULL.
	TransformConstraintData *findTransformConstraint(const String &constraintName);

	/// @return May be NULL.
	PathConstraintData *findPathConstraint(const String &constraintName);

	/// @return -1 if the path constraint was not found.
	int findPathConstraintIndex(const String &pathConstraintName);

	const String &getName();

	void setName(const String &inValue);

	/// The skeleton's bones, sorted parent first. The root bone is always the first bone.
	Vector<BoneData *> &getBones();

	Vector<SlotData *> &getSlots();

	/// All skins, including the default skin.
	Vector<Skin *> &getSkins();

	/// The skeleton's default skin.
	/// By default this skin contains all attachments that were not in a skin in Skel.
	/// @return May be NULL.
	Skin *getDefaultSkin();

	void setDefaultSkin(Skin *inValue);

	Vector<skel::EventData *> &getEvents();

	Vector<Animation *> &getAnimations();

	Vector<IkConstraintData *> &getIkConstraints();

	Vector<TransformConstraintData *> &getTransformConstraints();

	Vector<PathConstraintData *> &getPathConstraints();

	float getX();

	void setX(float inValue);

	float getY();

	void setY(float inValue);

	float getWidth();

	void setWidth(float inValue);

	float getHeight();

	void setHeight(float inValue);

	/// The Skel version used to export this data, or NULL.
	const String &getVersion();

	void setVersion(const String &inValue);

	const String &getHash();

	void setHash(const String &inValue);

	const String &getImagesPath();

	void setImagesPath(const String &inValue);

	const String &getAudioPath();

	void setAudioPath(const String &inValue);

	/// The dopesheet FPS in Skel. Available only when nonessential data was exported.
	float getFps();

	void setFps(float inValue);

protected:
	String _name;
	Vector<BoneData *> _bones; // Ordered parents first
	Vector<SlotData *> _slots; // Setup pose draw order.
	Vector<Skin *> _skins;
	Skin *_defaultSkin;
	Vector<EventData *> _events;
	Vector<Animation *> _animations;
	Vector<IkConstraintData *> _ikConstraints;
	Vector<TransformConstraintData *> _transformConstraints;
	Vector<PathConstraintData *> _pathConstraints;
	float _x, _y, _width, _height;
	String _version;
	String _hash;
	Vector<char*> _strings;

	// Nonessential.
	float _fps;
	String _imagesPath;
	String _audioPath;
};
}

#endif /* Skel_SkeletonData_h */
