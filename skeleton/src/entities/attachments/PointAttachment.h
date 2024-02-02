#ifndef Skel_PointAttachment_h
#define Skel_PointAttachment_h

#include "Attachment.h"

namespace skel {
	class Bone;

	/// An attachment which is a single point and a rotation. This can be used to spawn projectiles, particles, etc. A bone can be
	/// used in similar ways, but a PointAttachment is slightly less expensive to compute and can be hidden, shown, and placed in a
	/// skin.
	///
	/// See http://esotericsoftware.com/skel-point-attachments for Point Attachments in the Skel User Guide.
	///
	class SK_API PointAttachment : public Attachment {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		RTTI_DECL

	public:
		explicit PointAttachment(const String& name);

		void computeWorldPosition(Bone& bone, float& ox, float& oy);

		float computeWorldRotation(Bone& bone);

		float getX();
		void setX(float inValue);

		float getY();
		void setY(float inValue);

		float getRotation();
		void setRotation(float inValue);

		virtual Attachment* copy();

	private:
		float _x, _y, _rotation;
	};
}

#endif /* Skel_PointAttachment_h */
