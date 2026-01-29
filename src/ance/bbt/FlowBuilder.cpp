#include "FlowBuilder.h"

#include <cassert>
#include <map>

#include "ance/core/Intrinsic.h"

#include "ance/bbt/Type.h"
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
        TypeContext&   type_context_;

        std::vector<BlockInfo> blocks_;
        size_t                 active_id_ = std::numeric_limits<size_t>::max();

        Implementation(core::Location const& location, TypeContext& type_context) : location_(location), type_context_(type_context) {}

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

        Temporary const& pushTemporary(std::string id)
        {
            utility::Owned<Temporary> temporary = utility::makeOwned<Temporary>(id, location_);
            Temporary const&          ref       = *temporary;

            pushStatement(std::move(temporary));

            return ref;
        }

        std::map<std::string_view, size_t> variable_access_counters_;

        Temporary const& pushVariableAccess(core::Identifier const& name)
        {
            size_t count = variable_access_counters_[name.text()]++;

            Temporary const& scope_arg = pushTemporary(std::format("access_'{}'_{}_scope", name.text(), count));
            pushStatement(utility::makeOwned<CurrentScope>(scope_arg, location_));

            Temporary const& identifier_arg = pushTemporary(std::format("access_'{}'_{}_identifier", name.text(), count));
            pushStatement(utility::makeOwned<Constant>(Identifier::make(name, type_context_), identifier_arg, location_));

            Temporary const&                                       resolve_result = pushTemporary(std::format("access_'{}'_{}_resolve", name.text(), count));
            utility::List<std::reference_wrapper<Temporary const>> resolve_arguments;
            resolve_arguments.emplace_back(scope_arg);
            resolve_arguments.emplace_back(identifier_arg);
            pushStatement(utility::makeOwned<Intrinsic>(core::Intrinsic::RESOLVE, std::move(resolve_arguments), resolve_result, location_));

            Temporary const& access_result = pushTemporary(std::format("access_'{}'_{}_result", name.text(), count));
            pushStatement(utility::makeOwned<Access>(resolve_result, access_result, location_));

            return access_result;
        }

        size_t constant_counter_ = 0;

        Temporary const& pushConstant(utility::Shared<Value> value)
        {
            Temporary const& constant_result = pushTemporary(std::format("constant_{}", constant_counter_++));
            pushStatement(utility::makeOwned<Constant>(std::move(value), constant_result, location_));

            return constant_result;
        }

        utility::Owned<Flow> build(std::string identifier)
        {
            utility::List<utility::Owned<BasicBlock>> blocks;

            for (size_t id = 0; id < blocks_.size(); id++)
            {
                blocks.emplace_back(
                    utility::makeOwned<BasicBlock>(id, std::move(blocks_[id].statements), utility::makeOwned<Return>(nullptr, location_), location_));
            }

            blocks_.clear();
            active_id_ = std::numeric_limits<size_t>::max();

            BasicBlock& entry = *blocks[0];

            return utility::makeOwned<Flow>(std::move(blocks), entry, std::move(identifier), location_);
        }
    };

    FlowBuilder::FlowBuilder(core::Location const& location, TypeContext& type_context)
        : implementation_(utility::makeOwned<Implementation>(location, type_context))
    {}

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

    Temporary const& FlowBuilder::pushTemporary(std::string id)
    {
        return implementation_->pushTemporary(std::move(id));
    }

    Temporary const& FlowBuilder::pushVariableAccess(core::Identifier const& name)
    {
        return implementation_->pushVariableAccess(name);
    }

    Temporary const& FlowBuilder::pushConstant(utility::Shared<Value> value)
    {
        return implementation_->pushConstant(std::move(value));
    }

    utility::Owned<Flow> FlowBuilder::build(std::string id)
    {
        return implementation_->build(std::move(id));
    }

}
