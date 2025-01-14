export module ast;

export namespace ance::ast
{
    /**
     * Base class for all nodes in the AST.
     */
    class Node
    {
    };

    /**
     * A statement is an independent part of code.
     */
    class Statement : public Node
    {
    };

    /**
     * A block statement combines multiple statements into a single statement.
     */
    class BlockStatement : public Statement
    {
    };

    /**
     * An expression statement is a statement that consists of a single expression.
     */
    class ExpressionStatement : public Statement
    {
    };

    /**
     * An expression is a piece of code that produces a value.
     */
    class Expression : public Node
    {
    };

    /**
     * A function call is an expression that calls a function.
     */
    class FunctionCall : public Expression
    {
    };

    /**
     * Parses files into ASTs.
     */
    class Parser
    {
        // todo: declare an NodeVisitor class that visits nodes in the AST using the visitor template
        // todo: the parser class should use the antlr4 visitor to create the ast
        // todo: that should handle fault tolerance - check what old does but do not fail on errors, instead handle by checking the antlr4 ctx objects and return error nodes
        // todo: cause compiler errors (create a reporter class, should take source file)
        // todo: the parser needs the following method: parse(std::filesystem::path const& file_path) -> std::unique_ptr<Statement>
    };
}
