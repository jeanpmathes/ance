#include "tree/Definition.h"

[[maybe_unused]] static tree::Definition bbt =
    tree::Definition::create()
        .node(
            "Flows",
            "A set of flows, e.g. all flows of a file.",
            [](auto& node) {
                node.owned("Flow", "flows", tree::Definition::Multiplicity::ZERO_OR_MORE);
            }
        )
        .node(
            "UnorderedScope",
            "An unordered scope contains a set of parts which are evaluated in an "
            "unspecified order. An example of an unordered scope is the scope in "
            "which the flows of all files are placed, which is the project scope.",
            [](auto& node) {
                node.owned("Flow", "flows", tree::Definition::Multiplicity::ZERO_OR_MORE);
            }
        )
        .node(
            "Flow",
            "The flow node represents a complete control flow build up by a set of "
            "basic blocks.",
            [](auto& node) {
                node.owned(
                    "BasicBlock",
                    "blocks",
                    tree::Definition::Multiplicity::ZERO_OR_MORE
                );
                node.reference(
                    "BasicBlock",
                    "entry",
                    tree::Definition::Multiplicity::ONE,
                    false
                );
                node.attribute(tree::Definition::AttributeType::STRING, "identifier");
                node.attribute(
                    tree::Definition::AttributeType::OCCURRENCE,
                    "explicit_return_value_occurrence"
                );
                node.method("[[nodiscard]] std::string id() const");
            }
        )
        .node(
            "BasicBlock",
            "A basic block is a sequence of statements that are executed without "
            "interruption. Control flow can be set up between basic blocks.",
            [](auto& node) {
                node.attribute(tree::Definition::AttributeType::SIZE, "id");
                node.owned(
                    "Statement",
                    "statements",
                    tree::Definition::Multiplicity::ZERO_OR_MORE
                );
                node.owned("Link", "link");
            }
        )
        // todo: do not forget that the patterns should become compiletime-only at some point
        // todo: then we could have a pattern node type, and default would become an actual node, and we would not need the pattern location here and all the other nodes as a separate field
        .node(
            "SwitchCase",
            "A case of a switch link. Has either a single pattern or no patterns if "
            "it matches everything.",
            [](auto& node) {
                node.attribute(
                    tree::Definition::AttributeType::LOCATION,
                    "pattern_location"
                );
                node.reference(
                    "Temporary",
                    "pattern",
                    tree::Definition::Multiplicity::ZERO_OR_ONE
                );
                node.reference("BasicBlock", "target");
            }
        )
        // todo: make this a node, make it visitable, use that in visitors
        .node(
            "Parameter",
            "A parameter for a callable, e.g. a function or lambda.",
            [](auto& node) {
                node.attribute(tree::Definition::AttributeType::IDENTIFIER, "identifier");
                node.reference("Temporary", "type");
            }
        )
        .category(
            "Link",
            "Describes how control flow is passed between basic blocks.",
            [](auto& category) {
                category
                    .node(
                        "ErrorLink",
                        "The error link is used to represent an error in the "
                        "control flow.",
                        [](auto&) {}
                    )
                    .node(
                        "Return",
                        "The return link ends the current function, not linking to "
                        "any other basic block. The link cannot set a return value, "
                        "for this the SetReturnValue statement is used.",
                        [](auto&) {}
                    )
                    .node(
                        "Branch",
                        "Chooses between two branches based on a condition.",
                        [](auto& node) {
                            node.reference("Temporary", "condition");
                            node.reference("BasicBlock", "true_branch");
                            node.reference("BasicBlock", "false_branch");
                        }
                    )
                    .node(
                        "Jump",
                        "A simple and direct jump to a block.",
                        [](auto& node) { node.reference("BasicBlock", "target"); }
                    )
                    .node(
                        "Switch",
                        "Matches a value against a series of cases and jumps to the "
                        "block corresponding to the first matching case.",
                        [](auto& node) {
                            node.reference("Temporary", "condition");
                            node.owned(
                                "SwitchCase",
                                "cases",
                                tree::Definition::Multiplicity::ZERO_OR_MORE
                            );
                        }
                    );
            }
        )
        .category("Statement", "Statement node in the BBT.", [](auto& category) {
            category.method(
                "[[nodiscard]] virtual bool isRelevantForReachability() const"
            );

            category
                .node(
                    "ErrorStatement",
                    "Error statement, mostly as pass-through from the AST.",
                    [](auto&) {}
                )
                .node("Pass", "Pass statement, a no-op.", [](auto&) {})
                .node(
                    "Assert",
                    "Asserts that a condition is true. If not, execution is "
                    "stopped.",
                    [](auto& node) { node.reference("Temporary", "condition"); }
                )
                .node(
                    "Store",
                    "Stores a value to a variable reference.",
                    [](auto& node) {
                        node.reference("Temporary", "target");
                        node.reference("Temporary", "value");
                    }
                )
                .node(
                    "Access",
                    "Provides a reference to a variable.",
                    [](auto& node) {
                        node.reference("Temporary", "variable");
                        node.reference("Temporary", "destination");
                    }
                )
                .node(
                    "Temporary",
                    "Introduce a temporary variable, which works similar to any "
                    "other local variable but does not have a name it is bound to. "
                    "Temporaries live within the local scope they are defined in.",
                    [](auto& node) {
                        node.attribute(
                            tree::Definition::AttributeType::STRING,
                            "identifier"
                        );
                        node.method("[[nodiscard]] std::string id() const");
                    }
                )
                .node(
                    "Dereference",
                    "Dereferences a value, unwrapping every reference until a "
                    "concrete value is reached.",
                    [](auto& node) {
                        node.reference("Temporary", "target");
                        node.reference("Temporary", "destination");
                    }
                )
                .node(
                    "Intrinsic",
                    "Performs a compiler-provided operation like operators or "
                    "functions.",
                    [](auto& node) {
                        node.attribute(
                            tree::Definition::AttributeType::INTRINSIC,
                            "intrinsic"
                        );
                        node.reference(
                            "Temporary",
                            "arguments",
                            tree::Definition::Multiplicity::ZERO_OR_MORE
                        );
                        node.reference("Temporary", "destination");
                    }
                )
                .node(
                    "Call",
                    "Calls a function.",
                    [](auto& node) {
                        node.reference("Temporary", "called");
                        node.reference(
                            "Temporary",
                            "arguments",
                            tree::Definition::Multiplicity::ZERO_OR_MORE
                        );
                        node.reference("Temporary", "destination");
                    }
                )
                .node(
                    "Subscript",
                    "Accesses a value by a given index.",
                    [](auto& node) {
                        node.reference("Temporary", "indexed");
                        node.reference("Temporary", "index");
                        node.reference("Temporary", "destination");
                    }
                )
                // todo: remove when actual function constructors exist
                .node(
                    "FunctionConstructor",
                    "Creates a function.",
                    [](auto& node) {
                        node.attribute(
                            tree::Definition::AttributeType::IDENTIFIER,
                            "name"
                        );
                        node.owned(
                            "Parameter",
                            "parameters",
                            tree::Definition::Multiplicity::ZERO_OR_MORE
                        );
                        node.reference("Temporary", "return_type");
                        node.owned("Flow", "body");
                        node.reference("Temporary", "destination");
                    }
                )
                .node(
                    "Constant",
                    "A constant value.",
                    [](auto& node) {
                        node.owned(
                            "Value",
                            "value",
                            tree::Definition::Multiplicity::ONE,
                            true
                        );
                        node.reference("Temporary", "destination");
                    }
                )
                .node(
                    "Default",
                    "Provides the default value for a type.",
                    [](auto& node) {
                        node.reference("Temporary", "type");
                        node.reference("Temporary", "destination");
                    }
                )
                .node(
                    "CurrentScope",
                    "Writes the current scope to the destination temporary.",
                    [](auto& node) { node.reference("Temporary", "destination"); }
                )
                // todo: ugly, see comments at GetBinaryOperatorFunctionIdentifier
                .node(
                    "GetUnaryOperatorFunctionIdentifier",
                    "Retrieves the operator function identifier for a unary "
                    "operation from the operand type.",
                    [](auto& node) {
                        node.attribute(
                            tree::Definition::AttributeType::UNARY_OPERATOR,
                            "op"
                        );
                        node.reference("Temporary", "type");
                        node.reference("Temporary", "destination");
                    }
                )
                // todo: unify this with member function access as soon as those are added, consider whether this should be an intrinsic instead or use a completely different approach
                // todo: I really feel that this is ugly, and should rather be an intrinsic
                // todo: maybe it should not be an intrinsic and instead be something along the lines of GEP just for members
                // todo: it would be reworked to a simple GetMember where just the operator would be passed in and then standard overload resolution, which would also mean there would be no separate GetUnaryOperatorFunctionIdentifier
                .node(
                    "GetBinaryOperatorFunctionIdentifier",
                    "Retrieves the operator function identifier for a binary "
                    "operation from the left operand's type.",
                    [](auto& node) {
                        node.attribute(
                            tree::Definition::AttributeType::BINARY_OPERATOR,
                            "op"
                        );
                        node.reference("Temporary", "left_type");
                        node.reference("Temporary", "right_type");
                        node.reference("Temporary", "destination");
                    }
                )
                // todo: should no longer evaluate the expressions
                .node(
                    "TypeOf",
                    "Finds the common type of all provided values.",
                    [](auto& node) {
                        node.reference(
                            "Temporary",
                            "values",
                            tree::Definition::Multiplicity::ZERO_OR_MORE
                        );
                        node.reference("Temporary", "destination");
                    }
                )
                .node(
                    "ArrayTypeConstructor",
                    "An expression that constructs an array type. The array type has "
                    "a fixed length and element type.",
                    [](auto& node) {
                        node.reference("Temporary", "element_type");
                        node.reference("Temporary", "length");
                        node.reference("Temporary", "destination");
                    }
                )
                .node(
                    "ArrayConstructor",
                    "Creates an array value from an optional element type and "
                    "elements. Could also be called an array literal.",
                    [](auto& node) {
                        node.reference(
                            "Temporary",
                            "element_type",
                            tree::Definition::Multiplicity::ZERO_OR_ONE
                        );
                        node.reference(
                            "Temporary",
                            "elements",
                            tree::Definition::Multiplicity::ZERO_OR_MORE
                        );
                        node.reference("Temporary", "destination");
                    }
                )
                .node(
                    "OrderedScopeEnter",
                    "Enters an ordered scope, which is used to manage variable "
                    "lifetimes and visibility.",
                    [](auto& node) {
                        node.method(
                            "[[nodiscard]] bool isRelevantForReachability() const "
                            "override"
                        );
                    }
                )
                .node(
                    "OrderedScopeExit",
                    "Exits an ordered scope, which is used to manage variable "
                    "lifetimes and visibility.",
                    [](auto& node) {
                        node.reference("OrderedScopeEnter", "enter");
                        node.method(
                            "[[nodiscard]] bool isRelevantForReachability() const "
                            "override"
                        );
                    }
                )
                .node(
                    "SetReturnValue",
                    "Set the return value of the current function. This may only "
                    "be called at most once per function execution. The statement "
                    "is necessary to allow persisting the return value even after "
                    "all scopes and their temporaries have been destroyed.",
                    [](auto& node) { node.reference("Temporary", "value"); }
                );
        });
