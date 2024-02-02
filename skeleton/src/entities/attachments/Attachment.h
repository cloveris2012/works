#ifndef Skel_Attachment_h
#define Skel_Attachment_h

#include "common/RTTI.h"
#include "common/SkelObject.h"
#include "common/SkelString.h"

namespace skel {
class SK_API Attachment : public SkelObject {
RTTI_DECL

public:
	explicit Attachment(const String &name);

	virtual ~Attachment();

	const String &getName() const;

	virtual Attachment* copy() = 0;

	int getRefCount();
	void reference();
	void dereference();

private:
	const String _name;
	int _refCount;
};
}

#endif /* Skel_Attachment_h */
