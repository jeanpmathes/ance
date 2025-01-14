#include "InitializerFunction.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/CodeBlock.h"
#include "lang/expression/VariableAccess.h"
#include "lang/statement/Assignment.h"

lang::InitializerFunction::InitializerFunction(lang::Function& function,
                                               Statement&      initializer,
                                               lang::CMP                         cmp,
                                               lang::ResolvingHandle<lang::Type> return_type,
                                               lang::Scope&    containing_scope)
    : lang::StatementFunction(function,
                              lang::AccessModifier::PRIVATE_ACCESS,
                              cmp,
                              return_type,
                              lang::Location::global(),
                              {},
                              initializer,
                              containing_scope,
                              lang::Location::global())
{}

Owned<Statement> lang::InitializerFunction::makeInitializerBlock(lang::ResolvingHandle<lang::Variable> variable,
                                                                 lang::Assigner                        assigner,
                                                                 lang::CMP                             cmp,
                                                                 Owned<Expression>                     initializer)
{
    Owned<lang::CodeBlock> code = lang::CodeBlock::makeScoped(lang::Location::global());

    if (cmp.isCompileTime())
    {
        Owned<Statement> returning = makeOwned<Return>(std::move(initializer), lang::Location::global());

        Owned<lang::CodeBlock> body = lang::CodeBlock::makeWithStatement(std::move(returning));
        code->append(std::move(body));
    }
    else
    {
        Owned<Statement> assignment =
            makeOwned<Assignment>(makeOwned<VariableAccess>(variable, false, lang::Location::global()),
                                  assigner,
                                  std::move(initializer),
                                  lang::Location::global());

        Owned<lang::CodeBlock> body = lang::CodeBlock::makeWithStatement(std::move(assignment));
        code->append(std::move(body));
    }

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
