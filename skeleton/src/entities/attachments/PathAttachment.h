#ifndef Skel_PathAttachment_h
#define Skel_PathAttachment_h

#include "VertexAttachment.h"

namespace skel {
	class SK_API PathAttachment : public VertexAttachment {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		RTTI_DECL

	public:
		explicit PathAttachment(const String& name);

		/// The length in the setup pose from the start of the path to the end of each curve.
		Vector<float>& getLengths();
		bool isClosed();
		void setClosed(bool inValue);
		bool isConstantSpeed();
		void setConstantSpeed(bool inValue);

		virtual Attachment* copy();
	private:
		Vector<float> _lengths;
		bool _closed;
		bool _constantSpeed;
	};
}

#endif /* Skel_PathAttachment_h */
