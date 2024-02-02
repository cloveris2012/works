#ifndef Skel_RTTI_h
#define Skel_RTTI_h

#include "common/SkelObject.h"

namespace skel {
class SK_API RTTI : public SkelObject {
public:
	explicit RTTI(const char *className);

	RTTI(const char *className, const RTTI &baseRTTI);

	const char *getClassName() const;

	bool isExactly(const RTTI &rtti) const;

	bool instanceOf(const RTTI &rtti) const;

private:
	// Prevent copying
	RTTI(const RTTI &obj);

	RTTI &operator=(const RTTI &obj);

	const char* _className;
	const RTTI *_pBaseRTTI;
};
}

#define RTTI_DECL \
public: \
static const skel::RTTI rtti; \
virtual const skel::RTTI& getRTTI() const;

#define RTTI_IMPL_NOPARENT(name) \
const skel::RTTI name::rtti(#name); \
const skel::RTTI& name::getRTTI() const { return rtti; }

#define RTTI_IMPL(name, parent) \
const skel::RTTI name::rtti(#name, parent::rtti); \
const skel::RTTI& name::getRTTI() const { return rtti; }

#endif /* Skel_RTTI_h */
