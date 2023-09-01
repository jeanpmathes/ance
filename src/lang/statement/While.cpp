#include "While.h"

#include "lang/ApplicationVisitor.h"
#include "lang/expression/Expression.h"
#include "lang/type/BooleanType.h"
#include "validation/ValidationLogger.h"

While::While(Owned<Expression> condition, Owned<Statement> block, lang::Location location)
    : Statement(location)
    , condition_(std::move(condition))
    , block_(std::move(block))
{
    addSubexpression(*condition_);
    addSubstatement(*block_);
}

Expression const& While::condition() const
{
    return *condition_;
}

Statement const& While::body() const
{
    return *block_;
}

std::vector<Owned<lang::BasicBlock>> While::createBasicBlocks(lang::BasicBlock&, lang::Function&)
{
    return {};// Handled by the loop statement.
}

void While::validate(ValidationLogger& validation_logger) const
{
    if (!condition_->validate(validation_logger)) return;

    block_->validate(validation_logger);

    lang::Type::checkMismatch(scope()->context().getBooleanType(),
                              condition_->type(),
                              condition_->location(),
                              validation_logger);
}

Statements While::expandWith(Expressions subexpressions, Statements substatements, lang::Context& new_context) const
{
    auto temp_name          = lang::Identifier::like(scope()->getTemporaryName(), location());
    auto make_temp_variable = [&temp_name]() { return lang::makeHandled<lang::Variable>(temp_name); };

    auto condition = std::move(subexpressions[0]);
    auto body      = std::move(substatements[0]);

    Statements statements;

    statements.emplace_back(makeOwned<LocalVariableDefinition>(temp_name,
                                                               condition_->type().getUndefinedTypeClone(new_context),
                                                               location(),
                                                               lang::Assigner::COPY_ASSIGNMENT,
                                                               std::move(condition),
                                                               location()));

    statements.emplace_back(
        makeOwned<If>(makeOwned<UnaryOperation>(lang::UnaryOperator::NOT,
                                                makeOwned<VariableAccess>(make_temp_variable(), true, location()),
                                                location()),
                      makeOwned<Break>(location()),
                      std::nullopt,
                      location()));

    statements.emplace_back(std::move(body));

    return statements;
}

Statements While::arrangeExpandedStatements(Statements before, Statements expanded, Statements after) const
{
    auto condition_variable = std::move(expanded[0]);
    auto loop_break         = std::move(expanded[1]);
    auto loop_inner_body    = std::move(expanded[2]);

    auto loop_body = lang::CodeBlock::makeScoped(location());

    // The before and after parts are around expressions (here: the condition) and not the whole loop.
    loop_body->append(lang::CodeBlock::wrapStatements(std::move(before)));
    loop_body->append(lang::CodeBlock::makeWithStatement(std::move(condition_variable)));
    loop_body->append(lang::CodeBlock::wrapStatements(std::move(after)));

    loop_body->append(lang::CodeBlock::makeWithStatement(std::move(loop_break)));
    loop_body->append(lang::CodeBlock::makeWithStatement(std::move(loop_inner_body)));

    Statements statements;

    statements.emplace_back(makeOwned<Loop>(std::move(loop_body), location()));

    return statements;
}

void While::doBuild(CompileContext&)
{
    // Handled by basic block.
}

bool While::isLoop() const
{
    return true;
}

std::pair<lang::BasicBlock*, lang::BasicBlock*> While::getLoopParts() const
{
    return loop_parts_;
}
