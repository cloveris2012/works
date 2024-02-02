#ifndef Skel_SkeletonJson_h
#define Skel_SkeletonJson_h

#include "common/Vector.h"
#include "common/SkelString.h"
#include "common/SkelObject.h"
#include <map>

namespace skel {
class CurveTimeline;

class VertexAttachment;

class Animation;

class Json;

class SkeletonData;

class Atlas;

class AttachmentLoader;

class LinkedMesh;

class String;

class SkeletonObjectCreator;

class SK_API SkeletonJson : public SkelObject {
public:
	explicit SkeletonJson(Atlas *atlas);

	explicit SkeletonJson(AttachmentLoader *attachmentLoader);

	~SkeletonJson();

	SkeletonData *readSkeletonDataFile(const String &path, SkeletonObjectCreator &creator);

	SkeletonData *readSkeletonData(const char *json, SkeletonObjectCreator &creator);

	SkeletonData *readSkeletonDataWithSkin(const char *json, std::map<std::string, std::string> skinList, SkeletonObjectCreator& creator);

	void setScale(float scale) { _scale = scale; }

	String &getError() { return _error; }

private:
	AttachmentLoader *_attachmentLoader;
	Vector<LinkedMesh *> _linkedMeshes;
	float _scale;
	const bool _ownsLoader;
	String _error;

	static void readCurve(Json *frame, CurveTimeline *timeline, size_t frameIndex);

	Animation *readAnimation(Json *root, SkeletonData *skeletonData, SkeletonObjectCreator &creator);

	void readVertices(Json *attachmentMap, VertexAttachment *attachment, size_t verticesLength);

	void setError(Json *root, const String &value1, const String &value2);
};
}

#endif /* Skel_SkeletonJson_h */
