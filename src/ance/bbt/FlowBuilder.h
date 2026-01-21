#ifndef ANCE_BBT_FLOWBUILDER_H
#define ANCE_BBT_FLOWBUILDER_H

#include "ance/core/Location.h"

#include "ance/bbt/Node.h"

namespace ance::core
{
    class Identifier;
}

namespace ance::bbt
{
    class Value;
    class TypeContext;
}

namespace ance::bbt
{
    /// Helps to build instances of flow.
    class FlowBuilder
    {
      public:
        FlowBuilder(core::Location const& location, TypeContext& type_context);
        ~FlowBuilder();

        /// Creates a new basic block and returns its ID.
        size_t createBasicBlock();

        /// Sets the currently active basic block to the one with the given ID.
        void setActiveBasicBlock(size_t id);

        /// Pushes a statement to the currently active basic block.
        void pushStatement(utility::Owned<Statement> statement);

        /// Pushes a statement to create a new temporary variable to the currently active basic block and returns the created temporary.
        Temporary const& pushTemporary(std::string id);

        /// Pushes the statements needed to resolve and access a variable with the given name to the currently active basic block and returns the temporary holding the access result.
        Temporary const& pushVariableAccess(core::Identifier const& name);

        /// Pushes the statements needed to create a constant value to the currently active basic block and returns the temporary holding the value.
        Temporary const& pushConstant(utility::Shared<Value> value);

        /// Builds the flow from the added basic blocks and statements.
        utility::Owned<Flow> build(std::string id);

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };

}

#endif
