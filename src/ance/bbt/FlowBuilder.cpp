#include "FlowBuilder.h"

#include <cassert>
#include <map>

#include "ance/core/Intrinsic.h"

#include "ance/bbt/Value.h"

namespace ance::bbt
{
    struct FlowBuilder::Implementation
    {
        struct BlockInfo
        {
            utility::List<utility::Owned<Statement>> statements;
        };

        core::Location location_;

        std::vector<BlockInfo> blocks_;
        size_t                 active_id_ = std::numeric_limits<size_t>::max();

        explicit Implementation(core::Location const& location) : location_(location) {}

        size_t createBasicBlock()
        {
            size_t const id = blocks_.size();
            blocks_.emplace_back();

            return id;
        }

        void setActiveBasicBlock(size_t const id)
        {
            assert(id < blocks_.size());

            active_id_ = id;
        }

        void pushStatement(utility::Owned<Statement> statement)
        {
            assert(active_id_ < blocks_.size());

            blocks_[active_id_].statements.emplace_back(std::move(statement));
        }

        Temporary const& pushTemporary()
        {
            utility::Owned<Temporary> temporary = utility::makeOwned<Temporary>(location_);
            Temporary&                ref         = *temporary;

            pushStatement(std::move(temporary));

            return ref;
        }

        Temporary const& pushVariableRead(core::Identifier const& name)
        {
            Temporary const& scope_arg = pushTemporary();
            pushStatement(utility::makeOwned<CurrentScope>(scope_arg, location_));

            Temporary const& identifier_arg = pushTemporary();
            pushStatement(utility::makeOwned<Constant>(IdentifierValue::make(name), identifier_arg, location_));

            Temporary const& resolve_result = pushTemporary();
            utility::List<std::reference_wrapper<Temporary const>> resolve_arguments;
            resolve_arguments.emplace_back(scope_arg);
            resolve_arguments.emplace_back(identifier_arg);
            pushStatement(utility::makeOwned<Intrinsic>(core::Resolve::instance(), std::move(resolve_arguments), resolve_result, location_));

            Temporary const& read_result = pushTemporary();
            pushStatement(utility::makeOwned<Read>(resolve_result, read_result, location_));

            return read_result;
        }

        Temporary const& pushConstant(utility::Shared<Value> value)
        {
            Temporary const& constant_result = pushTemporary();
            pushStatement(utility::makeOwned<Constant>(std::move(value), constant_result, location_));

            return constant_result;
        }

        utility::Owned<Flow> build()
        {
            utility::List<utility::Owned<BasicBlock>> blocks;

            for (size_t id = 0; id < blocks_.size(); id++)
            {
                blocks.emplace_back(utility::makeOwned<BasicBlock>(id, std::move(blocks_[id].statements), utility::makeOwned<Return>(location_), location_));
            }

            blocks_.clear();
            active_id_ = std::numeric_limits<size_t>::max();

            BasicBlock& entry = *blocks[0];

            return utility::makeOwned<Flow>(std::move(blocks), entry, location_);
        }
    };

    FlowBuilder::FlowBuilder(core::Location const& location) : implementation_(utility::makeOwned<Implementation>(location)) {}

    FlowBuilder::~FlowBuilder() = default;

    size_t FlowBuilder::createBasicBlock()
    {
        return implementation_->createBasicBlock();
    }

    void FlowBuilder::setActiveBasicBlock(size_t const id)
    {
        implementation_->setActiveBasicBlock(id);
    }

    void FlowBuilder::pushStatement(utility::Owned<Statement> statement)
    {
        implementation_->pushStatement(std::move(statement));
    }

    Temporary const& FlowBuilder::pushTemporary()
    {
        return implementation_->pushTemporary();
    }

    Temporary const& FlowBuilder::pushVariableRead(core::Identifier const& name)
    {
        return implementation_->pushVariableRead(name);
    }

    Temporary const& FlowBuilder::pushConstant(utility::Shared<Value> value)
    {
        return implementation_->pushConstant(std::move(value));
    }

    utility::Owned<Flow> FlowBuilder::build()
    {
        return implementation_->build();
    }

}
