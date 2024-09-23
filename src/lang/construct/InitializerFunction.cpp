#include "InitializerFunction.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/CodeBlock.h"
#include "lang/expression/VariableAccess.h"
#include "lang/statement/Assignment.h"

lang::InitializerFunction::InitializerFunction(lang::Function& function,
                                               Statement&      initializer,
                                               lang::Scope&    containing_scope)
    : lang::StatementFunction(function,
                              lang::AccessModifier::PRIVATE_ACCESS,
                              false,
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

    Owned<Statement> assignment =
        makeOwned<Assignment>(makeOwned<VariableAccess>(variable, false, lang::Location::global()),
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

Optional<lang::Location> lang::InitializerFunction::getDefinitionLocation() const
{
    return lang::Location::global();
}

bool lang::InitializerFunction::preserveUnitReturn() const
{
    return false;
}
