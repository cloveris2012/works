#ifndef Skel_Updatable_h
#define Skel_Updatable_h

#include "common/RTTI.h"
#include "common/SkelObject.h"

namespace skel {
class SK_API Updatable : public SkelObject {
RTTI_DECL

public:
	Updatable();

	virtual ~Updatable();

	virtual void update() = 0;

	virtual bool isActive() = 0;

	virtual void setActive(bool inValue) = 0;
};
}

#endif /* Skel_Updatable_h */
