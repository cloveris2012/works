#ifndef Skel_Vertices_h
#define Skel_Vertices_h

#include "common/Vector.h"

namespace skel {
class SK_API Vertices : public SkelObject {
public:
	Vector<size_t> _bones;
	Vector<float> _vertices;
};
}

#endif /* Skel_Vertices_h */
