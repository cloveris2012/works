#ifndef Skel_MeshAttachment_h
#define Skel_MeshAttachment_h

#include "VertexAttachment.h"
#include "common/Vector.h"
#include "common/Color.h"
#include "common/HasRendererObject.h"
#include <string>

namespace skel {
	/// Attachment that displays a texture region using a mesh.
	class SK_API MeshAttachment : public VertexAttachment, public HasRendererObject {
		friend class SkeletonBinary;
		friend class SkeletonJson;
		friend class AtlasAttachmentLoader;

		RTTI_DECL

	public:
		explicit MeshAttachment(const String& name);

		virtual ~MeshAttachment();

		void updateUVs();

		int getHullLength();
		void setHullLength(int inValue);

		Vector<float>& getRegionUVs();

		/// The UV pair for each vertex, normalized within the entire texture. See also MeshAttachment::updateUVs
		Vector<float>& getUVs();

		Vector<unsigned short>& getTriangles();

		Color& getColor();

		const String& getPath();
		void setPath(const String& inValue);

		float getRegionU();
		void setRegionU(float inValue);

		float getRegionV();
		void setRegionV(float inValue);

		float getRegionU2();
		void setRegionU2(float inValue);

		float getRegionV2();
		void setRegionV2(float inValue);

		bool getRegionRotate();
		void setRegionRotate(bool inValue);

		int getRegionDegrees();
		void setRegionDegrees(int inValue);

		float getRegionOffsetX();
		void setRegionOffsetX(float inValue);

		// Pixels stripped from the bottom left, unrotated.
		float getRegionOffsetY();
		void setRegionOffsetY(float inValue);

		float getRegionWidth();
		void setRegionWidth(float inValue);

		// Unrotated, stripped size.
		float getRegionHeight();
		void setRegionHeight(float inValue);

		float getRegionOriginalWidth();
		void setRegionOriginalWidth(float inValue);

		// Unrotated, unstripped size.
		float getRegionOriginalHeight();
		void setRegionOriginalHeight(float inValue);

		MeshAttachment* getParentMesh();
		void setParentMesh(MeshAttachment* inValue);

		std::string getTexName();

		// Nonessential.
		Vector<unsigned short>& getEdges();
		float getWidth();
		void setWidth(float inValue);
		float getHeight();
		void setHeight(float inValue);

		virtual Attachment* copy();

		MeshAttachment* newLinkedMesh();

		Vector<float> _uvs;
		Vector<unsigned short> _triangles;
		Vector<unsigned short> _edges;
		Vector<float> _regionUVs;
	
private:
		float _regionOffsetX, _regionOffsetY, _regionWidth, _regionHeight, _regionOriginalWidth, _regionOriginalHeight;
		MeshAttachment* _parentMesh;
		String _path;
		float _regionU;
		float _regionV;
		float _regionU2;
		float _regionV2;
		float _width;
		float _height;
		Color _color;
		int _hullLength;
		bool _regionRotate;
		int _regionDegrees;
		std::string _texName;
	};
}

#endif /* Skel_MeshAttachment_h */
