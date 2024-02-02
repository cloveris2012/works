#ifndef Skel_Constraint_h
#define Skel_Constraint_h

#include "entities/Updatable.h"
#include "common/SkelString.h"

namespace skel {
/// The interface for all constraints.
class SK_API ConstraintData : public SkelObject {

public:
	ConstraintData(const String& name);

	virtual ~ConstraintData();

	/// The IK constraint's name, which is unique within the skeleton.
	const String& getName();

	/// The ordinal for the order a skeleton's constraints will be applied.
	size_t getOrder();
	void setOrder(size_t inValue);

	/// Whether the constraint is only active for a specific skin.
	bool isSkinRequired();
	void setSkinRequired(bool inValue);

private:
	const String _name;
	size_t _order;
	bool _skinRequired;
};
}

#endif /* Skel_Constraint_h */
