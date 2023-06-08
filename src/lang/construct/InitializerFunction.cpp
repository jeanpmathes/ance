#include "InitializerFunction.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/CodeBlock.h"
#include "lang/expression/VariableAccess.h"
#include "lang/statement/Assignment.h"

lang::InitializerFunction::InitializerFunction(lang::Function& function,
                                               Statement&      initializer,
                                               lang::Scope&    containing_scope)
    : lang::StatementFunction(function,
                              lang::AccessModifier::PRIVATE_ACCESS,
                              containing_scope.context().getUnitType(),
                              lang::Location::global(),
                              {},
                              initializer,
                              containing_scope,
                              lang::Location::global())
{}

Owned<Statement> lang::InitializerFunction::makeInitializerBlock(lang::ResolvingHandle<lang::Variable> variable,
                                                                 lang::Assigner                        assigner,
                                                                 Owned<Expression>                     initializer)
{
    Owned<lang::CodeBlock> code = lang::CodeBlock::makeScoped(lang::Location::global());

    Owned<Statement> assignment = makeOwned<Assignment>(makeOwned<VariableAccess>(variable, lang::Location::global()),
                                                        assigner,
                                                        std::move(initializer),
                                                        lang::Location::global());

    Owned<lang::CodeBlock> body = lang::CodeBlock::makeWithStatement(std::move(assignment));
    code->append(std::move(body));

    return code;
}

bool lang::InitializerFunction::isMangled() const
{
    return false;
}

void lang::InitializerFunction::createNativeBacking(CompileContext& context)
{
    StatementFunction::createNativeBacking(context);

    auto [native_type, native_function] = getNativeRepresentation();

    llvm::DISubroutineType* debug_type =
        context.di().createSubroutineType(context.di().getOrCreateTypeArray({returnType()->getDebugType(context)}));
    llvm::DISubprogram* subprogram =
        context.di().createFunction(scope().getDebugScope(context),
                                    name().text(),
                                    native_function->getName(),
                                    nullptr,
                                    0,
                                    debug_type,
                                    0,
                                    llvm::DINode::DIFlags::FlagPrototyped,
                                    llvm::DISubprogram::toSPFlags(false, true, false, 0U, false));

    native_function->setSubprogram(subprogram);
}
