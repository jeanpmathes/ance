#include "content_exception.h"

data::content_exception::content_exception(const std::string& message) : std::runtime_error(message)
{

}
