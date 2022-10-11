#include "InitializerFunction.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/CodeBlock.h"
#include "lang/expression/VariableAccess.h"
#include "lang/statement/Assignment.h"
#include "lang/type/VoidType.h"

lang::InitializerFunction::InitializerFunction(lang::Function&                       function,
                                               lang::ResolvingHandle<lang::Variable> variable,
                                               lang::Assigner                        assigner,
                                               std::unique_ptr<Expression>           initializer,
                                               lang::Scope&                          containing_scope)
    : lang::StatementFunction(function,
                              lang::AccessModifier::PRIVATE_ACCESS,
                              lang::VoidType::get(),
                              lang::Location::global(),
                              {},
                              makeCode(std::move(variable), assigner, std::move(initializer)),
                              containing_scope,
                              lang::Location::global())
{}

std::unique_ptr<Statement> lang::InitializerFunction::makeCode(lang::ResolvingHandle<lang::Variable> variable,
                                                               lang::Assigner                        assigner,
                                                               std::unique_ptr<Expression>           initializer)
{
    std::unique_ptr<lang::CodeBlock> code =
        std::unique_ptr<lang::CodeBlock>(lang::CodeBlock::makeScoped(lang::Location::global()));

    std::unique_ptr<Statement> assignment =
        std::make_unique<Assignment>(std::make_unique<VariableAccess>(variable, lang::Location::global()),
                                     assigner,
                                     std::move(initializer),
                                     lang::Location::global());

    std::unique_ptr<lang::CodeBlock> body =
        std::unique_ptr<lang::CodeBlock>(lang::CodeBlock::wrapStatement(std::move(assignment)));
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
        context.di()->createSubroutineType(context.di()->getOrCreateTypeArray({returnType()->getDebugType(context)}));
    llvm::DISubprogram* subprogram =
        context.di()->createFunction(scope().getDebugScope(context),
                                     name().text(),
                                     name().text(),
                                     context.sourceFile(),
                                     0,
                                     debug_type,
                                     0,
                                     llvm::DINode::DIFlags::FlagPrototyped,
                                     llvm::DISubprogram::toSPFlags(false, true, false, 0U, false));

    native_function->setSubprogram(subprogram);
}
