#ifndef Skel_RegionAttachment_h
#define Skel_RegionAttachment_h

#include "Attachment.h"
#include "common/Vector.h"
#include "common/Color.h"
#include "common/HasRendererObject.h"
#include <string>

#define NUM_UVS 8

namespace skel {
	class Bone;

	/// Attachment that displays a texture region.
	class SK_API RegionAttachment : public Attachment, public HasRendererObject {
		friend class SkeletonBinary;
		friend class SkeletonJson;
		friend class AtlasAttachmentLoader;

		RTTI_DECL

	public:
		explicit RegionAttachment(const String& name);

		void updateOffset();

		void setUVs(float u, float v, float u2, float v2, bool rotate);

		/// Transforms the attachment's four vertices to world coordinates.
		/// @param bone The parent bone.
		/// @param worldVertices The output world vertices. Must have a length greater than or equal to offset + 8.
		/// @param offset The worldVertices index to begin writing values.
		/// @param stride The number of worldVertices entries between the value pairs written.
		void computeWorldVertices(Bone& bone, float *worldVertices, size_t offset, size_t stride = 2);
		void computeWorldVertices(Bone& bone, Vector<float>& worldVertices, size_t offset, size_t stride = 2);
		void computeVertices(Bone& bone, float *vertices, size_t offset, size_t stride);

		float getX();
		void setX(float inValue);
		float getY();
		void setY(float inValue);
		float getRotation();
		void setRotation(float inValue);
		float getScaleX();
		void setScaleX(float inValue);
		float getScaleY();
		void setScaleY(float inValue);
		float getWidth();
		void setWidth(float inValue);
		float getHeight();
		void setHeight(float inValue);

		Color& getColor();

		const String& getPath();
		void setPath(const String& inValue);

		float getRegionOffsetX();
		void setRegionOffsetX(float inValue);

		float getRegionOffsetY();
		void setRegionOffsetY(float inValue);

		float getRegionWidth();
		void setRegionWidth(float inValue);

		float getRegionHeight();
		void setRegionHeight(float inValue);

		float getRegionOriginalWidth();
		void setRegionOriginalWidth(float inValue);

		float getRegionOriginalHeight();
		void setRegionOriginalHeight(float inValue);

		Vector<float>& getOffset();
		Vector<float>& getUVs();

		std::string getTexName();

		virtual Attachment* copy();

	private:
		static const int BLX;
		static const int BLY;
		static const int ULX;
		static const int ULY;
		static const int URX;
		static const int URY;
		static const int BRX;
		static const int BRY;

		float _x, _y, _rotation, _scaleX, _scaleY, _width, _height;
		float _regionOffsetX, _regionOffsetY, _regionWidth, _regionHeight, _regionOriginalWidth, _regionOriginalHeight;
		Vector<float> _vertexOffset;
		Vector<float> _uvs;
		String _path;
		float _regionU;
		float _regionV;
		float _regionU2;
		float _regionV2;
		Color _color;
		std::string _texName;
	};
}

#endif /* Skel_RegionAttachment_h */
