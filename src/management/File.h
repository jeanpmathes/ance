#ifndef ANCE_SRC_MANAGEMENT_FILE_H_
#define ANCE_SRC_MANAGEMENT_FILE_H_

#include <filesystem>

#include "Element.h"

namespace data
{
class File
{
	public:
		explicit File(const std::filesystem::path& path);

		const std::filesystem::path& path();

		void read();

		const data::Element& root();

	private:
		const std::filesystem::path& path_;
		std::unique_ptr<data::Element> element_;
};
}

#endif
