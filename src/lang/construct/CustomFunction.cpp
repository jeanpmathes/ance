#include "CustomFunction.h"

#include <utility>

#include <llvm/ADT/SmallVector.h>// critical, missing include will cause linking error

#include "compiler/CompileContext.h"
#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/type/Type.h"
#include "lang/type/VoidType.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::CustomFunction::CustomFunction(Function&                            function,
                                     lang::AccessModifier                 access,
                                     lang::ResolvingHandle<lang::Type>    return_type,
                                     lang::Location                       return_type_location,
                                     std::vector<Shared<lang::Parameter>> parameters,
                                     Owned<Statement>                     code,
                                     Scope&                               containing_scope,
                                     lang::Location                       declaration_location,
                                     lang::Location                       definition_location)
    : lang::StatementFunction(function,
                              access,
                              return_type,
                              return_type_location,
                              std::move(parameters),
                              std::move(code),
                              containing_scope,
                              declaration_location)
    , definition_location_(definition_location)
{}

bool lang::CustomFunction::isMangled() const
{
    return true;
}

void lang::CustomFunction::validate(ValidationLogger& validation_logger) const
{
    if (lang::validation::isTypeUndefined(returnType(), returnTypeLocation(), validation_logger)) return;

    returnType().validate(validation_logger, returnTypeLocation());

    for (auto const [parameter, argument] : llvm::zip(parameters(), arguments()))
    {
        if (not argument.hasValue())
        {
            validation_logger.logError("Name '" + parameter->name() + "' already defined in the current context",
                                       parameter->name().location());
        }

        if (lang::validation::isTypeUndefined(parameter->type(), parameter->typeLocation(), validation_logger)) return;

        parameter->type().validate(validation_logger, parameter->typeLocation());

        if (parameter->type() == lang::VoidType::get())
        {
            validation_logger.logError("Parameter cannot have 'void' type", parameter->location());
        }
    }

    StatementFunction::validate(validation_logger);
}

bool lang::CustomFunction::validateFlow(ValidationLogger& validation_logger) const
{
    validateReturn(validation_logger);
    validateUnreachable(validation_logger);

    return true;
}

void lang::CustomFunction::validateReturn(ValidationLogger& validation_logger) const
{
    std::list<lang::BasicBlock const*> const final_blocks = getInitialBlock().getLeaves();

    Optional<lang::Location> missing_return_location;

    for (auto* block : final_blocks)
    {
        Optional<std::pair<Optional<std::reference_wrapper<lang::Value const>>, lang::Location>> return_value =
            block->getReturnValue();

        if (return_value.hasValue())
        {
            auto& [value, location] = *return_value;

            if (value.hasValue())
            {
                if (returnType().isVoidType())
                {
                    validation_logger.logError("Cannot return value in void function '" + name() + "'",
                                               this->location());
                }
                else
                {
                    lang::Type::checkMismatch(returnType(), value.value().get().type(), location, validation_logger);
                }
            }
            else if (!returnType().isVoidType())
            {
                validation_logger.logError("Missing return value in function '" + name() + "'", location);
            }
            else
            {
                // No value, but void return type -> OK
            }
        }
        else
        {
            if (!returnType().isVoidType())
            {
                lang::Location end = block->getEndLocation();
                if (end.isGlobal()) end = this->location();
                missing_return_location = end;
            }
        }
    }

    if (missing_return_location.hasValue())
    {
        validation_logger.logError("Not all code paths of '" + name() + "' return a value", *missing_return_location);
    }
}

void lang::CustomFunction::validateUnreachable(ValidationLogger& validation_logger) const
{
    Optional<lang::Location> unreachable_code_location = findUnreachableCode();

    if (unreachable_code_location.hasValue())
    {
        validation_logger.logWarning("Unreachable code in function '" + name() + "'", *unreachable_code_location);
    }
}

void lang::CustomFunction::createNativeBacking(CompileContext& context)
{
    StatementFunction::createNativeBacking(context);

    auto [native_type, native_function] = getNativeRepresentation();

    std::vector<llvm::Metadata*> di_types;
    di_types.push_back(returnType()->getDebugType(context));

    for (auto const pair : llvm::zip(parameters(), native_function->args()))
    {
        auto& [parameter, argument] = pair;
        di_types.push_back(parameter->type().getDebugType(context));
    }

    llvm::DISubroutineType* debug_type = context.di().createSubroutineType(context.di().getOrCreateTypeArray(di_types));
    llvm::DISubprogram*     subprogram =
        context.di().createFunction(scope().getDebugScope(context),
                                    name().text(),
                                    isMangled() ? signature_.getMangledName() : name().text(),
                                    context.getSourceFile(location()),
                                    static_cast<unsigned>(location().line()),
                                    debug_type,
                                    static_cast<unsigned>(definition_location_.line()),
                                    llvm::DINode::DIFlags::FlagPrototyped,
                                    llvm::DISubprogram::toSPFlags(false, true, false, 0U, name().text() == "main"));

    native_function->setSubprogram(subprogram);
}

llvm::DISubprogram* lang::CustomFunction::debugSubprogram() const
{
    auto [native_type, native_function] = getNativeRepresentation();
    return native_function->getSubprogram();
}

llvm::DIScope* lang::CustomFunction::getDebugScope(CompileContext&) const
{
    return debugSubprogram();
}
