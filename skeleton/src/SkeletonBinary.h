#ifndef Skel_SkeletonBinary_h
#define Skel_SkeletonBinary_h

#include "config/TransformMode.h"
#include "common/Vector.h"
#include "common/SkelObject.h"

#include "common/SkelString.h"
#include "common/Color.h"

namespace skel {
	class SkeletonData;
	class Atlas;
	class AttachmentLoader;
	class LinkedMesh;
	class Skin;
	class Attachment;
	class VertexAttachment;
	class Animation;
	class CurveTimeline;
	class SkeletonObjectCreator;

	class SK_API SkeletonBinary : public SkelObject {
	public:
		static const int BONE_ROTATE;
		static const int BONE_TRANSLATE;
		static const int BONE_SCALE;
		static const int BONE_SHEAR;

		static const int SLOT_ATTACHMENT;
		static const int SLOT_COLOR;
		static const int SLOT_TWO_COLOR;

		static const int PATH_POSITION;
		static const int PATH_SPACING;
		static const int PATH_MIX;

		static const int CURVE_LINEAR;
		static const int CURVE_STEPPED;
		static const int CURVE_BEZIER;

		explicit SkeletonBinary(Atlas* atlasArray);

		explicit SkeletonBinary(AttachmentLoader* attachmentLoader);

		~SkeletonBinary();

		SkeletonData* readSkeletonData(const unsigned char* binary, int length, SkeletonObjectCreator &creator);

		SkeletonData* readSkeletonDataFile(const String& path, SkeletonObjectCreator &creator);

		void setScale(float scale) { _scale = scale; }

		String& getError() { return _error; }

	private:
		struct DataInput : public SkelObject {
			const unsigned char* cursor;
			const unsigned char* end;
		};

		AttachmentLoader* _attachmentLoader;
		Vector<LinkedMesh*> _linkedMeshes;
		String _error;
		float _scale;
		const bool _ownsLoader;

		void setError(const char* value1, const char* value2);

		char* readString(DataInput* input);

		char* readStringRef(DataInput* input, SkeletonData* skeletonData);

		float readFloat(DataInput* input);

		unsigned char readByte(DataInput* input);

		signed char readSByte(DataInput* input);

		bool readBoolean(DataInput* input);

		int readInt(DataInput* input);

		void readColor(DataInput* input, Color& color);

		int readVarint(DataInput* input, bool optimizePositive);

		Skin* readSkin(SkeletonObjectCreator &creator, DataInput* input, bool defaultSkin, SkeletonData* skeletonData, bool nonessential);

		Attachment* readAttachment(SkeletonObjectCreator &creator, DataInput* input, Skin* skin, int slotIndex, const String& attachmentName, SkeletonData* skeletonData, bool nonessential);

		void readVertices(DataInput* input, VertexAttachment* attachment, int vertexCount);

		void readFloatArray(DataInput *input, int n, float scale, Vector<float>& array);

		void readShortArray(DataInput *input, Vector<unsigned short>& array);

		Animation* readAnimation(const String& name, DataInput* input, SkeletonData *skeletonData);

		void readCurve(DataInput* input, int frameIndex, CurveTimeline* timeline);
	};
}

#endif /* Skel_SkeletonBinary_h */
