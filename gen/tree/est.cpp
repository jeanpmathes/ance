#include "tree/Definition.h"

[[maybe_unused]] static tree::Definition est =
    tree::Definition::create()
        .node(
            "File",
            "Represents a source file creating an unordered scope. Note that actual "
            "source files may contain a top-level ordered scope, which would be "
            "represented as a statement node instead of a file node.",
            [](auto& node) {
                node.owned(
                    "Declaration",
                    "declarations",
                    tree::Definition::Multiplicity::ZERO_OR_MORE
                );
            }
        )
        .node(
            "MatchCase",
            "A case of a match statement. Has a set of patterns, or no patterns if "
            "it is the default case.",
            [](auto& node) {
                node.owned(
                    "Expression",
                    "patterns",
                    tree::Definition::Multiplicity::ZERO_OR_MORE
                );
                // todo: make default a pattern with an actual node, then no special field is needed
                node.attribute(
                    tree::Definition::AttributeType::LOCATION,
                    "default_pattern_location"
                );
                node.owned("Statement", "body");
            }
        )
        // todo: make this a node, make it visitable, use that in visitors
        .node(
            "Parameter",
            "A parameter for a callable, e.g. a function or lambda.",
            [](auto& node) {
                node.attribute(tree::Definition::AttributeType::IDENTIFIER, "identifier");
                node.owned("Expression", "type");
            }
        )
        .category(
            "Declaration",
            "Base class for all declaration nodes in the EST.",
            [](auto& category) {
                category.method(
                    "[[nodiscard]] virtual std::string displayName() const",
                    true
                );

                category
                    .node(
                        "RunnableDeclaration",
                        "A runnable declaration runs a statement in an unordered "
                        "scope.",
                        [](auto& node) {
                            node.owned("Statement", "body");
                            node.method(
                                "[[nodiscard]] std::string displayName() const override"
                            );
                        }
                    )
                    .node(
                        "NameDeclaration",
                        "Declares a name in an unordered scope.",
                        [](auto& node) {
                            node.attribute(
                                tree::Definition::AttributeType::ACCESS_MODIFIER,
                                "access_modifier"
                            );
                            node.attribute(
                                tree::Definition::AttributeType::EXECUTION_MODIFIER,
                                "execution_modifier"
                            );
                            node.attribute(
                                tree::Definition::AttributeType::IDENTIFIER,
                                "identifier"
                            );
                            node.owned("Expression", "type");
                            node.attribute(
                                tree::Definition::AttributeType::ASSIGNER,
                                "assigner"
                            );
                            node.owned(
                                "Expression",
                                "value",
                                tree::Definition::Multiplicity::ZERO_OR_ONE
                            );
                            node.method(
                                "[[nodiscard]] std::string displayName() const override"
                            );
                        }
                    );
            }
        )
        .category(
            "Statement",
            "Statement node in the EST.",
            [](auto& category) {
                category.method("[[nodiscard]] virtual bool isCompound() const");

                category
                    .node(
                        "ErrorStatement",
                        "Error statement, mostly as pass-through from the AST.",
                        [](auto&) {}
                    )
                    .node("Pass", "Pass statement, a no-op.", [](auto&) {})
                    .node(
                        "Block",
                        "Block statement, containing multiple statements.",
                        [](auto& node) {
                            node.owned(
                                "Statement",
                                "statements",
                                tree::Definition::Multiplicity::ZERO_OR_MORE
                            );
                            node.method("[[nodiscard]] bool isCompound() const override");
                        }
                    )
                    .node(
                        "Independent",
                        "Statement that simply wraps an expression, discarding its "
                        "result.",
                        [](auto& node) { node.owned("Expression", "expression"); }
                    )
                    .node(
                        "Assignment",
                        "An assignment statement assigns a value to an assignable.",
                        [](auto& node) {
                            node.owned("Expression", "assignee");
                            node.attribute(
                                tree::Definition::AttributeType::ASSIGNER,
                                "assigner"
                            );
                            node.owned("Expression", "value");
                        }
                    )
                    .node(
                        "If",
                        "An if-statement chooses one of two blocks to execute based on a "
                        "condition.",
                        [](auto& node) {
                            node.owned("Expression", "condition");
                            node.owned("Statement", "true_block");
                            node.owned("Statement", "false_block");
                        }
                    )
                    .node(
                        "Loop",
                        "A loop statement executes a block of code repeatedly and "
                        "unconditionally.",
                        [](auto& node) { node.owned("Statement", "body"); }
                    )
                    .node(
                        "Break",
                        "Break statement exits the nearest enclosing loop.",
                        [](auto&) {}
                    )
                    .node(
                        "Continue",
                        "Continue statement continues the nearest enclosing loop.",
                        [](auto&) {}
                    )
                    .node(
                        "Match",
                        "Matches an expression against a series of patterns and executes "
                        "the code of the first matching pattern.",
                        [](auto& node) {
                            node.owned("Expression", "value");
                            node.owned(
                                "MatchCase",
                                "cases",
                                tree::Definition::Multiplicity::ZERO_OR_MORE
                            );
                        }
                    )
                    .node(
                        "Return",
                        "Returns from the current runnable, optionally with a value.",
                        [](auto& node) {
                            node.owned(
                                "Expression",
                                "value",
                                tree::Definition::Multiplicity::ZERO_OR_ONE
                            );
                        }
                    )
                    .node(
                        "Bind",
                        "A bind statement binds a value to a name in a local scope as a "
                        "variable or constant, or simply prepares the binding of a name.",
                        [](auto& node) {
                            node.attribute(
                                tree::Definition::AttributeType::IDENTIFIER,
                                "identifier"
                            );
                            node.attribute(
                                tree::Definition::AttributeType::VARIABILITY_MODIFIER,
                                "variability"
                            );
                            node.owned("Expression", "type");
                            node.attribute(
                                tree::Definition::AttributeType::ASSIGNER,
                                "assigner"
                            );
                            node.owned(
                                "Expression",
                                "value",
                                tree::Definition::Multiplicity::ZERO_OR_ONE
                            );
                        }
                    )
                    .node(
                        "Erase",
                        "Erases a variable from the current scope, making it "
                        "inaccessible and causing destruction.",
                        [](auto& node) {
                            node.attribute(
                                tree::Definition::AttributeType::IDENTIFIER,
                                "identifier"
                            );
                        }
                    )
                    .node(
                        "Assert",
                        "Asserts that a condition is true. If not, execution is stopped.",
                        [](auto& node) { node.owned("Expression", "condition"); }
                    );
            }
        )
        .category("Expression", "Expression node in the EST.", [](auto& category) {
            category
                .node(
                    "ErrorExpression",
                    "Error expression, mostly as pass-through from the AST.",
                    [](auto&) {}
                )
                .node(
                    "Intrinsic",
                    "An intrinsic expression, calling an intrinsic specified by a "
                    "string.",
                    [](auto& node) {
                        node.owned("Expression", "name");
                        node.owned(
                            "Expression",
                            "arguments",
                            tree::Definition::Multiplicity::ZERO_OR_MORE
                        );
                    }
                )
                .node(
                    "BlockExpression",
                    "An expression that combines a sequence of statements with a "
                    "final expression inside an ordered scope.",
                    [](auto& node) {
                        node.owned(
                            "Statement",
                            "statements",
                            tree::Definition::Multiplicity::ZERO_OR_MORE
                        );
                        node.owned("Expression", "result");
                    }
                )
                .node(
                    "Parenthesis",
                    "An expression wrapped in parentheses.",
                    [](auto& node) { node.owned("Expression", "contained"); }
                )
                .node(
                    "Call",
                    "A call expression.",
                    [](auto& node) {
                        node.owned("Expression", "callee");
                        node.owned(
                            "Expression",
                            "arguments",
                            tree::Definition::Multiplicity::ZERO_OR_MORE
                        );
                    }
                )
                .node(
                    "Subscript",
                    "A subscript expression accesses an element using an index.",
                    [](auto& node) {
                        node.owned("Expression", "indexed");
                        node.owned("Expression", "index");
                    }
                )
                // todo: make this an actual constructor of function types
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
                        node.owned("Expression", "return_type");
                        node.owned("Statement", "body");
                    }
                )
                .node(
                    "Access",
                    "Accesses a variable by identifier.",
                    [](auto& node) {
                        node.attribute(
                            tree::Definition::AttributeType::IDENTIFIER,
                            "identifier"
                        );
                    }
                )
                .node("UnitLiteral", "A literal for the unit value.", [](auto&) {})
                .node(
                    "SizeLiteral",
                    "A literal for a value of the size type.",
                    [](auto& node) {
                        node.attribute(tree::Definition::AttributeType::STRING, "value");
                    }
                )
                .node(
                    "FloatingPointLiteral",
                    "A literal for a value of the floating point types.",
                    [](auto& node) {
                        node.attribute(
                            tree::Definition::AttributeType::PRECISION,
                            "precision"
                        );
                        node.attribute(tree::Definition::AttributeType::STRING, "value");
                    }
                )
                .node(
                    "StringLiteral",
                    "A literal for a string value.",
                    [](auto& node) {
                        node.attribute(tree::Definition::AttributeType::STRING, "value");
                    }
                )
                .node(
                    "BoolLiteral",
                    "A literal for a boolean value.",
                    [](auto& node) {
                        node.attribute(tree::Definition::AttributeType::BOOL, "value");
                    }
                )
                .node(
                    "Default",
                    "Provides the default value for a type.",
                    [](auto& node) { node.owned("Expression", "type"); }
                )
                .node(
                    "Here",
                    "Expression providing the current source location.",
                    [](auto&) {}
                )
                .node(
                    "UnaryOperation",
                    "Applies an operation to an operand.",
                    [](auto& node) {
                        node.attribute(
                            tree::Definition::AttributeType::UNARY_OPERATOR,
                            "op"
                        );
                        node.owned("Expression", "operand");
                    }
                )
                .node(
                    "BinaryOperation",
                    "Applies a binary operation to two operands.",
                    [](auto& node) {
                        node.owned("Expression", "left");
                        node.attribute(
                            tree::Definition::AttributeType::BINARY_OPERATOR,
                            "op"
                        );
                        node.owned("Expression", "right");
                    }
                )
                // todo: should no longer evaluate the expressions
                .node(
                    "TypeOf",
                    "Gives the common type of the values produced by the "
                    "expressions - the expressions WILL BE evaluated.",
                    [](auto& node) {
                        node.owned(
                            "Expression",
                            "expressions",
                            tree::Definition::Multiplicity::ZERO_OR_MORE
                        );
                    }
                )
                .node(
                    "ArrayTypeConstructor",
                    "An expression that constructs an array type. The array type has "
                    "a fixed length and element type.",
                    [](auto& node) {
                        node.owned("Expression", "element_type");
                        node.owned("Expression", "length");
                    }
                )
                .node(
                    "ArrayConstructor",
                    "An expression that creates an array value. Could also be "
                    "called an array literal.",
                    [](auto& node) {
                        node.owned(
                            "Expression",
                            "element_type",
                            tree::Definition::Multiplicity::ZERO_OR_ONE
                        );
                        node.owned(
                            "Expression",
                            "elements",
                            tree::Definition::Multiplicity::ZERO_OR_MORE
                        );
                    }
                );
        });
