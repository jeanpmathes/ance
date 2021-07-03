#ifndef ANCE_SRC_MANAGEMENT_CONTENT_EXCEPTION_H_
#define ANCE_SRC_MANAGEMENT_CONTENT_EXCEPTION_H_

#include <string>
#include <stdexcept>

namespace data
{
class content_exception : public std::runtime_error
{
	public:
		explicit content_exception(const std::string& message);
};
}

#endif
