#include "tree/Definition.h"

[[maybe_unused]] static tree::Definition ast =
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
        .node(
            "MatchExpressionCase",
            "A case of a match expression. Has a set of patterns, or no patterns if "
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
                node.owned("Expression", "result");
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
            "Declarations are nodes that introduce named entities and are used in "
            "unordered scopes.",
            [](auto& category) {
                category
                    .node(
                        "ErrorDeclaration",
                        "A declaration that could not be parsed correctly.",
                        [](auto&) {}
                    )
                    .node(
                        "RunnableDeclaration",
                        "Declares a statement to be run in an unordered scope.",
                        [](auto& node) { node.owned("Statement", "body"); }
                    )
                    .node(
                        "NameDeclaration",
                        "A name declaration in an unordered scope.",
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
                        }
                    )
                    .node(
                        "FunctionDeclaration",
                        "A function declaration in an unordered scope.",
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
                            node.owned(
                                "Parameter",
                                "parameters",
                                tree::Definition::Multiplicity::ZERO_OR_MORE
                            );
                            node.owned(
                                "Expression",
                                "return_type",
                                tree::Definition::Multiplicity::ZERO_OR_ONE
                            );
                            node.owned("Statement", "body");
                        }
                    );
            }
        )
        .category(
            "Statement",
            "A statement is an independent part of code.",
            [](auto& category) {
                category.method("[[nodiscard]] virtual bool isCompound() const");

                category
                    .node(
                        "ErrorStatement",
                        "A statement that could not be parsed correctly.",
                        [](auto&) {}
                    )
                    .node(
                        "Block",
                        "A block statement combines multiple statements into a single "
                        "statement, creating a new ordered scope.",
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
                        "An independent expression statement is a statement that "
                        "consists of a single expression.",
                        [](auto& node) { node.owned("Expression", "expression"); }
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
                        "An if-statement chooses one of two statements to execute "
                        "based on a condition. The second statement is optional.",
                        [](auto& node) {
                            node.owned("Expression", "condition");
                            node.owned("Statement", "true_part");
                            node.owned(
                                "Statement",
                                "false_part",
                                tree::Definition::Multiplicity::ZERO_OR_ONE
                            );
                        }
                    )
                    .node(
                        "Loop",
                        "Unconditionally repeats a statement.",
                        [](auto& node) { node.owned("Statement", "body"); }
                    )
                    .node(
                        "Break",
                        "Breaks out of the innermost containing loop.",
                        [](auto&) {}
                    )
                    .node(
                        "Continue",
                        "Begins a new iteration of the innermost containing loop.",
                        [](auto&) {}
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
                        "While",
                        "Loops as long as the condition is true.",
                        [](auto& node) {
                            node.owned("Expression", "condition");
                            node.owned("Statement", "body");
                        }
                    )
                    .node(
                        "Match",
                        "Matches an expression against a series of patterns and executes "
                        "the code of the first matching pattern.",
                        [](auto& node) {
                            node.owned("Expression", "condition");
                            node.owned(
                                "MatchCase",
                                "cases",
                                tree::Definition::Multiplicity::ZERO_OR_MORE
                            );
                        }
                    )
                    .node(
                        "Erase",
                        "Erases a variable from the current scope, making it "
                        "inaccessible "
                        "and causing destruction.",
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
        .category(
            "Expression",
            "An expression is a piece of code that produces a value.",
            [](auto& category) {
                category
                    .node(
                        "ErrorExpression",
                        "An expression that could not be parsed correctly.",
                        [](auto&) {}
                    )
                    .node(
                        "And",
                        "Logical, short-circuiting and-expression. Can be negated to "
                        "create a nand-expression.",
                        [](auto& node) {
                            node.owned("Expression", "left");
                            node.attribute(
                                tree::Definition::AttributeType::BOOL,
                                "negated"
                            );
                            node.owned("Expression", "right");
                        }
                    )
                    .node(
                        "Or",
                        "Logical, short-circuiting or-expression. Can be negated to "
                        "create a nor-expression.",
                        [](auto& node) {
                            node.owned("Expression", "left");
                            node.attribute(
                                tree::Definition::AttributeType::BOOL,
                                "negated"
                            );
                            node.owned("Expression", "right");
                        }
                    )
                    .node(
                        "Call",
                        "A call is an expression that performs the call-operator on a "
                        "callable entity.",
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
                    .node(
                        "Lambda",
                        "A lambda expression creates an anonymous function.",
                        [](auto& node) {
                            node.owned(
                                "Parameter",
                                "parameters",
                                tree::Definition::Multiplicity::ZERO_OR_MORE
                            );
                            node.owned(
                                "Expression",
                                "return_type",
                                tree::Definition::Multiplicity::ZERO_OR_ONE
                            );
                            node.owned(
                                "Expression",
                                "expression_body",
                                tree::Definition::Multiplicity::ZERO_OR_ONE
                            );
                            node.owned(
                                "Statement",
                                "statement_body",
                                tree::Definition::Multiplicity::ZERO_OR_ONE
                            );
                        }
                    )
                    .node(
                        "Access",
                        "Access is an expression that reads the value of a named entity.",
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
                            node.attribute(
                                tree::Definition::AttributeType::STRING,
                                "value"
                            );
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
                            node.attribute(
                                tree::Definition::AttributeType::STRING,
                                "value"
                            );
                        }
                    )
                    .node(
                        "StringLiteral",
                        "A literal for a string value.",
                        [](auto& node) {
                            node.attribute(
                                tree::Definition::AttributeType::STRING,
                                "value"
                            );
                        }
                    )
                    .node(
                        "BoolLiteral",
                        "A literal for a boolean value.",
                        [](auto& node) {
                            node.attribute(
                                tree::Definition::AttributeType::BOOL,
                                "value"
                            );
                        }
                    )
                    .node(
                        "Intrinsic",
                        "An expression that calls an intrinsic by name.",
                        [](auto& node) {
                            node.owned("Expression", "name");
                            node.owned(
                                "Expression",
                                "arguments",
                                tree::Definition::Multiplicity::ZERO_OR_MORE
                            );
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
                            node.owned(
                                "Expression",
                                "result",
                                tree::Definition::Multiplicity::ZERO_OR_ONE
                            );
                        }
                    )
                    .node(
                        "Parenthesis",
                        "An expression wrapped in parentheses.",
                        [](auto& node) { node.owned("Expression", "contained"); }
                    )
                    .node(
                        "Here",
                        "An expression that resolves to its own source location.",
                        [](auto&) {}
                    )
                    .node(
                        "IfExpression",
                        "An expression that evaluates to one of two expressions based "
                        "on a condition.",
                        [](auto& node) {
                            node.owned("Expression", "condition");
                            node.owned("Expression", "then_expression");
                            node.owned("Expression", "else_expression");
                        }
                    )
                    .node(
                        "MatchExpression",
                        "An expression that evaluates to one of several expressions "
                        "based "
                        "on a condition.",
                        [](auto& node) {
                            node.owned("Expression", "condition");
                            node.owned(
                                "MatchExpressionCase",
                                "cases",
                                tree::Definition::Multiplicity::ZERO_OR_MORE
                            );
                        }
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
                    );
            }
        );
