#include "AssignableExpression.h"

#include "Type.h"
#include "PointerType.h"

bool AssignableExpression::canAssignToValue()
{
	// Currently only values stored as pointer internally or actual pointer values allow assignment to their elements.
	return getType()->storage() == InternalStorage::AS_POINTER || ance::PointerType::isPointerType(getType());
}
