#ifndef Skel_SkeletonBounds_h
#define Skel_SkeletonBounds_h

#include "common/Vector.h"
#include "common/SkelObject.h"
#include "common/Pool.h"

namespace skel {
	class Skeleton;
	class BoundingBoxAttachment;
	class Polygon;

	/// Collects each BoundingBoxAttachment that is visible and computes the world vertices for its polygon.
	/// The polygon vertices are provided along with convenience methods for doing hit detection.
	class SK_API SkeletonBounds : public SkelObject {
	public:
		SkeletonBounds();
		~SkeletonBounds();

		/// Clears any previous polygons, finds all visible bounding box attachments,
		/// and computes the world vertices for each bounding box's polygon.
		/// @param skeleton The skeleton.
		/// @param updateAabb
		/// If true, the axis aligned bounding box containing all the polygons is computed.
		/// If false, the SkeletonBounds AABB methods will always return true.
		///
		void update(Skeleton& skeleton, bool updateAabb);

		/// Returns true if the axis aligned bounding box contains the point.
		bool aabbcontainsPoint(float x, float y);

		/// Returns true if the axis aligned bounding box intersects the line segment.
		bool aabbintersectsSegment(float x1, float y1, float x2, float y2);

		/// Returns true if the axis aligned bounding box intersects the axis aligned bounding box of the specified bounds.
		bool aabbIntersectsSkeleton(SkeletonBounds bounds);

		/// Returns true if the polygon contains the point.
		bool containsPoint(Polygon* polygon, float x, float y);

		/// Returns the first bounding box attachment that contains the point, or NULL. When doing many checks, it is usually more
		/// efficient to only call this method if {@link #aabbcontainsPoint(float, float)} returns true.
		BoundingBoxAttachment* containsPoint(float x, float y);

		/// Returns the first bounding box attachment that contains the line segment, or NULL. When doing many checks, it is usually
		/// more efficient to only call this method if {@link #aabbintersectsSegment(float, float, float, float)} returns true.
		BoundingBoxAttachment* intersectsSegment(float x1, float y1, float x2, float y2);

		/// Returns true if the polygon contains the line segment.
		bool intersectsSegment(Polygon* polygon, float x1, float y1, float x2, float y2);

		Polygon* getPolygon(BoundingBoxAttachment* attachment);

		float getWidth();
		float getHeight();

	private:
		Pool<Polygon> _polygonPool;
		Vector<BoundingBoxAttachment*> _boundingBoxes;
		Vector<Polygon*> _polygons;
		float _minX, _minY, _maxX, _maxY;

		void aabbCompute();
	};

	class Polygon : public SkelObject {
	public:
		Vector<float> _vertices;
		int _count;

		Polygon() : _count(0) {
			_vertices.ensureCapacity(16);
		}
	};
}

#endif /* Skel_SkeletonBounds_h */
