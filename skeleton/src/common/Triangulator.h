#ifndef Skel_Triangulator_h
#define Skel_Triangulator_h

#include "common/Vector.h"
#include "Pool.h"

namespace skel {
class SK_API Triangulator : public SkelObject {
public:
	~Triangulator();

	Vector<int> &triangulate(Vector<float> &vertices);

	Vector< Vector<float>* > &decompose(Vector<float> &vertices, Vector<int> &triangles);

private:
	Vector<Vector < float>* > _convexPolygons;
	Vector<Vector < int>* > _convexPolygonsIndices;

	Vector<int> _indices;
	Vector<bool> _isConcaveArray;
	Vector<int> _triangles;

	Pool <Vector<float> > _polygonPool;
	Pool <Vector<int> > _polygonIndicesPool;

	static bool isConcave(int index, int vertexCount, Vector<float> &vertices, Vector<int> &indices);

	static bool positiveArea(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y);

	static int winding(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y);
};
}

#endif /* Skel_Triangulator_h */
