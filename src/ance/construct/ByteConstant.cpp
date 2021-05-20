#include "ByteConstant.h"

#include <utility>

#include "Application.h"
#include "IntegerType.h"

ance::ByteConstant::ByteConstant(uint8_t byte, Application& app)
	: type_(ance::IntegerType::get(app, 8, false)), byte_(byte)
{

}

ance::Type* ance::ByteConstant::getType()
{
	return type_;
}

llvm::Constant * ance::ByteConstant::buildContent(llvm::LLVMContext& c)
{
	return llvm::ConstantInt::get(type_->getNativeType(c), byte_, false);
}

char ance::ByteConstant::resolveEscaped(char content)
{
	switch (content)
	{
		case 'n':
			return '\n';

		case '0':
			return '\0';

		default:
			return content;
	}
}

uint8_t ance::ByteConstant::parse(const std::string& unparsed)
{
	uint8_t byte;
	bool escaped = false;

	for (char const& c : unparsed)
	{
		if (escaped)
		{
			byte = resolveEscaped(c);
			escaped = false;
		}
		else
		{
			if (c == '\\')
			{
				escaped = true;
			}
			else if (c != '\'')
			{
				byte = c;
			}
		}
	}

	return byte;
}
