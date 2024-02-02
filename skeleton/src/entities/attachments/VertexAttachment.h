#ifndef Skel_VertexAttachment_h
#define Skel_VertexAttachment_h

#include "Attachment.h"
#include "common/Vector.h"

namespace skel {
	class Slot;

	/// An attachment with vertices that are transformed by one or more bones and can be deformed by a slot's vertices.
	class SK_API VertexAttachment : public Attachment {
		friend class SkeletonBinary;
		friend class SkeletonJson;
		friend class DeformTimeline;

		RTTI_DECL

	public:
		explicit VertexAttachment(const String& name);

		virtual ~VertexAttachment();

		void computeWorldVertices(Slot& slot, float* worldVertices);
		void computeWorldVertices(Slot& slot, Vector<float>& worldVertices);

		/// Transforms local vertices to world coordinates.
		/// @param start The index of the first Vertices value to transform. Each vertex has 2 values, x and y.
		/// @param count The number of world vertex values to output. Must be less than or equal to WorldVerticesLength - start.
		/// @param worldVertices The output world vertices. Must have a length greater than or equal to offset + count.
		/// @param offset The worldVertices index to begin writing values.
		/// @param stride The number of worldVertices entries between the value pairs written.
		void computeWorldVertices(Slot& slot, size_t start, size_t count, float* worldVertices, size_t offset, size_t stride = 2);
		void computeWorldVertices(Slot& slot, size_t start, size_t count, Vector<float>& worldVertices, size_t offset, size_t stride = 2);
		void computeVertices(Slot& slot, size_t start, size_t count, float* vertices, size_t offset, size_t stride = 2);

		/// Gets a unique ID for this attachment.
		int getId();

		Vector<size_t>& getBones();

		Vector<float>& getVertices();

		size_t getWorldVerticesLength();
		void setWorldVerticesLength(size_t inValue);

		VertexAttachment* getDeformAttachment();
		void setDeformAttachment(VertexAttachment* attachment);

		void copyTo(VertexAttachment* other);

	protected:
		Vector<size_t> _bones;
		Vector<float> _vertices;
		size_t _worldVerticesLength;
		VertexAttachment* _deformAttachment;

	private:
		const int _id;

		static int getNextID();
	};
}

#endif /* Skel_VertexAttachment_h */
