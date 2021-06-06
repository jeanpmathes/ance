#include "AssignableExpression.h"

#include "Type.h"

bool AssignableExpression::canAssignToValue()
{
	// Currently only values stored as pointer internally allow assignment to their elements.
	return getType()->storage() == InternalStorage::AS_POINTER;
}
