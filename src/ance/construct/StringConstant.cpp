#include "StringConstant.h"

#include <sstream>

#include "ArrayType.h"
#include "IntegerType.h"
#include "ByteConstant.h"

ance::StringConstant::StringConstant(std::string string, Application& app)
	: type_(ance::ArrayType::get(app, ance::IntegerType::get(app, 8, false), string.size())),
	  string_(string)
{

}

ance::Type* ance::StringConstant::getType()
{
	return type_;
}

llvm::Constant* ance::StringConstant::buildContent(llvm::LLVMContext& c)
{
	return llvm::ConstantDataArray::getString(c, string_, false);
}

std::string ance::StringConstant::parse(const std::string& unparsed)
{
	std::stringstream builder;

	bool escaped = false;

	for (char const& c : unparsed)
	{
		if (escaped)
		{
			builder << ance::ByteConstant::resolveEscaped(c);
			escaped = false;
		}
		else
		{
			if (c == '\\')
			{
				escaped = true;
			}
			else if (c != '"')
			{
				builder << c;
			}
		}
	}

	return builder.str();
}
