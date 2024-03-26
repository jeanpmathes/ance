#include "UnsignedIntegerPointerType.h"

#include "lang/ApplicationVisitor.h"

lang::UnsignedIntegerPointerType::UnsignedIntegerPointerType() : TypeDefinition(lang::Identifier::like("uiptr")) {}

bool lang::UnsignedIntegerPointerType::isUnsignedIntegerPointerType() const
{
    return true;
}

bool lang::UnsignedIntegerPointerType::acceptOverloadRequest(std::vector<ResolvingHandle<lang::Type>> parameters)
{
    if (parameters.size() == 1 && parameters[0]->isAddressType()) return true;

    return IntegerType::acceptOverloadRequest(parameters);
}

void lang::UnsignedIntegerPointerType::execRequestedOverload(
    std::vector<std::reference_wrapper<lang::Type const>> parameters,
    lang::PredefinedFunction&                             function,
    Execution&                                            exec) const
{
    if (parameters.size() == 1) { execRequestedOverload(parameters[0], self(), function, exec); }
}

void lang::UnsignedIntegerPointerType::execRequestedOverload(lang::Type const&         parameter_element,
                                                             lang::Type const&         return_type,
                                                              lang::PredefinedFunction& function,
                                                              Execution&                exec) const
{
    if (parameter_element.isAddressType())
    {
        lang::Function* fn = &function.function();

        exec.defineFunctionBody(function.function(), [fn](Execution& e) {
            Shared<lang::Value> argument = e.getParameterValue(*fn, 0);
            Shared<lang::Value> result   = e.computePointerToInteger(argument);

            e.performReturn(result);
        });

        return;
    }

    IntegerType::execRequestedOverload(parameter_element, return_type, function, exec);
}

std::string lang::UnsignedIntegerPointerType::createMangledName() const
{
    return std::string(name().text());
}

void lang::UnsignedIntegerPointerType::init(Unit& unit)
{
    size_ = static_cast<unsigned int>(std::max(unit.getTarget().getPointerSize() * 8, MINIMUM_BIT_SIZE));
}

Optional<size_t> lang::UnsignedIntegerPointerType::getBitSize() const
{
    return std::nullopt;
}

size_t lang::UnsignedIntegerPointerType::getNativeBitSize() const
{
    return size_;
}

bool lang::UnsignedIntegerPointerType::isSigned() const
{
    return false;
}

size_t lang::UnsignedIntegerPointerType::getMinimumBitSize() const
{
    return MINIMUM_BIT_SIZE;
}

std::string lang::UnsignedIntegerPointerType::getSuffix() const
{
    return "uiptr";
}

lang::ResolvingHandle<lang::Type> lang::UnsignedIntegerPointerType::clone(lang::Context& new_context) const
{
    return new_context.getUnsignedIntegerPointerType();
}
