#include "UnitType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/construct/constant/BooleanConstant.h"
#include "lang/type/Type.h"

lang::UnitType::UnitType() : TypeDefinition(lang::Identifier::like("()")) {}

StateCount lang::UnitType::getStateCount() const
{
    return StateCount::unit();
}

llvm::Constant* lang::UnitType::getDefaultContent(CompileContext& context) const
{
    return llvm::ConstantStruct::get(getContentType(context), {});
}

llvm::StructType* lang::UnitType::getContentType(CompileContext& context) const
{
    if (!native_type_)
    {
        native_type_ = llvm::StructType::create(context.exec().llvmContext(), "unit");

        std::vector<llvm::Type*> const elements;
        native_type_->setBody(elements, false);
    }

    return native_type_;
}

std::string lang::UnitType::createMangledName() const
{
    return std::string(name().text());
}

Execution::Type lang::UnitType::createDebugType(CompileContext& context) const
{
    return context.exec().registerUnitType(self());
}

bool lang::UnitType::isUnitType() const
{
    return true;
}

void lang::UnitType::performDefaultInitializer(Shared<Value>, Shared<Value>, CompileContext&)
{
    // No runtime initialization required.
}

void lang::UnitType::performCopyInitializer(Shared<Value>, Shared<Value>, CompileContext&)
{
    // No runtime copy required.
}

void lang::UnitType::performFinalizer(Shared<Value>, Shared<Value>, CompileContext&)
{
    // No runtime finalization required.
}

lang::ResolvingHandle<lang::Type> lang::UnitType::clone(lang::Context& new_context) const
{
    return new_context.getUnitType();
}

bool lang::UnitType::isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const
{
    return op.isEquality() && other.isUnitType();
}

lang::ResolvingHandle<lang::Type> lang::UnitType::getOperatorResultType(lang::BinaryOperator              op,
                                                                        lang::ResolvingHandle<lang::Type> other)
{
    return TypeDefinition::getOperatorResultType(op, other);
}

bool lang::UnitType::validateOperator(lang::BinaryOperator,
                                      lang::Type const&,
                                      lang::Location,
                                      lang::Location,
                                      ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::UnitType::buildOperator(lang::BinaryOperator op,
                                                  Shared<Value>,
                                                  Shared<Value>,
                                                  CompileContext&)
{
    if (op == BinaryOperator::EQUAL) return BooleanConstant::createTrue(scope()->context());

    if (op == BinaryOperator::NOT_EQUAL) return BooleanConstant::createFalse(scope()->context());

    throw std::logic_error("Unit type does not support operator '" + op.toString() + "'");
}
