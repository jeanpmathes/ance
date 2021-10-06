
// Generated from ./src/grammar/ance.g4 by ANTLR 4.8

#include "anceVisitor.h"

#include "anceParser.h"

using namespace antlrcpp;
using namespace antlr4;

anceParser::anceParser(TokenStream* input) : Parser(input)
{
    _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

anceParser::~anceParser()
{
    delete _interpreter;
}

std::string anceParser::getGrammarFileName() const
{
    return "ance.g4";
}

const std::vector<std::string>& anceParser::getRuleNames() const
{
    return _ruleNames;
}

dfa::Vocabulary& anceParser::getVocabulary() const
{
    return _vocabulary;
}

//----------------- FileContext ------------------------------------------------------------------

anceParser::FileContext::FileContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::FileContext::EOF()
{
    return getToken(anceParser::EOF, 0);
}

std::vector<anceParser::VariableDeclarationContext*> anceParser::FileContext::variableDeclaration()
{
    return getRuleContexts<anceParser::VariableDeclarationContext>();
}

anceParser::VariableDeclarationContext* anceParser::FileContext::variableDeclaration(size_t i)
{
    return getRuleContext<anceParser::VariableDeclarationContext>(i);
}

std::vector<anceParser::FunctionContext*> anceParser::FileContext::function()
{
    return getRuleContexts<anceParser::FunctionContext>();
}

anceParser::FunctionContext* anceParser::FileContext::function(size_t i)
{
    return getRuleContext<anceParser::FunctionContext>(i);
}

size_t anceParser::FileContext::getRuleIndex() const
{
    return anceParser::RuleFile;
}

antlrcpp::Any anceParser::FileContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitFile(this);
    else
        return visitor->visitChildren(this);
}

anceParser::FileContext* anceParser::file()
{
    FileContext* _localctx = _tracker.createInstance<FileContext>(_ctx, getState());
    enterRule(_localctx, 0, anceParser::RuleFile);
    size_t _la = 0;

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(96);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (
            (((_la & ~0x3fULL) == 0)
             && ((1ULL << _la) & ((1ULL << anceParser::T__4) | (1ULL << anceParser::T__6) | (1ULL << anceParser::T__7)))
                    != 0))
        {
            setState(94);
            _errHandler->sync(this);
            switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx))
            {
                case 1:
                {
                    setState(92);
                    variableDeclaration();
                    break;
                }

                case 2:
                {
                    setState(93);
                    function();
                    break;
                }
            }
            setState(98);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(99);
        match(anceParser::EOF);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

anceParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::AccessModifierContext* anceParser::VariableDeclarationContext::accessModifier()
{
    return getRuleContext<anceParser::AccessModifierContext>(0);
}

anceParser::TypeContext* anceParser::VariableDeclarationContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::VariableDeclarationContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::VariableDeclarationContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

tree::TerminalNode* anceParser::VariableDeclarationContext::CONST()
{
    return getToken(anceParser::CONST, 0);
}

anceParser::AssignerContext* anceParser::VariableDeclarationContext::assigner()
{
    return getRuleContext<anceParser::AssignerContext>(0);
}

anceParser::LiteralExpressionContext* anceParser::VariableDeclarationContext::literalExpression()
{
    return getRuleContext<anceParser::LiteralExpressionContext>(0);
}

size_t anceParser::VariableDeclarationContext::getRuleIndex() const
{
    return anceParser::RuleVariableDeclaration;
}

antlrcpp::Any anceParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitVariableDeclaration(this);
    else
        return visitor->visitChildren(this);
}

anceParser::VariableDeclarationContext* anceParser::variableDeclaration()
{
    VariableDeclarationContext* _localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
    enterRule(_localctx, 2, anceParser::RuleVariableDeclaration);
    size_t _la = 0;

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(101);
        accessModifier();
        setState(103);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::CONST)
        {
            setState(102);
            match(anceParser::CONST);
        }
        setState(105);
        type();
        setState(106);
        match(anceParser::IDENTIFIER);
        setState(110);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0)
             && ((1ULL << _la)
                 & ((1ULL << anceParser::T__12) | (1ULL << anceParser::T__13) | (1ULL << anceParser::T__14)))
                    != 0))
        {
            setState(107);
            assigner();
            setState(108);
            literalExpression();
        }
        setState(112);
        match(anceParser::SEMICOLON);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FunctionContext ------------------------------------------------------------------

anceParser::FunctionContext::FunctionContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::FunctionContext::getRuleIndex() const
{
    return anceParser::RuleFunction;
}

void anceParser::FunctionContext::copyFrom(FunctionContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- ExternFunctionDeclarationContext ------------------------------------------------------------------

anceParser::TypeContext* anceParser::ExternFunctionDeclarationContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::ExternFunctionDeclarationContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::ParametersContext* anceParser::ExternFunctionDeclarationContext::parameters()
{
    return getRuleContext<anceParser::ParametersContext>(0);
}

tree::TerminalNode* anceParser::ExternFunctionDeclarationContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

anceParser::ExternFunctionDeclarationContext::ExternFunctionDeclarationContext(FunctionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::ExternFunctionDeclarationContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitExternFunctionDeclaration(this);
    else
        return visitor->visitChildren(this);
}
//----------------- FunctionDefinitionContext ------------------------------------------------------------------

anceParser::AccessModifierContext* anceParser::FunctionDefinitionContext::accessModifier()
{
    return getRuleContext<anceParser::AccessModifierContext>(0);
}

anceParser::TypeContext* anceParser::FunctionDefinitionContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::FunctionDefinitionContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::ParametersContext* anceParser::FunctionDefinitionContext::parameters()
{
    return getRuleContext<anceParser::ParametersContext>(0);
}

std::vector<anceParser::StatementContext*> anceParser::FunctionDefinitionContext::statement()
{
    return getRuleContexts<anceParser::StatementContext>();
}

anceParser::StatementContext* anceParser::FunctionDefinitionContext::statement(size_t i)
{
    return getRuleContext<anceParser::StatementContext>(i);
}

anceParser::FunctionDefinitionContext::FunctionDefinitionContext(FunctionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitFunctionDefinition(this);
    else
        return visitor->visitChildren(this);
}
anceParser::FunctionContext* anceParser::function()
{
    FunctionContext* _localctx = _tracker.createInstance<FunctionContext>(_ctx, getState());
    enterRule(_localctx, 4, anceParser::RuleFunction);
    size_t _la = 0;

    auto onExit = finally([=] { exitRule(); });
    try
    {
        setState(137);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__6:
            case anceParser::T__7:
            {
                _localctx = dynamic_cast<FunctionContext*>(
                    _tracker.createInstance<anceParser::FunctionDefinitionContext>(_localctx));
                enterOuterAlt(_localctx, 1);
                setState(114);
                accessModifier();
                setState(115);
                type();
                setState(116);
                match(anceParser::IDENTIFIER);
                setState(117);
                match(anceParser::T__0);
                setState(118);
                parameters();
                setState(119);
                match(anceParser::T__1);
                setState(120);
                match(anceParser::T__2);
                setState(124);
                _errHandler->sync(this);
                _la = _input->LA(1);
                while ((((_la & ~0x3fULL) == 0)
                        && ((1ULL << _la)
                            & ((1ULL << anceParser::T__8) | (1ULL << anceParser::T__15) | (1ULL << anceParser::T__16)
                               | (1ULL << anceParser::T__17) | (1ULL << anceParser::T__26) | (1ULL << anceParser::T__27)
                               | (1ULL << anceParser::T__28) | (1ULL << anceParser::T__29) | (1ULL << anceParser::T__30)
                               | (1ULL << anceParser::T__31) | (1ULL << anceParser::T__32) | (1ULL << anceParser::T__33)
                               | (1ULL << anceParser::T__34) | (1ULL << anceParser::T__35)
                               | (1ULL << anceParser::NATIVE_INTEGER_TYPE) | (1ULL << anceParser::IDENTIFIER)))
                               != 0))
                {
                    setState(121);
                    statement();
                    setState(126);
                    _errHandler->sync(this);
                    _la = _input->LA(1);
                }
                setState(127);
                match(anceParser::T__3);
                break;
            }

            case anceParser::T__4:
            {
                _localctx = dynamic_cast<FunctionContext*>(
                    _tracker.createInstance<anceParser::ExternFunctionDeclarationContext>(_localctx));
                enterOuterAlt(_localctx, 2);
                setState(129);
                match(anceParser::T__4);
                setState(130);
                type();
                setState(131);
                match(anceParser::IDENTIFIER);
                setState(132);
                match(anceParser::T__0);
                setState(133);
                parameters();
                setState(134);
                match(anceParser::T__1);
                setState(135);
                match(anceParser::SEMICOLON);
                break;
            }

            default:
                throw NoViableAltException(this);
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ParametersContext ------------------------------------------------------------------

anceParser::ParametersContext::ParametersContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

std::vector<anceParser::ParameterContext*> anceParser::ParametersContext::parameter()
{
    return getRuleContexts<anceParser::ParameterContext>();
}

anceParser::ParameterContext* anceParser::ParametersContext::parameter(size_t i)
{
    return getRuleContext<anceParser::ParameterContext>(i);
}

size_t anceParser::ParametersContext::getRuleIndex() const
{
    return anceParser::RuleParameters;
}

antlrcpp::Any anceParser::ParametersContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitParameters(this);
    else
        return visitor->visitChildren(this);
}

anceParser::ParametersContext* anceParser::parameters()
{
    ParametersContext* _localctx = _tracker.createInstance<ParametersContext>(_ctx, getState());
    enterRule(_localctx, 6, anceParser::RuleParameters);
    size_t _la = 0;

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(147);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0)
             && ((1ULL << _la)
                 & ((1ULL << anceParser::T__17) | (1ULL << anceParser::T__26) | (1ULL << anceParser::T__27)
                    | (1ULL << anceParser::T__28) | (1ULL << anceParser::T__29) | (1ULL << anceParser::T__30)
                    | (1ULL << anceParser::T__31) | (1ULL << anceParser::T__32) | (1ULL << anceParser::T__33)
                    | (1ULL << anceParser::T__34) | (1ULL << anceParser::T__35)
                    | (1ULL << anceParser::NATIVE_INTEGER_TYPE)))
                    != 0))
        {
            setState(139);
            parameter();
            setState(144);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == anceParser::T__5)
            {
                setState(140);
                match(anceParser::T__5);
                setState(141);
                parameter();
                setState(146);
                _errHandler->sync(this);
                _la = _input->LA(1);
            }
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ParameterContext ------------------------------------------------------------------

anceParser::ParameterContext::ParameterContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::TypeContext* anceParser::ParameterContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::ParameterContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

size_t anceParser::ParameterContext::getRuleIndex() const
{
    return anceParser::RuleParameter;
}

antlrcpp::Any anceParser::ParameterContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitParameter(this);
    else
        return visitor->visitChildren(this);
}

anceParser::ParameterContext* anceParser::parameter()
{
    ParameterContext* _localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
    enterRule(_localctx, 8, anceParser::RuleParameter);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(149);
        type();
        setState(150);
        match(anceParser::IDENTIFIER);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- AccessModifierContext ------------------------------------------------------------------

anceParser::AccessModifierContext::AccessModifierContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::AccessModifierContext::getRuleIndex() const
{
    return anceParser::RuleAccessModifier;
}

void anceParser::AccessModifierContext::copyFrom(AccessModifierContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- PrivateContext ------------------------------------------------------------------

anceParser::PrivateContext::PrivateContext(AccessModifierContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::PrivateContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitPrivate(this);
    else
        return visitor->visitChildren(this);
}
//----------------- PublicContext ------------------------------------------------------------------

anceParser::PublicContext::PublicContext(AccessModifierContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::PublicContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitPublic(this);
    else
        return visitor->visitChildren(this);
}
anceParser::AccessModifierContext* anceParser::accessModifier()
{
    AccessModifierContext* _localctx = _tracker.createInstance<AccessModifierContext>(_ctx, getState());
    enterRule(_localctx, 10, anceParser::RuleAccessModifier);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        setState(154);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__6:
            {
                _localctx =
                    dynamic_cast<AccessModifierContext*>(_tracker.createInstance<anceParser::PublicContext>(_localctx));
                enterOuterAlt(_localctx, 1);
                setState(152);
                match(anceParser::T__6);
                break;
            }

            case anceParser::T__7:
            {
                _localctx = dynamic_cast<AccessModifierContext*>(
                    _tracker.createInstance<anceParser::PrivateContext>(_localctx));
                enterOuterAlt(_localctx, 2);
                setState(153);
                match(anceParser::T__7);
                break;
            }

            default:
                throw NoViableAltException(this);
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

anceParser::StatementContext::StatementContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::ExpressionStatementContext* anceParser::StatementContext::expressionStatement()
{
    return getRuleContext<anceParser::ExpressionStatementContext>(0);
}

anceParser::LocalVariableDefinitionContext* anceParser::StatementContext::localVariableDefinition()
{
    return getRuleContext<anceParser::LocalVariableDefinitionContext>(0);
}

anceParser::LocalReferenceDefinitionContext* anceParser::StatementContext::localReferenceDefinition()
{
    return getRuleContext<anceParser::LocalReferenceDefinitionContext>(0);
}

anceParser::AssignmentContext* anceParser::StatementContext::assignment()
{
    return getRuleContext<anceParser::AssignmentContext>(0);
}

anceParser::DeleteStatementContext* anceParser::StatementContext::deleteStatement()
{
    return getRuleContext<anceParser::DeleteStatementContext>(0);
}

anceParser::ReturnStatementContext* anceParser::StatementContext::returnStatement()
{
    return getRuleContext<anceParser::ReturnStatementContext>(0);
}

size_t anceParser::StatementContext::getRuleIndex() const
{
    return anceParser::RuleStatement;
}

antlrcpp::Any anceParser::StatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitStatement(this);
    else
        return visitor->visitChildren(this);
}

anceParser::StatementContext* anceParser::statement()
{
    StatementContext* _localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
    enterRule(_localctx, 12, anceParser::RuleStatement);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        setState(162);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx))
        {
            case 1:
            {
                enterOuterAlt(_localctx, 1);
                setState(156);
                expressionStatement();
                break;
            }

            case 2:
            {
                enterOuterAlt(_localctx, 2);
                setState(157);
                localVariableDefinition();
                break;
            }

            case 3:
            {
                enterOuterAlt(_localctx, 3);
                setState(158);
                localReferenceDefinition();
                break;
            }

            case 4:
            {
                enterOuterAlt(_localctx, 4);
                setState(159);
                assignment();
                break;
            }

            case 5:
            {
                enterOuterAlt(_localctx, 5);
                setState(160);
                deleteStatement();
                break;
            }

            case 6:
            {
                enterOuterAlt(_localctx, 6);
                setState(161);
                returnStatement();
                break;
            }
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ExpressionStatementContext ------------------------------------------------------------------

anceParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::IndependentExpressionContext* anceParser::ExpressionStatementContext::independentExpression()
{
    return getRuleContext<anceParser::IndependentExpressionContext>(0);
}

tree::TerminalNode* anceParser::ExpressionStatementContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

size_t anceParser::ExpressionStatementContext::getRuleIndex() const
{
    return anceParser::RuleExpressionStatement;
}

antlrcpp::Any anceParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitExpressionStatement(this);
    else
        return visitor->visitChildren(this);
}

anceParser::ExpressionStatementContext* anceParser::expressionStatement()
{
    ExpressionStatementContext* _localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
    enterRule(_localctx, 14, anceParser::RuleExpressionStatement);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(164);
        independentExpression();
        setState(165);
        match(anceParser::SEMICOLON);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- LocalVariableDefinitionContext ------------------------------------------------------------------

anceParser::LocalVariableDefinitionContext::LocalVariableDefinitionContext(ParserRuleContext* parent,
                                                                           size_t             invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::TypeContext* anceParser::LocalVariableDefinitionContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::LocalVariableDefinitionContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::LocalVariableDefinitionContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

anceParser::AssignerContext* anceParser::LocalVariableDefinitionContext::assigner()
{
    return getRuleContext<anceParser::AssignerContext>(0);
}

anceParser::ExpressionContext* anceParser::LocalVariableDefinitionContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

size_t anceParser::LocalVariableDefinitionContext::getRuleIndex() const
{
    return anceParser::RuleLocalVariableDefinition;
}

antlrcpp::Any anceParser::LocalVariableDefinitionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitLocalVariableDefinition(this);
    else
        return visitor->visitChildren(this);
}

anceParser::LocalVariableDefinitionContext* anceParser::localVariableDefinition()
{
    LocalVariableDefinitionContext* _localctx =
        _tracker.createInstance<LocalVariableDefinitionContext>(_ctx, getState());
    enterRule(_localctx, 16, anceParser::RuleLocalVariableDefinition);
    size_t _la = 0;

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(167);
        type();
        setState(168);
        match(anceParser::IDENTIFIER);
        setState(172);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0)
             && ((1ULL << _la)
                 & ((1ULL << anceParser::T__12) | (1ULL << anceParser::T__13) | (1ULL << anceParser::T__14)))
                    != 0))
        {
            setState(169);
            assigner();
            setState(170);
            expression(0);
        }
        setState(174);
        match(anceParser::SEMICOLON);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- LocalReferenceDefinitionContext ------------------------------------------------------------------

anceParser::LocalReferenceDefinitionContext::LocalReferenceDefinitionContext(ParserRuleContext* parent,
                                                                             size_t             invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::LocalReferenceDefinitionContext::getRuleIndex() const
{
    return anceParser::RuleLocalReferenceDefinition;
}

void anceParser::LocalReferenceDefinitionContext::copyFrom(LocalReferenceDefinitionContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- LocalReferenceToValueDefinitionContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::LocalReferenceToValueDefinitionContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::TypeContext* anceParser::LocalReferenceToValueDefinitionContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::ExpressionContext* anceParser::LocalReferenceToValueDefinitionContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

tree::TerminalNode* anceParser::LocalReferenceToValueDefinitionContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

anceParser::LocalReferenceToValueDefinitionContext::LocalReferenceToValueDefinitionContext(
    LocalReferenceDefinitionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::LocalReferenceToValueDefinitionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitLocalReferenceToValueDefinition(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LocalReferenceToPointerDefinitionContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::LocalReferenceToPointerDefinitionContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::TypeContext* anceParser::LocalReferenceToPointerDefinitionContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::ExpressionContext* anceParser::LocalReferenceToPointerDefinitionContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

tree::TerminalNode* anceParser::LocalReferenceToPointerDefinitionContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

anceParser::LocalReferenceToPointerDefinitionContext::LocalReferenceToPointerDefinitionContext(
    LocalReferenceDefinitionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::LocalReferenceToPointerDefinitionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitLocalReferenceToPointerDefinition(this);
    else
        return visitor->visitChildren(this);
}
anceParser::LocalReferenceDefinitionContext* anceParser::localReferenceDefinition()
{
    LocalReferenceDefinitionContext* _localctx =
        _tracker.createInstance<LocalReferenceDefinitionContext>(_ctx, getState());
    enterRule(_localctx, 18, anceParser::RuleLocalReferenceDefinition);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        setState(193);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx))
        {
            case 1:
            {
                _localctx = dynamic_cast<LocalReferenceDefinitionContext*>(
                    _tracker.createInstance<anceParser::LocalReferenceToValueDefinitionContext>(_localctx));
                enterOuterAlt(_localctx, 1);
                setState(176);
                match(anceParser::T__8);
                setState(177);
                match(anceParser::IDENTIFIER);
                setState(178);
                match(anceParser::T__9);
                setState(179);
                type();
                setState(180);
                match(anceParser::T__10);
                setState(181);
                expression(0);
                setState(182);
                match(anceParser::SEMICOLON);
                break;
            }

            case 2:
            {
                _localctx = dynamic_cast<LocalReferenceDefinitionContext*>(
                    _tracker.createInstance<anceParser::LocalReferenceToPointerDefinitionContext>(_localctx));
                enterOuterAlt(_localctx, 2);
                setState(184);
                match(anceParser::T__8);
                setState(185);
                match(anceParser::IDENTIFIER);
                setState(186);
                match(anceParser::T__9);
                setState(187);
                type();
                setState(188);
                match(anceParser::T__10);
                setState(189);
                match(anceParser::T__11);
                setState(190);
                expression(0);
                setState(191);
                match(anceParser::SEMICOLON);
                break;
            }
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

anceParser::AssignmentContext::AssignmentContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::AssignableContext* anceParser::AssignmentContext::assignable()
{
    return getRuleContext<anceParser::AssignableContext>(0);
}

anceParser::AssignerContext* anceParser::AssignmentContext::assigner()
{
    return getRuleContext<anceParser::AssignerContext>(0);
}

anceParser::ExpressionContext* anceParser::AssignmentContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

tree::TerminalNode* anceParser::AssignmentContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

size_t anceParser::AssignmentContext::getRuleIndex() const
{
    return anceParser::RuleAssignment;
}

antlrcpp::Any anceParser::AssignmentContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitAssignment(this);
    else
        return visitor->visitChildren(this);
}

anceParser::AssignmentContext* anceParser::assignment()
{
    AssignmentContext* _localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
    enterRule(_localctx, 20, anceParser::RuleAssignment);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(195);
        assignable();
        setState(196);
        assigner();
        setState(197);
        expression(0);
        setState(198);
        match(anceParser::SEMICOLON);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- AssignerContext ------------------------------------------------------------------

anceParser::AssignerContext::AssignerContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::AssignerContext::getRuleIndex() const
{
    return anceParser::RuleAssigner;
}

void anceParser::AssignerContext::copyFrom(AssignerContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- MoveAssignmentContext ------------------------------------------------------------------

anceParser::MoveAssignmentContext::MoveAssignmentContext(AssignerContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::MoveAssignmentContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitMoveAssignment(this);
    else
        return visitor->visitChildren(this);
}
//----------------- FinalCopyAssignmentContext ------------------------------------------------------------------

anceParser::FinalCopyAssignmentContext::FinalCopyAssignmentContext(AssignerContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::FinalCopyAssignmentContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitFinalCopyAssignment(this);
    else
        return visitor->visitChildren(this);
}
//----------------- CopyAssignmentContext ------------------------------------------------------------------

anceParser::CopyAssignmentContext::CopyAssignmentContext(AssignerContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::CopyAssignmentContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitCopyAssignment(this);
    else
        return visitor->visitChildren(this);
}
anceParser::AssignerContext* anceParser::assigner()
{
    AssignerContext* _localctx = _tracker.createInstance<AssignerContext>(_ctx, getState());
    enterRule(_localctx, 22, anceParser::RuleAssigner);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        setState(203);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__12:
            {
                _localctx = dynamic_cast<AssignerContext*>(
                    _tracker.createInstance<anceParser::CopyAssignmentContext>(_localctx));
                enterOuterAlt(_localctx, 1);
                setState(200);
                match(anceParser::T__12);
                break;
            }

            case anceParser::T__13:
            {
                _localctx = dynamic_cast<AssignerContext*>(
                    _tracker.createInstance<anceParser::MoveAssignmentContext>(_localctx));
                enterOuterAlt(_localctx, 2);
                setState(201);
                match(anceParser::T__13);
                break;
            }

            case anceParser::T__14:
            {
                _localctx = dynamic_cast<AssignerContext*>(
                    _tracker.createInstance<anceParser::FinalCopyAssignmentContext>(_localctx));
                enterOuterAlt(_localctx, 3);
                setState(202);
                match(anceParser::T__14);
                break;
            }

            default:
                throw NoViableAltException(this);
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- DeleteStatementContext ------------------------------------------------------------------

anceParser::DeleteStatementContext::DeleteStatementContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::ExpressionContext* anceParser::DeleteStatementContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

tree::TerminalNode* anceParser::DeleteStatementContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

tree::TerminalNode* anceParser::DeleteStatementContext::BUFFER()
{
    return getToken(anceParser::BUFFER, 0);
}

size_t anceParser::DeleteStatementContext::getRuleIndex() const
{
    return anceParser::RuleDeleteStatement;
}

antlrcpp::Any anceParser::DeleteStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitDeleteStatement(this);
    else
        return visitor->visitChildren(this);
}

anceParser::DeleteStatementContext* anceParser::deleteStatement()
{
    DeleteStatementContext* _localctx = _tracker.createInstance<DeleteStatementContext>(_ctx, getState());
    enterRule(_localctx, 24, anceParser::RuleDeleteStatement);
    size_t _la = 0;

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(205);
        match(anceParser::T__15);
        setState(207);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::BUFFER)
        {
            setState(206);
            match(anceParser::BUFFER);
        }
        setState(209);
        expression(0);
        setState(210);
        match(anceParser::SEMICOLON);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

anceParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::ReturnStatementContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

anceParser::ExpressionContext* anceParser::ReturnStatementContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

size_t anceParser::ReturnStatementContext::getRuleIndex() const
{
    return anceParser::RuleReturnStatement;
}

antlrcpp::Any anceParser::ReturnStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitReturnStatement(this);
    else
        return visitor->visitChildren(this);
}

anceParser::ReturnStatementContext* anceParser::returnStatement()
{
    ReturnStatementContext* _localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
    enterRule(_localctx, 26, anceParser::RuleReturnStatement);
    size_t _la = 0;

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(212);
        match(anceParser::T__16);
        setState(214);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0)
             && ((1ULL << _la)
                 & ((1ULL << anceParser::T__2) | (1ULL << anceParser::T__10) | (1ULL << anceParser::T__19)
                    | (1ULL << anceParser::T__22) | (1ULL << anceParser::T__23) | (1ULL << anceParser::T__24)
                    | (1ULL << anceParser::T__25) | (1ULL << anceParser::SIGNED_INTEGER)
                    | (1ULL << anceParser::HEX_INTEGER) | (1ULL << anceParser::BIN_INTEGER)
                    | (1ULL << anceParser::OCT_INTEGER) | (1ULL << anceParser::HALF) | (1ULL << anceParser::SINGLE)
                    | (1ULL << anceParser::DOUBLE) | (1ULL << anceParser::QUAD) | (1ULL << anceParser::STRING)
                    | (1ULL << anceParser::BYTE) | (1ULL << anceParser::INTEGER) | (1ULL << anceParser::IDENTIFIER)))
                    != 0))
        {
            setState(213);
            expression(0);
        }
        setState(216);
        match(anceParser::SEMICOLON);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- AssignableContext ------------------------------------------------------------------

anceParser::AssignableContext::AssignableContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::VariableAssignableContext* anceParser::AssignableContext::variableAssignable()
{
    return getRuleContext<anceParser::VariableAssignableContext>(0);
}

size_t anceParser::AssignableContext::getRuleIndex() const
{
    return anceParser::RuleAssignable;
}

antlrcpp::Any anceParser::AssignableContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitAssignable(this);
    else
        return visitor->visitChildren(this);
}

anceParser::AssignableContext* anceParser::assignable()
{
    AssignableContext* _localctx = _tracker.createInstance<AssignableContext>(_ctx, getState());
    enterRule(_localctx, 28, anceParser::RuleAssignable);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(218);
        variableAssignable();
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- VariableAssignableContext ------------------------------------------------------------------

anceParser::VariableAssignableContext::VariableAssignableContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::VariableAssignableContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

size_t anceParser::VariableAssignableContext::getRuleIndex() const
{
    return anceParser::RuleVariableAssignable;
}

antlrcpp::Any anceParser::VariableAssignableContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitVariableAssignable(this);
    else
        return visitor->visitChildren(this);
}

anceParser::VariableAssignableContext* anceParser::variableAssignable()
{
    VariableAssignableContext* _localctx = _tracker.createInstance<VariableAssignableContext>(_ctx, getState());
    enterRule(_localctx, 30, anceParser::RuleVariableAssignable);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(220);
        match(anceParser::IDENTIFIER);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

anceParser::ExpressionContext::ExpressionContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::ExpressionContext::getRuleIndex() const
{
    return anceParser::RuleExpression;
}

void anceParser::ExpressionContext::copyFrom(ExpressionContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- CastContext ------------------------------------------------------------------

anceParser::RoughCastContext* anceParser::CastContext::roughCast()
{
    return getRuleContext<anceParser::RoughCastContext>(0);
}

anceParser::CastContext::CastContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::CastContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitCast(this);
    else
        return visitor->visitChildren(this);
}
//----------------- RefContext ------------------------------------------------------------------

anceParser::BindRefContext* anceParser::RefContext::bindRef()
{
    return getRuleContext<anceParser::BindRefContext>(0);
}

anceParser::RefContext::RefContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::RefContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitRef(this);
    else
        return visitor->visitChildren(this);
}
//----------------- IndependentContext ------------------------------------------------------------------

anceParser::IndependentExpressionContext* anceParser::IndependentContext::independentExpression()
{
    return getRuleContext<anceParser::IndependentExpressionContext>(0);
}

anceParser::IndependentContext::IndependentContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::IndependentContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitIndependent(this);
    else
        return visitor->visitChildren(this);
}
//----------------- VariableContext ------------------------------------------------------------------

anceParser::VariableAccessContext* anceParser::VariableContext::variableAccess()
{
    return getRuleContext<anceParser::VariableAccessContext>(0);
}

anceParser::VariableContext::VariableContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::VariableContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitVariable(this);
    else
        return visitor->visitChildren(this);
}
//----------------- AllocContext ------------------------------------------------------------------

anceParser::AllocationContext* anceParser::AllocContext::allocation()
{
    return getRuleContext<anceParser::AllocationContext>(0);
}

anceParser::AllocContext::AllocContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::AllocContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitAlloc(this);
    else
        return visitor->visitChildren(this);
}
//----------------- AdressOfContext ------------------------------------------------------------------

anceParser::AddressofContext* anceParser::AdressOfContext::addressof()
{
    return getRuleContext<anceParser::AddressofContext>(0);
}

anceParser::AdressOfContext::AdressOfContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::AdressOfContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitAdressOf(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LiteralContext ------------------------------------------------------------------

anceParser::LiteralExpressionContext* anceParser::LiteralContext::literalExpression()
{
    return getRuleContext<anceParser::LiteralExpressionContext>(0);
}

anceParser::LiteralContext::LiteralContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::LiteralContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitLiteral(this);
    else
        return visitor->visitChildren(this);
}
//----------------- SizeOfContext ------------------------------------------------------------------

anceParser::SizeofTypeContext* anceParser::SizeOfContext::sizeofType()
{
    return getRuleContext<anceParser::SizeofTypeContext>(0);
}

anceParser::SizeofExpressionContext* anceParser::SizeOfContext::sizeofExpression()
{
    return getRuleContext<anceParser::SizeofExpressionContext>(0);
}

anceParser::SizeOfContext::SizeOfContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::SizeOfContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitSizeOf(this);
    else
        return visitor->visitChildren(this);
}
//----------------- SubscriptContext ------------------------------------------------------------------

std::vector<anceParser::ExpressionContext*> anceParser::SubscriptContext::expression()
{
    return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::SubscriptContext::expression(size_t i)
{
    return getRuleContext<anceParser::ExpressionContext>(i);
}

anceParser::SubscriptContext::SubscriptContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::SubscriptContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitSubscript(this);
    else
        return visitor->visitChildren(this);
}

anceParser::ExpressionContext* anceParser::expression()
{
    return expression(0);
}

anceParser::ExpressionContext* anceParser::expression(int precedence)
{
    ParserRuleContext*             parentContext   = _ctx;
    size_t                         parentState     = getState();
    anceParser::ExpressionContext* _localctx       = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
    anceParser::ExpressionContext* previousContext = _localctx;
    (void) previousContext;// Silence compiler, in case the context is not used by generated code.
    size_t startState = 32;
    enterRecursionRule(_localctx, 32, anceParser::RuleExpression, precedence);

    auto onExit = finally([=] { unrollRecursionContexts(parentContext); });
    try
    {
        size_t alt;
        enterOuterAlt(_localctx, 1);
        setState(232);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx))
        {
            case 1:
            {
                _localctx       = _tracker.createInstance<VariableContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;

                setState(223);
                variableAccess();
                break;
            }

            case 2:
            {
                _localctx       = _tracker.createInstance<AllocContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(224);
                allocation();
                break;
            }

            case 3:
            {
                _localctx       = _tracker.createInstance<CastContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(225);
                roughCast();
                break;
            }

            case 4:
            {
                _localctx       = _tracker.createInstance<AdressOfContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(226);
                addressof();
                break;
            }

            case 5:
            {
                _localctx       = _tracker.createInstance<RefContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(227);
                bindRef();
                break;
            }

            case 6:
            {
                _localctx       = _tracker.createInstance<SizeOfContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(228);
                sizeofType();
                break;
            }

            case 7:
            {
                _localctx       = _tracker.createInstance<SizeOfContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(229);
                sizeofExpression();
                break;
            }

            case 8:
            {
                _localctx       = _tracker.createInstance<LiteralContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(230);
                literalExpression();
                break;
            }

            case 9:
            {
                _localctx       = _tracker.createInstance<IndependentContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(231);
                independentExpression();
                break;
            }
        }
        _ctx->stop = _input->LT(-1);
        setState(241);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER)
        {
            if (alt == 1)
            {
                if (!_parseListeners.empty()) triggerExitRuleEvent();
                previousContext = _localctx;
                auto newContext = _tracker.createInstance<SubscriptContext>(
                    _tracker.createInstance<ExpressionContext>(parentContext, parentState));
                _localctx           = newContext;
                newContext->indexed = previousContext;
                pushNewRecursionContext(newContext, startState, RuleExpression);
                setState(234);

                if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
                setState(235);
                match(anceParser::T__17);
                setState(236);
                dynamic_cast<SubscriptContext*>(_localctx)->index = expression(0);
                setState(237);
                match(anceParser::T__18);
            }
            setState(243);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }
    return _localctx;
}

//----------------- IndependentExpressionContext ------------------------------------------------------------------

anceParser::IndependentExpressionContext::IndependentExpressionContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::FunctionCallContext* anceParser::IndependentExpressionContext::functionCall()
{
    return getRuleContext<anceParser::FunctionCallContext>(0);
}

size_t anceParser::IndependentExpressionContext::getRuleIndex() const
{
    return anceParser::RuleIndependentExpression;
}

antlrcpp::Any anceParser::IndependentExpressionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitIndependentExpression(this);
    else
        return visitor->visitChildren(this);
}

anceParser::IndependentExpressionContext* anceParser::independentExpression()
{
    IndependentExpressionContext* _localctx = _tracker.createInstance<IndependentExpressionContext>(_ctx, getState());
    enterRule(_localctx, 34, anceParser::RuleIndependentExpression);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(244);
        functionCall();
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

anceParser::FunctionCallContext::FunctionCallContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::FunctionCallContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::ArgumentsContext* anceParser::FunctionCallContext::arguments()
{
    return getRuleContext<anceParser::ArgumentsContext>(0);
}

size_t anceParser::FunctionCallContext::getRuleIndex() const
{
    return anceParser::RuleFunctionCall;
}

antlrcpp::Any anceParser::FunctionCallContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitFunctionCall(this);
    else
        return visitor->visitChildren(this);
}

anceParser::FunctionCallContext* anceParser::functionCall()
{
    FunctionCallContext* _localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
    enterRule(_localctx, 36, anceParser::RuleFunctionCall);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(246);
        match(anceParser::IDENTIFIER);
        setState(247);
        match(anceParser::T__0);
        setState(248);
        arguments();
        setState(249);
        match(anceParser::T__1);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ArgumentsContext ------------------------------------------------------------------

anceParser::ArgumentsContext::ArgumentsContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

std::vector<anceParser::ExpressionContext*> anceParser::ArgumentsContext::expression()
{
    return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::ArgumentsContext::expression(size_t i)
{
    return getRuleContext<anceParser::ExpressionContext>(i);
}

size_t anceParser::ArgumentsContext::getRuleIndex() const
{
    return anceParser::RuleArguments;
}

antlrcpp::Any anceParser::ArgumentsContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitArguments(this);
    else
        return visitor->visitChildren(this);
}

anceParser::ArgumentsContext* anceParser::arguments()
{
    ArgumentsContext* _localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
    enterRule(_localctx, 38, anceParser::RuleArguments);
    size_t _la = 0;

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(259);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0)
             && ((1ULL << _la)
                 & ((1ULL << anceParser::T__2) | (1ULL << anceParser::T__10) | (1ULL << anceParser::T__19)
                    | (1ULL << anceParser::T__22) | (1ULL << anceParser::T__23) | (1ULL << anceParser::T__24)
                    | (1ULL << anceParser::T__25) | (1ULL << anceParser::SIGNED_INTEGER)
                    | (1ULL << anceParser::HEX_INTEGER) | (1ULL << anceParser::BIN_INTEGER)
                    | (1ULL << anceParser::OCT_INTEGER) | (1ULL << anceParser::HALF) | (1ULL << anceParser::SINGLE)
                    | (1ULL << anceParser::DOUBLE) | (1ULL << anceParser::QUAD) | (1ULL << anceParser::STRING)
                    | (1ULL << anceParser::BYTE) | (1ULL << anceParser::INTEGER) | (1ULL << anceParser::IDENTIFIER)))
                    != 0))
        {
            setState(251);
            expression(0);
            setState(256);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == anceParser::T__5)
            {
                setState(252);
                match(anceParser::T__5);
                setState(253);
                expression(0);
                setState(258);
                _errHandler->sync(this);
                _la = _input->LA(1);
            }
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- VariableAccessContext ------------------------------------------------------------------

anceParser::VariableAccessContext::VariableAccessContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::VariableAccessContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

size_t anceParser::VariableAccessContext::getRuleIndex() const
{
    return anceParser::RuleVariableAccess;
}

antlrcpp::Any anceParser::VariableAccessContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitVariableAccess(this);
    else
        return visitor->visitChildren(this);
}

anceParser::VariableAccessContext* anceParser::variableAccess()
{
    VariableAccessContext* _localctx = _tracker.createInstance<VariableAccessContext>(_ctx, getState());
    enterRule(_localctx, 40, anceParser::RuleVariableAccess);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(261);
        match(anceParser::IDENTIFIER);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- AllocationContext ------------------------------------------------------------------

anceParser::AllocationContext::AllocationContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::AllocatorContext* anceParser::AllocationContext::allocator()
{
    return getRuleContext<anceParser::AllocatorContext>(0);
}

anceParser::TypeContext* anceParser::AllocationContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::ExpressionContext* anceParser::AllocationContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

size_t anceParser::AllocationContext::getRuleIndex() const
{
    return anceParser::RuleAllocation;
}

antlrcpp::Any anceParser::AllocationContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitAllocation(this);
    else
        return visitor->visitChildren(this);
}

anceParser::AllocationContext* anceParser::allocation()
{
    AllocationContext* _localctx = _tracker.createInstance<AllocationContext>(_ctx, getState());
    enterRule(_localctx, 42, anceParser::RuleAllocation);
    size_t _la = 0;

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(263);
        match(anceParser::T__19);
        setState(268);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::T__17)
        {
            setState(264);
            match(anceParser::T__17);
            setState(265);
            expression(0);
            setState(266);
            match(anceParser::T__18);
        }
        setState(270);
        allocator();
        setState(271);
        type();
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- AllocatorContext ------------------------------------------------------------------

anceParser::AllocatorContext::AllocatorContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::AllocatorContext::getRuleIndex() const
{
    return anceParser::RuleAllocator;
}

void anceParser::AllocatorContext::copyFrom(AllocatorContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- DynamicContext ------------------------------------------------------------------

anceParser::DynamicContext::DynamicContext(AllocatorContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::DynamicContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitDynamic(this);
    else
        return visitor->visitChildren(this);
}
//----------------- AutomaticContext ------------------------------------------------------------------

anceParser::AutomaticContext::AutomaticContext(AllocatorContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::AutomaticContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitAutomatic(this);
    else
        return visitor->visitChildren(this);
}
anceParser::AllocatorContext* anceParser::allocator()
{
    AllocatorContext* _localctx = _tracker.createInstance<AllocatorContext>(_ctx, getState());
    enterRule(_localctx, 44, anceParser::RuleAllocator);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        setState(275);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__20:
            {
                _localctx =
                    dynamic_cast<AllocatorContext*>(_tracker.createInstance<anceParser::DynamicContext>(_localctx));
                enterOuterAlt(_localctx, 1);
                setState(273);
                match(anceParser::T__20);
                break;
            }

            case anceParser::T__21:
            {
                _localctx =
                    dynamic_cast<AllocatorContext*>(_tracker.createInstance<anceParser::AutomaticContext>(_localctx));
                enterOuterAlt(_localctx, 2);
                setState(274);
                match(anceParser::T__21);
                break;
            }

            default:
                throw NoViableAltException(this);
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- RoughCastContext ------------------------------------------------------------------

anceParser::RoughCastContext::RoughCastContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::TypeContext* anceParser::RoughCastContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::ExpressionContext* anceParser::RoughCastContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

size_t anceParser::RoughCastContext::getRuleIndex() const
{
    return anceParser::RuleRoughCast;
}

antlrcpp::Any anceParser::RoughCastContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitRoughCast(this);
    else
        return visitor->visitChildren(this);
}

anceParser::RoughCastContext* anceParser::roughCast()
{
    RoughCastContext* _localctx = _tracker.createInstance<RoughCastContext>(_ctx, getState());
    enterRule(_localctx, 46, anceParser::RuleRoughCast);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(277);
        match(anceParser::T__2);
        setState(278);
        type();
        setState(279);
        match(anceParser::T__3);
        setState(280);
        expression(0);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- AddressofContext ------------------------------------------------------------------

anceParser::AddressofContext::AddressofContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::ExpressionContext* anceParser::AddressofContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

size_t anceParser::AddressofContext::getRuleIndex() const
{
    return anceParser::RuleAddressof;
}

antlrcpp::Any anceParser::AddressofContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitAddressof(this);
    else
        return visitor->visitChildren(this);
}

anceParser::AddressofContext* anceParser::addressof()
{
    AddressofContext* _localctx = _tracker.createInstance<AddressofContext>(_ctx, getState());
    enterRule(_localctx, 48, anceParser::RuleAddressof);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(282);
        match(anceParser::T__22);
        setState(283);
        expression(0);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- BindRefContext ------------------------------------------------------------------

anceParser::BindRefContext::BindRefContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::BindRefContext::getRuleIndex() const
{
    return anceParser::RuleBindRef;
}

void anceParser::BindRefContext::copyFrom(BindRefContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- BindReferenceToAddressContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::BindReferenceToAddressContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::BindReferenceToAddressContext::BindReferenceToAddressContext(BindRefContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::BindReferenceToAddressContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitBindReferenceToAddress(this);
    else
        return visitor->visitChildren(this);
}
//----------------- BindReferenceContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::BindReferenceContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::BindReferenceContext::BindReferenceContext(BindRefContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::BindReferenceContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitBindReference(this);
    else
        return visitor->visitChildren(this);
}
anceParser::BindRefContext* anceParser::bindRef()
{
    BindRefContext* _localctx = _tracker.createInstance<BindRefContext>(_ctx, getState());
    enterRule(_localctx, 50, anceParser::RuleBindRef);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        setState(290);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx))
        {
            case 1:
            {
                _localctx =
                    dynamic_cast<BindRefContext*>(_tracker.createInstance<anceParser::BindReferenceContext>(_localctx));
                enterOuterAlt(_localctx, 1);
                setState(285);
                match(anceParser::T__10);
                setState(286);
                expression(0);
                break;
            }

            case 2:
            {
                _localctx = dynamic_cast<BindRefContext*>(
                    _tracker.createInstance<anceParser::BindReferenceToAddressContext>(_localctx));
                enterOuterAlt(_localctx, 2);
                setState(287);
                match(anceParser::T__10);
                setState(288);
                match(anceParser::T__11);
                setState(289);
                expression(0);
                break;
            }
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- SizeofTypeContext ------------------------------------------------------------------

anceParser::SizeofTypeContext::SizeofTypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::TypeContext* anceParser::SizeofTypeContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

size_t anceParser::SizeofTypeContext::getRuleIndex() const
{
    return anceParser::RuleSizeofType;
}

antlrcpp::Any anceParser::SizeofTypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitSizeofType(this);
    else
        return visitor->visitChildren(this);
}

anceParser::SizeofTypeContext* anceParser::sizeofType()
{
    SizeofTypeContext* _localctx = _tracker.createInstance<SizeofTypeContext>(_ctx, getState());
    enterRule(_localctx, 52, anceParser::RuleSizeofType);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(292);
        match(anceParser::T__23);
        setState(293);
        type();
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- SizeofExpressionContext ------------------------------------------------------------------

anceParser::SizeofExpressionContext::SizeofExpressionContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::ExpressionContext* anceParser::SizeofExpressionContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

size_t anceParser::SizeofExpressionContext::getRuleIndex() const
{
    return anceParser::RuleSizeofExpression;
}

antlrcpp::Any anceParser::SizeofExpressionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitSizeofExpression(this);
    else
        return visitor->visitChildren(this);
}

anceParser::SizeofExpressionContext* anceParser::sizeofExpression()
{
    SizeofExpressionContext* _localctx = _tracker.createInstance<SizeofExpressionContext>(_ctx, getState());
    enterRule(_localctx, 54, anceParser::RuleSizeofExpression);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(295);
        match(anceParser::T__23);
        setState(296);
        match(anceParser::T__0);
        setState(297);
        expression(0);
        setState(298);
        match(anceParser::T__1);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- LiteralExpressionContext ------------------------------------------------------------------

anceParser::LiteralExpressionContext::LiteralExpressionContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::StringLiteralContext* anceParser::LiteralExpressionContext::stringLiteral()
{
    return getRuleContext<anceParser::StringLiteralContext>(0);
}

anceParser::ByteLiteralContext* anceParser::LiteralExpressionContext::byteLiteral()
{
    return getRuleContext<anceParser::ByteLiteralContext>(0);
}

anceParser::IntegerLiteralContext* anceParser::LiteralExpressionContext::integerLiteral()
{
    return getRuleContext<anceParser::IntegerLiteralContext>(0);
}

anceParser::FloatingPointLiteralContext* anceParser::LiteralExpressionContext::floatingPointLiteral()
{
    return getRuleContext<anceParser::FloatingPointLiteralContext>(0);
}

anceParser::BooleanLiteralContext* anceParser::LiteralExpressionContext::booleanLiteral()
{
    return getRuleContext<anceParser::BooleanLiteralContext>(0);
}

anceParser::SizeLiteralContext* anceParser::LiteralExpressionContext::sizeLiteral()
{
    return getRuleContext<anceParser::SizeLiteralContext>(0);
}

anceParser::DiffLiteralContext* anceParser::LiteralExpressionContext::diffLiteral()
{
    return getRuleContext<anceParser::DiffLiteralContext>(0);
}

size_t anceParser::LiteralExpressionContext::getRuleIndex() const
{
    return anceParser::RuleLiteralExpression;
}

antlrcpp::Any anceParser::LiteralExpressionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitLiteralExpression(this);
    else
        return visitor->visitChildren(this);
}

anceParser::LiteralExpressionContext* anceParser::literalExpression()
{
    LiteralExpressionContext* _localctx = _tracker.createInstance<LiteralExpressionContext>(_ctx, getState());
    enterRule(_localctx, 56, anceParser::RuleLiteralExpression);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        setState(307);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx))
        {
            case 1:
            {
                enterOuterAlt(_localctx, 1);
                setState(300);
                stringLiteral();
                break;
            }

            case 2:
            {
                enterOuterAlt(_localctx, 2);
                setState(301);
                byteLiteral();
                break;
            }

            case 3:
            {
                enterOuterAlt(_localctx, 3);
                setState(302);
                integerLiteral();
                break;
            }

            case 4:
            {
                enterOuterAlt(_localctx, 4);
                setState(303);
                floatingPointLiteral();
                break;
            }

            case 5:
            {
                enterOuterAlt(_localctx, 5);
                setState(304);
                booleanLiteral();
                break;
            }

            case 6:
            {
                enterOuterAlt(_localctx, 6);
                setState(305);
                sizeLiteral();
                break;
            }

            case 7:
            {
                enterOuterAlt(_localctx, 7);
                setState(306);
                diffLiteral();
                break;
            }
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- StringLiteralContext ------------------------------------------------------------------

anceParser::StringLiteralContext::StringLiteralContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::StringLiteralContext::STRING()
{
    return getToken(anceParser::STRING, 0);
}

tree::TerminalNode* anceParser::StringLiteralContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

size_t anceParser::StringLiteralContext::getRuleIndex() const
{
    return anceParser::RuleStringLiteral;
}

antlrcpp::Any anceParser::StringLiteralContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitStringLiteral(this);
    else
        return visitor->visitChildren(this);
}

anceParser::StringLiteralContext* anceParser::stringLiteral()
{
    StringLiteralContext* _localctx = _tracker.createInstance<StringLiteralContext>(_ctx, getState());
    enterRule(_localctx, 58, anceParser::RuleStringLiteral);
    size_t _la = 0;

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(310);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::IDENTIFIER)
        {
            setState(309);
            dynamic_cast<StringLiteralContext*>(_localctx)->prefix = match(anceParser::IDENTIFIER);
        }
        setState(312);
        match(anceParser::STRING);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ByteLiteralContext ------------------------------------------------------------------

anceParser::ByteLiteralContext::ByteLiteralContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::ByteLiteralContext::BYTE()
{
    return getToken(anceParser::BYTE, 0);
}

size_t anceParser::ByteLiteralContext::getRuleIndex() const
{
    return anceParser::RuleByteLiteral;
}

antlrcpp::Any anceParser::ByteLiteralContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitByteLiteral(this);
    else
        return visitor->visitChildren(this);
}

anceParser::ByteLiteralContext* anceParser::byteLiteral()
{
    ByteLiteralContext* _localctx = _tracker.createInstance<ByteLiteralContext>(_ctx, getState());
    enterRule(_localctx, 60, anceParser::RuleByteLiteral);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(314);
        match(anceParser::BYTE);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- IntegerLiteralContext ------------------------------------------------------------------

anceParser::IntegerLiteralContext::IntegerLiteralContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::UnsignedIntegerContext* anceParser::IntegerLiteralContext::unsignedInteger()
{
    return getRuleContext<anceParser::UnsignedIntegerContext>(0);
}

anceParser::SignedIntegerContext* anceParser::IntegerLiteralContext::signedInteger()
{
    return getRuleContext<anceParser::SignedIntegerContext>(0);
}

anceParser::SpecialIntegerContext* anceParser::IntegerLiteralContext::specialInteger()
{
    return getRuleContext<anceParser::SpecialIntegerContext>(0);
}

size_t anceParser::IntegerLiteralContext::getRuleIndex() const
{
    return anceParser::RuleIntegerLiteral;
}

antlrcpp::Any anceParser::IntegerLiteralContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitIntegerLiteral(this);
    else
        return visitor->visitChildren(this);
}

anceParser::IntegerLiteralContext* anceParser::integerLiteral()
{
    IntegerLiteralContext* _localctx = _tracker.createInstance<IntegerLiteralContext>(_ctx, getState());
    enterRule(_localctx, 62, anceParser::RuleIntegerLiteral);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        setState(319);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::INTEGER:
            {
                enterOuterAlt(_localctx, 1);
                setState(316);
                unsignedInteger();
                break;
            }

            case anceParser::SIGNED_INTEGER:
            {
                enterOuterAlt(_localctx, 2);
                setState(317);
                signedInteger();
                break;
            }

            case anceParser::HEX_INTEGER:
            case anceParser::BIN_INTEGER:
            case anceParser::OCT_INTEGER:
            {
                enterOuterAlt(_localctx, 3);
                setState(318);
                specialInteger();
                break;
            }

            default:
                throw NoViableAltException(this);
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- UnsignedIntegerContext ------------------------------------------------------------------

anceParser::UnsignedIntegerContext::UnsignedIntegerContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

std::vector<tree::TerminalNode*> anceParser::UnsignedIntegerContext::INTEGER()
{
    return getTokens(anceParser::INTEGER);
}

tree::TerminalNode* anceParser::UnsignedIntegerContext::INTEGER(size_t i)
{
    return getToken(anceParser::INTEGER, i);
}

size_t anceParser::UnsignedIntegerContext::getRuleIndex() const
{
    return anceParser::RuleUnsignedInteger;
}

antlrcpp::Any anceParser::UnsignedIntegerContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitUnsignedInteger(this);
    else
        return visitor->visitChildren(this);
}

anceParser::UnsignedIntegerContext* anceParser::unsignedInteger()
{
    UnsignedIntegerContext* _localctx = _tracker.createInstance<UnsignedIntegerContext>(_ctx, getState());
    enterRule(_localctx, 64, anceParser::RuleUnsignedInteger);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(321);
        dynamic_cast<UnsignedIntegerContext*>(_localctx)->value = match(anceParser::INTEGER);
        setState(322);
        match(anceParser::T__9);
        setState(323);
        dynamic_cast<UnsignedIntegerContext*>(_localctx)->width = match(anceParser::INTEGER);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- SignedIntegerContext ------------------------------------------------------------------

anceParser::SignedIntegerContext::SignedIntegerContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::SignedIntegerContext::SIGNED_INTEGER()
{
    return getToken(anceParser::SIGNED_INTEGER, 0);
}

tree::TerminalNode* anceParser::SignedIntegerContext::INTEGER()
{
    return getToken(anceParser::INTEGER, 0);
}

size_t anceParser::SignedIntegerContext::getRuleIndex() const
{
    return anceParser::RuleSignedInteger;
}

antlrcpp::Any anceParser::SignedIntegerContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitSignedInteger(this);
    else
        return visitor->visitChildren(this);
}

anceParser::SignedIntegerContext* anceParser::signedInteger()
{
    SignedIntegerContext* _localctx = _tracker.createInstance<SignedIntegerContext>(_ctx, getState());
    enterRule(_localctx, 66, anceParser::RuleSignedInteger);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(325);
        dynamic_cast<SignedIntegerContext*>(_localctx)->value = match(anceParser::SIGNED_INTEGER);
        setState(326);
        match(anceParser::T__9);
        setState(327);
        dynamic_cast<SignedIntegerContext*>(_localctx)->width = match(anceParser::INTEGER);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- SpecialIntegerContext ------------------------------------------------------------------

anceParser::SpecialIntegerContext::SpecialIntegerContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::SpecialIntegerContext::HEX_INTEGER()
{
    return getToken(anceParser::HEX_INTEGER, 0);
}

tree::TerminalNode* anceParser::SpecialIntegerContext::INTEGER()
{
    return getToken(anceParser::INTEGER, 0);
}

tree::TerminalNode* anceParser::SpecialIntegerContext::BIN_INTEGER()
{
    return getToken(anceParser::BIN_INTEGER, 0);
}

tree::TerminalNode* anceParser::SpecialIntegerContext::OCT_INTEGER()
{
    return getToken(anceParser::OCT_INTEGER, 0);
}

size_t anceParser::SpecialIntegerContext::getRuleIndex() const
{
    return anceParser::RuleSpecialInteger;
}

antlrcpp::Any anceParser::SpecialIntegerContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitSpecialInteger(this);
    else
        return visitor->visitChildren(this);
}

anceParser::SpecialIntegerContext* anceParser::specialInteger()
{
    SpecialIntegerContext* _localctx = _tracker.createInstance<SpecialIntegerContext>(_ctx, getState());
    enterRule(_localctx, 68, anceParser::RuleSpecialInteger);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        setState(338);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::HEX_INTEGER:
            {
                enterOuterAlt(_localctx, 1);
                setState(329);
                match(anceParser::HEX_INTEGER);
                setState(330);
                match(anceParser::T__9);
                setState(331);
                dynamic_cast<SpecialIntegerContext*>(_localctx)->width = match(anceParser::INTEGER);
                break;
            }

            case anceParser::BIN_INTEGER:
            {
                enterOuterAlt(_localctx, 2);
                setState(332);
                match(anceParser::BIN_INTEGER);
                setState(333);
                match(anceParser::T__9);
                setState(334);
                dynamic_cast<SpecialIntegerContext*>(_localctx)->width = match(anceParser::INTEGER);
                break;
            }

            case anceParser::OCT_INTEGER:
            {
                enterOuterAlt(_localctx, 3);
                setState(335);
                match(anceParser::OCT_INTEGER);
                setState(336);
                match(anceParser::T__9);
                setState(337);
                dynamic_cast<SpecialIntegerContext*>(_localctx)->width = match(anceParser::INTEGER);
                break;
            }

            default:
                throw NoViableAltException(this);
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FloatingPointLiteralContext ------------------------------------------------------------------

anceParser::FloatingPointLiteralContext::FloatingPointLiteralContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::FloatingPointLiteralContext::HALF()
{
    return getToken(anceParser::HALF, 0);
}

tree::TerminalNode* anceParser::FloatingPointLiteralContext::SINGLE()
{
    return getToken(anceParser::SINGLE, 0);
}

tree::TerminalNode* anceParser::FloatingPointLiteralContext::DOUBLE()
{
    return getToken(anceParser::DOUBLE, 0);
}

tree::TerminalNode* anceParser::FloatingPointLiteralContext::QUAD()
{
    return getToken(anceParser::QUAD, 0);
}

size_t anceParser::FloatingPointLiteralContext::getRuleIndex() const
{
    return anceParser::RuleFloatingPointLiteral;
}

antlrcpp::Any anceParser::FloatingPointLiteralContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitFloatingPointLiteral(this);
    else
        return visitor->visitChildren(this);
}

anceParser::FloatingPointLiteralContext* anceParser::floatingPointLiteral()
{
    FloatingPointLiteralContext* _localctx = _tracker.createInstance<FloatingPointLiteralContext>(_ctx, getState());
    enterRule(_localctx, 70, anceParser::RuleFloatingPointLiteral);
    size_t _la = 0;

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(340);
        _la = _input->LA(1);
        if (!((((_la & ~0x3fULL) == 0)
               && ((1ULL << _la)
                   & ((1ULL << anceParser::HALF) | (1ULL << anceParser::SINGLE) | (1ULL << anceParser::DOUBLE)
                      | (1ULL << anceParser::QUAD)))
                      != 0)))
        {
            _errHandler->recoverInline(this);
        }
        else
        {
            _errHandler->reportMatch(this);
            consume();
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- BooleanLiteralContext ------------------------------------------------------------------

anceParser::BooleanLiteralContext::BooleanLiteralContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::BooleanLiteralContext::getRuleIndex() const
{
    return anceParser::RuleBooleanLiteral;
}

void anceParser::BooleanLiteralContext::copyFrom(BooleanLiteralContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- TrueContext ------------------------------------------------------------------

anceParser::TrueContext::TrueContext(BooleanLiteralContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::TrueContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitTrue(this);
    else
        return visitor->visitChildren(this);
}
//----------------- FalseContext ------------------------------------------------------------------

anceParser::FalseContext::FalseContext(BooleanLiteralContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::FalseContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitFalse(this);
    else
        return visitor->visitChildren(this);
}
anceParser::BooleanLiteralContext* anceParser::booleanLiteral()
{
    BooleanLiteralContext* _localctx = _tracker.createInstance<BooleanLiteralContext>(_ctx, getState());
    enterRule(_localctx, 72, anceParser::RuleBooleanLiteral);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        setState(344);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__24:
            {
                _localctx =
                    dynamic_cast<BooleanLiteralContext*>(_tracker.createInstance<anceParser::TrueContext>(_localctx));
                enterOuterAlt(_localctx, 1);
                setState(342);
                match(anceParser::T__24);
                break;
            }

            case anceParser::T__25:
            {
                _localctx =
                    dynamic_cast<BooleanLiteralContext*>(_tracker.createInstance<anceParser::FalseContext>(_localctx));
                enterOuterAlt(_localctx, 2);
                setState(343);
                match(anceParser::T__25);
                break;
            }

            default:
                throw NoViableAltException(this);
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- SizeLiteralContext ------------------------------------------------------------------

anceParser::SizeLiteralContext::SizeLiteralContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::SizeLiteralContext::INTEGER()
{
    return getToken(anceParser::INTEGER, 0);
}

size_t anceParser::SizeLiteralContext::getRuleIndex() const
{
    return anceParser::RuleSizeLiteral;
}

antlrcpp::Any anceParser::SizeLiteralContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitSizeLiteral(this);
    else
        return visitor->visitChildren(this);
}

anceParser::SizeLiteralContext* anceParser::sizeLiteral()
{
    SizeLiteralContext* _localctx = _tracker.createInstance<SizeLiteralContext>(_ctx, getState());
    enterRule(_localctx, 74, anceParser::RuleSizeLiteral);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(346);
        match(anceParser::INTEGER);
        setState(349);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx))
        {
            case 1:
            {
                setState(347);
                match(anceParser::T__9);
                setState(348);
                match(anceParser::T__26);
                break;
            }
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- DiffLiteralContext ------------------------------------------------------------------

anceParser::DiffLiteralContext::DiffLiteralContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::DiffLiteralContext::SIGNED_INTEGER()
{
    return getToken(anceParser::SIGNED_INTEGER, 0);
}

size_t anceParser::DiffLiteralContext::getRuleIndex() const
{
    return anceParser::RuleDiffLiteral;
}

antlrcpp::Any anceParser::DiffLiteralContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitDiffLiteral(this);
    else
        return visitor->visitChildren(this);
}

anceParser::DiffLiteralContext* anceParser::diffLiteral()
{
    DiffLiteralContext* _localctx = _tracker.createInstance<DiffLiteralContext>(_ctx, getState());
    enterRule(_localctx, 76, anceParser::RuleDiffLiteral);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(351);
        match(anceParser::SIGNED_INTEGER);
        setState(354);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx))
        {
            case 1:
            {
                setState(352);
                match(anceParser::T__9);
                setState(353);
                match(anceParser::T__27);
                break;
            }
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

anceParser::TypeContext::TypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::TypeContext::getRuleIndex() const
{
    return anceParser::RuleType;
}

void anceParser::TypeContext::copyFrom(TypeContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- IntegerContext ------------------------------------------------------------------

anceParser::IntegerTypeContext* anceParser::IntegerContext::integerType()
{
    return getRuleContext<anceParser::IntegerTypeContext>(0);
}

anceParser::IntegerContext::IntegerContext(TypeContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::IntegerContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitInteger(this);
    else
        return visitor->visitChildren(this);
}
//----------------- ArrayContext ------------------------------------------------------------------

anceParser::ArrayTypeContext* anceParser::ArrayContext::arrayType()
{
    return getRuleContext<anceParser::ArrayTypeContext>(0);
}

anceParser::ArrayContext::ArrayContext(TypeContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::ArrayContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitArray(this);
    else
        return visitor->visitChildren(this);
}
//----------------- KeywordContext ------------------------------------------------------------------

anceParser::KeywordTypeContext* anceParser::KeywordContext::keywordType()
{
    return getRuleContext<anceParser::KeywordTypeContext>(0);
}

anceParser::KeywordContext::KeywordContext(TypeContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::KeywordContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitKeyword(this);
    else
        return visitor->visitChildren(this);
}
//----------------- ReferenceContext ------------------------------------------------------------------

anceParser::TypeContext* anceParser::ReferenceContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::ReferenceContext::ReferenceContext(TypeContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::ReferenceContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitReference(this);
    else
        return visitor->visitChildren(this);
}
//----------------- PointerContext ------------------------------------------------------------------

anceParser::TypeContext* anceParser::PointerContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::PointerContext::PointerContext(TypeContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::PointerContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitPointer(this);
    else
        return visitor->visitChildren(this);
}
anceParser::TypeContext* anceParser::type()
{
    TypeContext* _localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
    enterRule(_localctx, 78, anceParser::RuleType);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        setState(363);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::NATIVE_INTEGER_TYPE:
            {
                _localctx = dynamic_cast<TypeContext*>(_tracker.createInstance<anceParser::IntegerContext>(_localctx));
                enterOuterAlt(_localctx, 1);
                setState(356);
                integerType();
                break;
            }

            case anceParser::T__17:
            {
                _localctx = dynamic_cast<TypeContext*>(_tracker.createInstance<anceParser::ArrayContext>(_localctx));
                enterOuterAlt(_localctx, 2);
                setState(357);
                arrayType();
                break;
            }

            case anceParser::T__26:
            case anceParser::T__27:
            case anceParser::T__30:
            case anceParser::T__31:
            case anceParser::T__32:
            case anceParser::T__33:
            case anceParser::T__34:
            case anceParser::T__35:
            {
                _localctx = dynamic_cast<TypeContext*>(_tracker.createInstance<anceParser::KeywordContext>(_localctx));
                enterOuterAlt(_localctx, 3);
                setState(358);
                keywordType();
                break;
            }

            case anceParser::T__28:
            {
                _localctx = dynamic_cast<TypeContext*>(_tracker.createInstance<anceParser::PointerContext>(_localctx));
                enterOuterAlt(_localctx, 4);
                setState(359);
                match(anceParser::T__28);
                setState(360);
                type();
                break;
            }

            case anceParser::T__29:
            {
                _localctx =
                    dynamic_cast<TypeContext*>(_tracker.createInstance<anceParser::ReferenceContext>(_localctx));
                enterOuterAlt(_localctx, 5);
                setState(361);
                match(anceParser::T__29);
                setState(362);
                type();
                break;
            }

            default:
                throw NoViableAltException(this);
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- IntegerTypeContext ------------------------------------------------------------------

anceParser::IntegerTypeContext::IntegerTypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::IntegerTypeContext::NATIVE_INTEGER_TYPE()
{
    return getToken(anceParser::NATIVE_INTEGER_TYPE, 0);
}

size_t anceParser::IntegerTypeContext::getRuleIndex() const
{
    return anceParser::RuleIntegerType;
}

antlrcpp::Any anceParser::IntegerTypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitIntegerType(this);
    else
        return visitor->visitChildren(this);
}

anceParser::IntegerTypeContext* anceParser::integerType()
{
    IntegerTypeContext* _localctx = _tracker.createInstance<IntegerTypeContext>(_ctx, getState());
    enterRule(_localctx, 80, anceParser::RuleIntegerType);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(365);
        match(anceParser::NATIVE_INTEGER_TYPE);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ArrayTypeContext ------------------------------------------------------------------

anceParser::ArrayTypeContext::ArrayTypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::TypeContext* anceParser::ArrayTypeContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::ArrayTypeContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

tree::TerminalNode* anceParser::ArrayTypeContext::INTEGER()
{
    return getToken(anceParser::INTEGER, 0);
}

size_t anceParser::ArrayTypeContext::getRuleIndex() const
{
    return anceParser::RuleArrayType;
}

antlrcpp::Any anceParser::ArrayTypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitArrayType(this);
    else
        return visitor->visitChildren(this);
}

anceParser::ArrayTypeContext* anceParser::arrayType()
{
    ArrayTypeContext* _localctx = _tracker.createInstance<ArrayTypeContext>(_ctx, getState());
    enterRule(_localctx, 82, anceParser::RuleArrayType);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(367);
        match(anceParser::T__17);
        setState(368);
        type();
        setState(369);
        match(anceParser::SEMICOLON);
        setState(370);
        match(anceParser::INTEGER);
        setState(371);
        match(anceParser::T__18);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- KeywordTypeContext ------------------------------------------------------------------

anceParser::KeywordTypeContext::KeywordTypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::FloatingPointTypeContext* anceParser::KeywordTypeContext::floatingPointType()
{
    return getRuleContext<anceParser::FloatingPointTypeContext>(0);
}

anceParser::TargetDependentTypeContext* anceParser::KeywordTypeContext::targetDependentType()
{
    return getRuleContext<anceParser::TargetDependentTypeContext>(0);
}

anceParser::VoidTypeContext* anceParser::KeywordTypeContext::voidType()
{
    return getRuleContext<anceParser::VoidTypeContext>(0);
}

size_t anceParser::KeywordTypeContext::getRuleIndex() const
{
    return anceParser::RuleKeywordType;
}

antlrcpp::Any anceParser::KeywordTypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitKeywordType(this);
    else
        return visitor->visitChildren(this);
}

anceParser::KeywordTypeContext* anceParser::keywordType()
{
    KeywordTypeContext* _localctx = _tracker.createInstance<KeywordTypeContext>(_ctx, getState());
    enterRule(_localctx, 84, anceParser::RuleKeywordType);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        setState(376);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__30:
            case anceParser::T__31:
            case anceParser::T__32:
            case anceParser::T__33:
            {
                enterOuterAlt(_localctx, 1);
                setState(373);
                floatingPointType();
                break;
            }

            case anceParser::T__26:
            case anceParser::T__27:
            case anceParser::T__34:
            {
                enterOuterAlt(_localctx, 2);
                setState(374);
                targetDependentType();
                break;
            }

            case anceParser::T__35:
            {
                enterOuterAlt(_localctx, 3);
                setState(375);
                voidType();
                break;
            }

            default:
                throw NoViableAltException(this);
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FloatingPointTypeContext ------------------------------------------------------------------

anceParser::FloatingPointTypeContext::FloatingPointTypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::FloatingPointTypeContext::getRuleIndex() const
{
    return anceParser::RuleFloatingPointType;
}

antlrcpp::Any anceParser::FloatingPointTypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitFloatingPointType(this);
    else
        return visitor->visitChildren(this);
}

anceParser::FloatingPointTypeContext* anceParser::floatingPointType()
{
    FloatingPointTypeContext* _localctx = _tracker.createInstance<FloatingPointTypeContext>(_ctx, getState());
    enterRule(_localctx, 86, anceParser::RuleFloatingPointType);
    size_t _la = 0;

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(378);
        _la = _input->LA(1);
        if (!((((_la & ~0x3fULL) == 0)
               && ((1ULL << _la)
                   & ((1ULL << anceParser::T__30) | (1ULL << anceParser::T__31) | (1ULL << anceParser::T__32)
                      | (1ULL << anceParser::T__33)))
                      != 0)))
        {
            _errHandler->recoverInline(this);
        }
        else
        {
            _errHandler->reportMatch(this);
            consume();
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- TargetDependentTypeContext ------------------------------------------------------------------

anceParser::TargetDependentTypeContext::TargetDependentTypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::TargetDependentTypeContext::getRuleIndex() const
{
    return anceParser::RuleTargetDependentType;
}

antlrcpp::Any anceParser::TargetDependentTypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitTargetDependentType(this);
    else
        return visitor->visitChildren(this);
}

anceParser::TargetDependentTypeContext* anceParser::targetDependentType()
{
    TargetDependentTypeContext* _localctx = _tracker.createInstance<TargetDependentTypeContext>(_ctx, getState());
    enterRule(_localctx, 88, anceParser::RuleTargetDependentType);
    size_t _la = 0;

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(380);
        _la = _input->LA(1);
        if (!((((_la & ~0x3fULL) == 0)
               && ((1ULL << _la)
                   & ((1ULL << anceParser::T__26) | (1ULL << anceParser::T__27) | (1ULL << anceParser::T__34)))
                      != 0)))
        {
            _errHandler->recoverInline(this);
        }
        else
        {
            _errHandler->reportMatch(this);
            consume();
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- VoidTypeContext ------------------------------------------------------------------

anceParser::VoidTypeContext::VoidTypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::VoidTypeContext::getRuleIndex() const
{
    return anceParser::RuleVoidType;
}

antlrcpp::Any anceParser::VoidTypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitVoidType(this);
    else
        return visitor->visitChildren(this);
}

anceParser::VoidTypeContext* anceParser::voidType()
{
    VoidTypeContext* _localctx = _tracker.createInstance<VoidTypeContext>(_ctx, getState());
    enterRule(_localctx, 90, anceParser::RuleVoidType);

    auto onExit = finally([=] { exitRule(); });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(382);
        match(anceParser::T__35);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

bool anceParser::sempred(RuleContext* context, size_t ruleIndex, size_t predicateIndex)
{
    switch (ruleIndex)
    {
        case 16:
            return expressionSempred(dynamic_cast<ExpressionContext*>(context), predicateIndex);

        default:
            break;
    }
    return true;
}

bool anceParser::expressionSempred(ExpressionContext* _localctx, size_t predicateIndex)
{
    switch (predicateIndex)
    {
        case 0:
            return precpred(_ctx, 2);

        default:
            break;
    }
    return true;
}

// Static vars and initialization.
std::vector<dfa::DFA>       anceParser::_decisionToDFA;
atn::PredictionContextCache anceParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN              anceParser::_atn;
std::vector<uint16_t> anceParser::_serializedATN;

std::vector<std::string> anceParser::_ruleNames = {"file",
                                                   "variableDeclaration",
                                                   "function",
                                                   "parameters",
                                                   "parameter",
                                                   "accessModifier",
                                                   "statement",
                                                   "expressionStatement",
                                                   "localVariableDefinition",
                                                   "localReferenceDefinition",
                                                   "assignment",
                                                   "assigner",
                                                   "deleteStatement",
                                                   "returnStatement",
                                                   "assignable",
                                                   "variableAssignable",
                                                   "expression",
                                                   "independentExpression",
                                                   "functionCall",
                                                   "arguments",
                                                   "variableAccess",
                                                   "allocation",
                                                   "allocator",
                                                   "roughCast",
                                                   "addressof",
                                                   "bindRef",
                                                   "sizeofType",
                                                   "sizeofExpression",
                                                   "literalExpression",
                                                   "stringLiteral",
                                                   "byteLiteral",
                                                   "integerLiteral",
                                                   "unsignedInteger",
                                                   "signedInteger",
                                                   "specialInteger",
                                                   "floatingPointLiteral",
                                                   "booleanLiteral",
                                                   "sizeLiteral",
                                                   "diffLiteral",
                                                   "type",
                                                   "integerType",
                                                   "arrayType",
                                                   "keywordType",
                                                   "floatingPointType",
                                                   "targetDependentType",
                                                   "voidType"};

std::vector<std::string> anceParser::_literalNames = {"",
                                                      "'('",
                                                      "')'",
                                                      "'{'",
                                                      "'}'",
                                                      "'extern'",
                                                      "','",
                                                      "'public'",
                                                      "'private'",
                                                      "'let'",
                                                      "':'",
                                                      "'ref'",
                                                      "'to'",
                                                      "'<:'",
                                                      "'<-'",
                                                      "':='",
                                                      "'delete'",
                                                      "'return'",
                                                      "'['",
                                                      "']'",
                                                      "'new'",
                                                      "'dynamic'",
                                                      "'automatic'",
                                                      "'addressof'",
                                                      "'sizeof'",
                                                      "'true'",
                                                      "'false'",
                                                      "'size'",
                                                      "'diff'",
                                                      "'*'",
                                                      "'&'",
                                                      "'half'",
                                                      "'single'",
                                                      "'double'",
                                                      "'quad'",
                                                      "'uiptr'",
                                                      "'void'",
                                                      "",
                                                      "",
                                                      "",
                                                      "",
                                                      "",
                                                      "",
                                                      "",
                                                      "",
                                                      "",
                                                      "",
                                                      "",
                                                      "",
                                                      "",
                                                      "'[]'",
                                                      "'const'",
                                                      "",
                                                      "';'"};

std::vector<std::string> anceParser::_symbolicNames = {"",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "NATIVE_INTEGER_TYPE",
                                                       "SIGNED_INTEGER",
                                                       "HEX_INTEGER",
                                                       "BIN_INTEGER",
                                                       "OCT_INTEGER",
                                                       "HALF",
                                                       "SINGLE",
                                                       "DOUBLE",
                                                       "QUAD",
                                                       "DECIMAL",
                                                       "STRING",
                                                       "BYTE",
                                                       "INTEGER",
                                                       "BUFFER",
                                                       "CONST",
                                                       "IDENTIFIER",
                                                       "SEMICOLON",
                                                       "WHITESPACE",
                                                       "BLOCK_COMMENT",
                                                       "LINE_COMMENT"};

dfa::Vocabulary anceParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> anceParser::_tokenNames;

anceParser::Initializer::Initializer()
{
    for (size_t i = 0; i < _symbolicNames.size(); ++i)
    {
        std::string name = _vocabulary.getLiteralName(i);
        if (name.empty()) { name = _vocabulary.getSymbolicName(i); }

        if (name.empty()) { _tokenNames.push_back("<INVALID>"); }
        else
        {
            _tokenNames.push_back(name);
        }
    }

    _serializedATN = {
        0x3,   0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 0x3,   0x3a,  0x183, 0x4,   0x2,   0x9,
        0x2,   0x4,    0x3,    0x9,    0x3,    0x4,    0x4,    0x9,    0x4,    0x4,   0x5,   0x9,   0x5,   0x4,   0x6,
        0x9,   0x6,    0x4,    0x7,    0x9,    0x7,    0x4,    0x8,    0x9,    0x8,   0x4,   0x9,   0x9,   0x9,   0x4,
        0xa,   0x9,    0xa,    0x4,    0xb,    0x9,    0xb,    0x4,    0xc,    0x9,   0xc,   0x4,   0xd,   0x9,   0xd,
        0x4,   0xe,    0x9,    0xe,    0x4,    0xf,    0x9,    0xf,    0x4,    0x10,  0x9,   0x10,  0x4,   0x11,  0x9,
        0x11,  0x4,    0x12,   0x9,    0x12,   0x4,    0x13,   0x9,    0x13,   0x4,   0x14,  0x9,   0x14,  0x4,   0x15,
        0x9,   0x15,   0x4,    0x16,   0x9,    0x16,   0x4,    0x17,   0x9,    0x17,  0x4,   0x18,  0x9,   0x18,  0x4,
        0x19,  0x9,    0x19,   0x4,    0x1a,   0x9,    0x1a,   0x4,    0x1b,   0x9,   0x1b,  0x4,   0x1c,  0x9,   0x1c,
        0x4,   0x1d,   0x9,    0x1d,   0x4,    0x1e,   0x9,    0x1e,   0x4,    0x1f,  0x9,   0x1f,  0x4,   0x20,  0x9,
        0x20,  0x4,    0x21,   0x9,    0x21,   0x4,    0x22,   0x9,    0x22,   0x4,   0x23,  0x9,   0x23,  0x4,   0x24,
        0x9,   0x24,   0x4,    0x25,   0x9,    0x25,   0x4,    0x26,   0x9,    0x26,  0x4,   0x27,  0x9,   0x27,  0x4,
        0x28,  0x9,    0x28,   0x4,    0x29,   0x9,    0x29,   0x4,    0x2a,   0x9,   0x2a,  0x4,   0x2b,  0x9,   0x2b,
        0x4,   0x2c,   0x9,    0x2c,   0x4,    0x2d,   0x9,    0x2d,   0x4,    0x2e,  0x9,   0x2e,  0x4,   0x2f,  0x9,
        0x2f,  0x3,    0x2,    0x3,    0x2,    0x7,    0x2,    0x61,   0xa,    0x2,   0xc,   0x2,   0xe,   0x2,   0x64,
        0xb,   0x2,    0x3,    0x2,    0x3,    0x2,    0x3,    0x3,    0x3,    0x3,   0x5,   0x3,   0x6a,  0xa,   0x3,
        0x3,   0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,   0x5,   0x3,   0x71,  0xa,   0x3,
        0x3,   0x3,    0x3,    0x3,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,   0x3,   0x4,   0x3,   0x4,   0x3,
        0x4,   0x3,    0x4,    0x3,    0x4,    0x7,    0x4,    0x7d,   0xa,    0x4,   0xc,   0x4,   0xe,   0x4,   0x80,
        0xb,   0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,   0x3,   0x4,   0x3,   0x4,   0x3,
        0x4,   0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x5,    0x4,    0x8c,  0xa,   0x4,   0x3,   0x5,   0x3,
        0x5,   0x3,    0x5,    0x7,    0x5,    0x91,   0xa,    0x5,    0xc,    0x5,   0xe,   0x5,   0x94,  0xb,   0x5,
        0x5,   0x5,    0x96,   0xa,    0x5,    0x3,    0x6,    0x3,    0x6,    0x3,   0x6,   0x3,   0x7,   0x3,   0x7,
        0x5,   0x7,    0x9d,   0xa,    0x7,    0x3,    0x8,    0x3,    0x8,    0x3,   0x8,   0x3,   0x8,   0x3,   0x8,
        0x3,   0x8,    0x5,    0x8,    0xa5,   0xa,    0x8,    0x3,    0x9,    0x3,   0x9,   0x3,   0x9,   0x3,   0xa,
        0x3,   0xa,    0x3,    0xa,    0x3,    0xa,    0x3,    0xa,    0x5,    0xa,   0xaf,  0xa,   0xa,   0x3,   0xa,
        0x3,   0xa,    0x3,    0xb,    0x3,    0xb,    0x3,    0xb,    0x3,    0xb,   0x3,   0xb,   0x3,   0xb,   0x3,
        0xb,   0x3,    0xb,    0x3,    0xb,    0x3,    0xb,    0x3,    0xb,    0x3,   0xb,   0x3,   0xb,   0x3,   0xb,
        0x3,   0xb,    0x3,    0xb,    0x3,    0xb,    0x5,    0xb,    0xc4,   0xa,   0xb,   0x3,   0xc,   0x3,   0xc,
        0x3,   0xc,    0x3,    0xc,    0x3,    0xc,    0x3,    0xd,    0x3,    0xd,   0x3,   0xd,   0x5,   0xd,   0xce,
        0xa,   0xd,    0x3,    0xe,    0x3,    0xe,    0x5,    0xe,    0xd2,   0xa,   0xe,   0x3,   0xe,   0x3,   0xe,
        0x3,   0xe,    0x3,    0xf,    0x3,    0xf,    0x5,    0xf,    0xd9,   0xa,   0xf,   0x3,   0xf,   0x3,   0xf,
        0x3,   0x10,   0x3,    0x10,   0x3,    0x11,   0x3,    0x11,   0x3,    0x12,  0x3,   0x12,  0x3,   0x12,  0x3,
        0x12,  0x3,    0x12,   0x3,    0x12,   0x3,    0x12,   0x3,    0x12,   0x3,   0x12,  0x3,   0x12,  0x5,   0x12,
        0xeb,  0xa,    0x12,   0x3,    0x12,   0x3,    0x12,   0x3,    0x12,   0x3,   0x12,  0x3,   0x12,  0x7,   0x12,
        0xf2,  0xa,    0x12,   0xc,    0x12,   0xe,    0x12,   0xf5,   0xb,    0x12,  0x3,   0x13,  0x3,   0x13,  0x3,
        0x14,  0x3,    0x14,   0x3,    0x14,   0x3,    0x14,   0x3,    0x14,   0x3,   0x15,  0x3,   0x15,  0x3,   0x15,
        0x7,   0x15,   0x101,  0xa,    0x15,   0xc,    0x15,   0xe,    0x15,   0x104, 0xb,   0x15,  0x5,   0x15,  0x106,
        0xa,   0x15,   0x3,    0x16,   0x3,    0x16,   0x3,    0x17,   0x3,    0x17,  0x3,   0x17,  0x3,   0x17,  0x3,
        0x17,  0x5,    0x17,   0x10f,  0xa,    0x17,   0x3,    0x17,   0x3,    0x17,  0x3,   0x17,  0x3,   0x18,  0x3,
        0x18,  0x5,    0x18,   0x116,  0xa,    0x18,   0x3,    0x19,   0x3,    0x19,  0x3,   0x19,  0x3,   0x19,  0x3,
        0x19,  0x3,    0x1a,   0x3,    0x1a,   0x3,    0x1a,   0x3,    0x1b,   0x3,   0x1b,  0x3,   0x1b,  0x3,   0x1b,
        0x3,   0x1b,   0x5,    0x1b,   0x125,  0xa,    0x1b,   0x3,    0x1c,   0x3,   0x1c,  0x3,   0x1c,  0x3,   0x1d,
        0x3,   0x1d,   0x3,    0x1d,   0x3,    0x1d,   0x3,    0x1d,   0x3,    0x1e,  0x3,   0x1e,  0x3,   0x1e,  0x3,
        0x1e,  0x3,    0x1e,   0x3,    0x1e,   0x3,    0x1e,   0x5,    0x1e,   0x136, 0xa,   0x1e,  0x3,   0x1f,  0x5,
        0x1f,  0x139,  0xa,    0x1f,   0x3,    0x1f,   0x3,    0x1f,   0x3,    0x20,  0x3,   0x20,  0x3,   0x21,  0x3,
        0x21,  0x3,    0x21,   0x5,    0x21,   0x142,  0xa,    0x21,   0x3,    0x22,  0x3,   0x22,  0x3,   0x22,  0x3,
        0x22,  0x3,    0x23,   0x3,    0x23,   0x3,    0x23,   0x3,    0x23,   0x3,   0x24,  0x3,   0x24,  0x3,   0x24,
        0x3,   0x24,   0x3,    0x24,   0x3,    0x24,   0x3,    0x24,   0x3,    0x24,  0x3,   0x24,  0x5,   0x24,  0x155,
        0xa,   0x24,   0x3,    0x25,   0x3,    0x25,   0x3,    0x26,   0x3,    0x26,  0x5,   0x26,  0x15b, 0xa,   0x26,
        0x3,   0x27,   0x3,    0x27,   0x3,    0x27,   0x5,    0x27,   0x160,  0xa,   0x27,  0x3,   0x28,  0x3,   0x28,
        0x3,   0x28,   0x5,    0x28,   0x165,  0xa,    0x28,   0x3,    0x29,   0x3,   0x29,  0x3,   0x29,  0x3,   0x29,
        0x3,   0x29,   0x3,    0x29,   0x3,    0x29,   0x5,    0x29,   0x16e,  0xa,   0x29,  0x3,   0x2a,  0x3,   0x2a,
        0x3,   0x2b,   0x3,    0x2b,   0x3,    0x2b,   0x3,    0x2b,   0x3,    0x2b,  0x3,   0x2b,  0x3,   0x2c,  0x3,
        0x2c,  0x3,    0x2c,   0x5,    0x2c,   0x17b,  0xa,    0x2c,   0x3,    0x2d,  0x3,   0x2d,  0x3,   0x2e,  0x3,
        0x2e,  0x3,    0x2f,   0x3,    0x2f,   0x3,    0x2f,   0x2,    0x3,    0x22,  0x30,  0x2,   0x4,   0x6,   0x8,
        0xa,   0xc,    0xe,    0x10,   0x12,   0x14,   0x16,   0x18,   0x1a,   0x1c,  0x1e,  0x20,  0x22,  0x24,  0x26,
        0x28,  0x2a,   0x2c,   0x2e,   0x30,   0x32,   0x34,   0x36,   0x38,   0x3a,  0x3c,  0x3e,  0x40,  0x42,  0x44,
        0x46,  0x48,   0x4a,   0x4c,   0x4e,   0x50,   0x52,   0x54,   0x56,   0x58,  0x5a,  0x5c,  0x2,   0x5,   0x3,
        0x2,   0x2c,   0x2f,   0x3,    0x2,    0x21,   0x24,   0x4,    0x2,    0x1d,  0x1e,  0x25,  0x25,  0x2,   0x18a,
        0x2,   0x62,   0x3,    0x2,    0x2,    0x2,    0x4,    0x67,   0x3,    0x2,   0x2,   0x2,   0x6,   0x8b,  0x3,
        0x2,   0x2,    0x2,    0x8,    0x95,   0x3,    0x2,    0x2,    0x2,    0xa,   0x97,  0x3,   0x2,   0x2,   0x2,
        0xc,   0x9c,   0x3,    0x2,    0x2,    0x2,    0xe,    0xa4,   0x3,    0x2,   0x2,   0x2,   0x10,  0xa6,  0x3,
        0x2,   0x2,    0x2,    0x12,   0xa9,   0x3,    0x2,    0x2,    0x2,    0x14,  0xc3,  0x3,   0x2,   0x2,   0x2,
        0x16,  0xc5,   0x3,    0x2,    0x2,    0x2,    0x18,   0xcd,   0x3,    0x2,   0x2,   0x2,   0x1a,  0xcf,  0x3,
        0x2,   0x2,    0x2,    0x1c,   0xd6,   0x3,    0x2,    0x2,    0x2,    0x1e,  0xdc,  0x3,   0x2,   0x2,   0x2,
        0x20,  0xde,   0x3,    0x2,    0x2,    0x2,    0x22,   0xea,   0x3,    0x2,   0x2,   0x2,   0x24,  0xf6,  0x3,
        0x2,   0x2,    0x2,    0x26,   0xf8,   0x3,    0x2,    0x2,    0x2,    0x28,  0x105, 0x3,   0x2,   0x2,   0x2,
        0x2a,  0x107,  0x3,    0x2,    0x2,    0x2,    0x2c,   0x109,  0x3,    0x2,   0x2,   0x2,   0x2e,  0x115, 0x3,
        0x2,   0x2,    0x2,    0x30,   0x117,  0x3,    0x2,    0x2,    0x2,    0x32,  0x11c, 0x3,   0x2,   0x2,   0x2,
        0x34,  0x124,  0x3,    0x2,    0x2,    0x2,    0x36,   0x126,  0x3,    0x2,   0x2,   0x2,   0x38,  0x129, 0x3,
        0x2,   0x2,    0x2,    0x3a,   0x135,  0x3,    0x2,    0x2,    0x2,    0x3c,  0x138, 0x3,   0x2,   0x2,   0x2,
        0x3e,  0x13c,  0x3,    0x2,    0x2,    0x2,    0x40,   0x141,  0x3,    0x2,   0x2,   0x2,   0x42,  0x143, 0x3,
        0x2,   0x2,    0x2,    0x44,   0x147,  0x3,    0x2,    0x2,    0x2,    0x46,  0x154, 0x3,   0x2,   0x2,   0x2,
        0x48,  0x156,  0x3,    0x2,    0x2,    0x2,    0x4a,   0x15a,  0x3,    0x2,   0x2,   0x2,   0x4c,  0x15c, 0x3,
        0x2,   0x2,    0x2,    0x4e,   0x161,  0x3,    0x2,    0x2,    0x2,    0x50,  0x16d, 0x3,   0x2,   0x2,   0x2,
        0x52,  0x16f,  0x3,    0x2,    0x2,    0x2,    0x54,   0x171,  0x3,    0x2,   0x2,   0x2,   0x56,  0x17a, 0x3,
        0x2,   0x2,    0x2,    0x58,   0x17c,  0x3,    0x2,    0x2,    0x2,    0x5a,  0x17e, 0x3,   0x2,   0x2,   0x2,
        0x5c,  0x180,  0x3,    0x2,    0x2,    0x2,    0x5e,   0x61,   0x5,    0x4,   0x3,   0x2,   0x5f,  0x61,  0x5,
        0x6,   0x4,    0x2,    0x60,   0x5e,   0x3,    0x2,    0x2,    0x2,    0x60,  0x5f,  0x3,   0x2,   0x2,   0x2,
        0x61,  0x64,   0x3,    0x2,    0x2,    0x2,    0x62,   0x60,   0x3,    0x2,   0x2,   0x2,   0x62,  0x63,  0x3,
        0x2,   0x2,    0x2,    0x63,   0x65,   0x3,    0x2,    0x2,    0x2,    0x64,  0x62,  0x3,   0x2,   0x2,   0x2,
        0x65,  0x66,   0x7,    0x2,    0x2,    0x3,    0x66,   0x3,    0x3,    0x2,   0x2,   0x2,   0x67,  0x69,  0x5,
        0xc,   0x7,    0x2,    0x68,   0x6a,   0x7,    0x35,   0x2,    0x2,    0x69,  0x68,  0x3,   0x2,   0x2,   0x2,
        0x69,  0x6a,   0x3,    0x2,    0x2,    0x2,    0x6a,   0x6b,   0x3,    0x2,   0x2,   0x2,   0x6b,  0x6c,  0x5,
        0x50,  0x29,   0x2,    0x6c,   0x70,   0x7,    0x36,   0x2,    0x2,    0x6d,  0x6e,  0x5,   0x18,  0xd,   0x2,
        0x6e,  0x6f,   0x5,    0x3a,   0x1e,   0x2,    0x6f,   0x71,   0x3,    0x2,   0x2,   0x2,   0x70,  0x6d,  0x3,
        0x2,   0x2,    0x2,    0x70,   0x71,   0x3,    0x2,    0x2,    0x2,    0x71,  0x72,  0x3,   0x2,   0x2,   0x2,
        0x72,  0x73,   0x7,    0x37,   0x2,    0x2,    0x73,   0x5,    0x3,    0x2,   0x2,   0x2,   0x74,  0x75,  0x5,
        0xc,   0x7,    0x2,    0x75,   0x76,   0x5,    0x50,   0x29,   0x2,    0x76,  0x77,  0x7,   0x36,  0x2,   0x2,
        0x77,  0x78,   0x7,    0x3,    0x2,    0x2,    0x78,   0x79,   0x5,    0x8,   0x5,   0x2,   0x79,  0x7a,  0x7,
        0x4,   0x2,    0x2,    0x7a,   0x7e,   0x7,    0x5,    0x2,    0x2,    0x7b,  0x7d,  0x5,   0xe,   0x8,   0x2,
        0x7c,  0x7b,   0x3,    0x2,    0x2,    0x2,    0x7d,   0x80,   0x3,    0x2,   0x2,   0x2,   0x7e,  0x7c,  0x3,
        0x2,   0x2,    0x2,    0x7e,   0x7f,   0x3,    0x2,    0x2,    0x2,    0x7f,  0x81,  0x3,   0x2,   0x2,   0x2,
        0x80,  0x7e,   0x3,    0x2,    0x2,    0x2,    0x81,   0x82,   0x7,    0x6,   0x2,   0x2,   0x82,  0x8c,  0x3,
        0x2,   0x2,    0x2,    0x83,   0x84,   0x7,    0x7,    0x2,    0x2,    0x84,  0x85,  0x5,   0x50,  0x29,  0x2,
        0x85,  0x86,   0x7,    0x36,   0x2,    0x2,    0x86,   0x87,   0x7,    0x3,   0x2,   0x2,   0x87,  0x88,  0x5,
        0x8,   0x5,    0x2,    0x88,   0x89,   0x7,    0x4,    0x2,    0x2,    0x89,  0x8a,  0x7,   0x37,  0x2,   0x2,
        0x8a,  0x8c,   0x3,    0x2,    0x2,    0x2,    0x8b,   0x74,   0x3,    0x2,   0x2,   0x2,   0x8b,  0x83,  0x3,
        0x2,   0x2,    0x2,    0x8c,   0x7,    0x3,    0x2,    0x2,    0x2,    0x8d,  0x92,  0x5,   0xa,   0x6,   0x2,
        0x8e,  0x8f,   0x7,    0x8,    0x2,    0x2,    0x8f,   0x91,   0x5,    0xa,   0x6,   0x2,   0x90,  0x8e,  0x3,
        0x2,   0x2,    0x2,    0x91,   0x94,   0x3,    0x2,    0x2,    0x2,    0x92,  0x90,  0x3,   0x2,   0x2,   0x2,
        0x92,  0x93,   0x3,    0x2,    0x2,    0x2,    0x93,   0x96,   0x3,    0x2,   0x2,   0x2,   0x94,  0x92,  0x3,
        0x2,   0x2,    0x2,    0x95,   0x8d,   0x3,    0x2,    0x2,    0x2,    0x95,  0x96,  0x3,   0x2,   0x2,   0x2,
        0x96,  0x9,    0x3,    0x2,    0x2,    0x2,    0x97,   0x98,   0x5,    0x50,  0x29,  0x2,   0x98,  0x99,  0x7,
        0x36,  0x2,    0x2,    0x99,   0xb,    0x3,    0x2,    0x2,    0x2,    0x9a,  0x9d,  0x7,   0x9,   0x2,   0x2,
        0x9b,  0x9d,   0x7,    0xa,    0x2,    0x2,    0x9c,   0x9a,   0x3,    0x2,   0x2,   0x2,   0x9c,  0x9b,  0x3,
        0x2,   0x2,    0x2,    0x9d,   0xd,    0x3,    0x2,    0x2,    0x2,    0x9e,  0xa5,  0x5,   0x10,  0x9,   0x2,
        0x9f,  0xa5,   0x5,    0x12,   0xa,    0x2,    0xa0,   0xa5,   0x5,    0x14,  0xb,   0x2,   0xa1,  0xa5,  0x5,
        0x16,  0xc,    0x2,    0xa2,   0xa5,   0x5,    0x1a,   0xe,    0x2,    0xa3,  0xa5,  0x5,   0x1c,  0xf,   0x2,
        0xa4,  0x9e,   0x3,    0x2,    0x2,    0x2,    0xa4,   0x9f,   0x3,    0x2,   0x2,   0x2,   0xa4,  0xa0,  0x3,
        0x2,   0x2,    0x2,    0xa4,   0xa1,   0x3,    0x2,    0x2,    0x2,    0xa4,  0xa2,  0x3,   0x2,   0x2,   0x2,
        0xa4,  0xa3,   0x3,    0x2,    0x2,    0x2,    0xa5,   0xf,    0x3,    0x2,   0x2,   0x2,   0xa6,  0xa7,  0x5,
        0x24,  0x13,   0x2,    0xa7,   0xa8,   0x7,    0x37,   0x2,    0x2,    0xa8,  0x11,  0x3,   0x2,   0x2,   0x2,
        0xa9,  0xaa,   0x5,    0x50,   0x29,   0x2,    0xaa,   0xae,   0x7,    0x36,  0x2,   0x2,   0xab,  0xac,  0x5,
        0x18,  0xd,    0x2,    0xac,   0xad,   0x5,    0x22,   0x12,   0x2,    0xad,  0xaf,  0x3,   0x2,   0x2,   0x2,
        0xae,  0xab,   0x3,    0x2,    0x2,    0x2,    0xae,   0xaf,   0x3,    0x2,   0x2,   0x2,   0xaf,  0xb0,  0x3,
        0x2,   0x2,    0x2,    0xb0,   0xb1,   0x7,    0x37,   0x2,    0x2,    0xb1,  0x13,  0x3,   0x2,   0x2,   0x2,
        0xb2,  0xb3,   0x7,    0xb,    0x2,    0x2,    0xb3,   0xb4,   0x7,    0x36,  0x2,   0x2,   0xb4,  0xb5,  0x7,
        0xc,   0x2,    0x2,    0xb5,   0xb6,   0x5,    0x50,   0x29,   0x2,    0xb6,  0xb7,  0x7,   0xd,   0x2,   0x2,
        0xb7,  0xb8,   0x5,    0x22,   0x12,   0x2,    0xb8,   0xb9,   0x7,    0x37,  0x2,   0x2,   0xb9,  0xc4,  0x3,
        0x2,   0x2,    0x2,    0xba,   0xbb,   0x7,    0xb,    0x2,    0x2,    0xbb,  0xbc,  0x7,   0x36,  0x2,   0x2,
        0xbc,  0xbd,   0x7,    0xc,    0x2,    0x2,    0xbd,   0xbe,   0x5,    0x50,  0x29,  0x2,   0xbe,  0xbf,  0x7,
        0xd,   0x2,    0x2,    0xbf,   0xc0,   0x7,    0xe,    0x2,    0x2,    0xc0,  0xc1,  0x5,   0x22,  0x12,  0x2,
        0xc1,  0xc2,   0x7,    0x37,   0x2,    0x2,    0xc2,   0xc4,   0x3,    0x2,   0x2,   0x2,   0xc3,  0xb2,  0x3,
        0x2,   0x2,    0x2,    0xc3,   0xba,   0x3,    0x2,    0x2,    0x2,    0xc4,  0x15,  0x3,   0x2,   0x2,   0x2,
        0xc5,  0xc6,   0x5,    0x1e,   0x10,   0x2,    0xc6,   0xc7,   0x5,    0x18,  0xd,   0x2,   0xc7,  0xc8,  0x5,
        0x22,  0x12,   0x2,    0xc8,   0xc9,   0x7,    0x37,   0x2,    0x2,    0xc9,  0x17,  0x3,   0x2,   0x2,   0x2,
        0xca,  0xce,   0x7,    0xf,    0x2,    0x2,    0xcb,   0xce,   0x7,    0x10,  0x2,   0x2,   0xcc,  0xce,  0x7,
        0x11,  0x2,    0x2,    0xcd,   0xca,   0x3,    0x2,    0x2,    0x2,    0xcd,  0xcb,  0x3,   0x2,   0x2,   0x2,
        0xcd,  0xcc,   0x3,    0x2,    0x2,    0x2,    0xce,   0x19,   0x3,    0x2,   0x2,   0x2,   0xcf,  0xd1,  0x7,
        0x12,  0x2,    0x2,    0xd0,   0xd2,   0x7,    0x34,   0x2,    0x2,    0xd1,  0xd0,  0x3,   0x2,   0x2,   0x2,
        0xd1,  0xd2,   0x3,    0x2,    0x2,    0x2,    0xd2,   0xd3,   0x3,    0x2,   0x2,   0x2,   0xd3,  0xd4,  0x5,
        0x22,  0x12,   0x2,    0xd4,   0xd5,   0x7,    0x37,   0x2,    0x2,    0xd5,  0x1b,  0x3,   0x2,   0x2,   0x2,
        0xd6,  0xd8,   0x7,    0x13,   0x2,    0x2,    0xd7,   0xd9,   0x5,    0x22,  0x12,  0x2,   0xd8,  0xd7,  0x3,
        0x2,   0x2,    0x2,    0xd8,   0xd9,   0x3,    0x2,    0x2,    0x2,    0xd9,  0xda,  0x3,   0x2,   0x2,   0x2,
        0xda,  0xdb,   0x7,    0x37,   0x2,    0x2,    0xdb,   0x1d,   0x3,    0x2,   0x2,   0x2,   0xdc,  0xdd,  0x5,
        0x20,  0x11,   0x2,    0xdd,   0x1f,   0x3,    0x2,    0x2,    0x2,    0xde,  0xdf,  0x7,   0x36,  0x2,   0x2,
        0xdf,  0x21,   0x3,    0x2,    0x2,    0x2,    0xe0,   0xe1,   0x8,    0x12,  0x1,   0x2,   0xe1,  0xeb,  0x5,
        0x2a,  0x16,   0x2,    0xe2,   0xeb,   0x5,    0x2c,   0x17,   0x2,    0xe3,  0xeb,  0x5,   0x30,  0x19,  0x2,
        0xe4,  0xeb,   0x5,    0x32,   0x1a,   0x2,    0xe5,   0xeb,   0x5,    0x34,  0x1b,  0x2,   0xe6,  0xeb,  0x5,
        0x36,  0x1c,   0x2,    0xe7,   0xeb,   0x5,    0x38,   0x1d,   0x2,    0xe8,  0xeb,  0x5,   0x3a,  0x1e,  0x2,
        0xe9,  0xeb,   0x5,    0x24,   0x13,   0x2,    0xea,   0xe0,   0x3,    0x2,   0x2,   0x2,   0xea,  0xe2,  0x3,
        0x2,   0x2,    0x2,    0xea,   0xe3,   0x3,    0x2,    0x2,    0x2,    0xea,  0xe4,  0x3,   0x2,   0x2,   0x2,
        0xea,  0xe5,   0x3,    0x2,    0x2,    0x2,    0xea,   0xe6,   0x3,    0x2,   0x2,   0x2,   0xea,  0xe7,  0x3,
        0x2,   0x2,    0x2,    0xea,   0xe8,   0x3,    0x2,    0x2,    0x2,    0xea,  0xe9,  0x3,   0x2,   0x2,   0x2,
        0xeb,  0xf3,   0x3,    0x2,    0x2,    0x2,    0xec,   0xed,   0xc,    0x4,   0x2,   0x2,   0xed,  0xee,  0x7,
        0x14,  0x2,    0x2,    0xee,   0xef,   0x5,    0x22,   0x12,   0x2,    0xef,  0xf0,  0x7,   0x15,  0x2,   0x2,
        0xf0,  0xf2,   0x3,    0x2,    0x2,    0x2,    0xf1,   0xec,   0x3,    0x2,   0x2,   0x2,   0xf2,  0xf5,  0x3,
        0x2,   0x2,    0x2,    0xf3,   0xf1,   0x3,    0x2,    0x2,    0x2,    0xf3,  0xf4,  0x3,   0x2,   0x2,   0x2,
        0xf4,  0x23,   0x3,    0x2,    0x2,    0x2,    0xf5,   0xf3,   0x3,    0x2,   0x2,   0x2,   0xf6,  0xf7,  0x5,
        0x26,  0x14,   0x2,    0xf7,   0x25,   0x3,    0x2,    0x2,    0x2,    0xf8,  0xf9,  0x7,   0x36,  0x2,   0x2,
        0xf9,  0xfa,   0x7,    0x3,    0x2,    0x2,    0xfa,   0xfb,   0x5,    0x28,  0x15,  0x2,   0xfb,  0xfc,  0x7,
        0x4,   0x2,    0x2,    0xfc,   0x27,   0x3,    0x2,    0x2,    0x2,    0xfd,  0x102, 0x5,   0x22,  0x12,  0x2,
        0xfe,  0xff,   0x7,    0x8,    0x2,    0x2,    0xff,   0x101,  0x5,    0x22,  0x12,  0x2,   0x100, 0xfe,  0x3,
        0x2,   0x2,    0x2,    0x101,  0x104,  0x3,    0x2,    0x2,    0x2,    0x102, 0x100, 0x3,   0x2,   0x2,   0x2,
        0x102, 0x103,  0x3,    0x2,    0x2,    0x2,    0x103,  0x106,  0x3,    0x2,   0x2,   0x2,   0x104, 0x102, 0x3,
        0x2,   0x2,    0x2,    0x105,  0xfd,   0x3,    0x2,    0x2,    0x2,    0x105, 0x106, 0x3,   0x2,   0x2,   0x2,
        0x106, 0x29,   0x3,    0x2,    0x2,    0x2,    0x107,  0x108,  0x7,    0x36,  0x2,   0x2,   0x108, 0x2b,  0x3,
        0x2,   0x2,    0x2,    0x109,  0x10e,  0x7,    0x16,   0x2,    0x2,    0x10a, 0x10b, 0x7,   0x14,  0x2,   0x2,
        0x10b, 0x10c,  0x5,    0x22,   0x12,   0x2,    0x10c,  0x10d,  0x7,    0x15,  0x2,   0x2,   0x10d, 0x10f, 0x3,
        0x2,   0x2,    0x2,    0x10e,  0x10a,  0x3,    0x2,    0x2,    0x2,    0x10e, 0x10f, 0x3,   0x2,   0x2,   0x2,
        0x10f, 0x110,  0x3,    0x2,    0x2,    0x2,    0x110,  0x111,  0x5,    0x2e,  0x18,  0x2,   0x111, 0x112, 0x5,
        0x50,  0x29,   0x2,    0x112,  0x2d,   0x3,    0x2,    0x2,    0x2,    0x113, 0x116, 0x7,   0x17,  0x2,   0x2,
        0x114, 0x116,  0x7,    0x18,   0x2,    0x2,    0x115,  0x113,  0x3,    0x2,   0x2,   0x2,   0x115, 0x114, 0x3,
        0x2,   0x2,    0x2,    0x116,  0x2f,   0x3,    0x2,    0x2,    0x2,    0x117, 0x118, 0x7,   0x5,   0x2,   0x2,
        0x118, 0x119,  0x5,    0x50,   0x29,   0x2,    0x119,  0x11a,  0x7,    0x6,   0x2,   0x2,   0x11a, 0x11b, 0x5,
        0x22,  0x12,   0x2,    0x11b,  0x31,   0x3,    0x2,    0x2,    0x2,    0x11c, 0x11d, 0x7,   0x19,  0x2,   0x2,
        0x11d, 0x11e,  0x5,    0x22,   0x12,   0x2,    0x11e,  0x33,   0x3,    0x2,   0x2,   0x2,   0x11f, 0x120, 0x7,
        0xd,   0x2,    0x2,    0x120,  0x125,  0x5,    0x22,   0x12,   0x2,    0x121, 0x122, 0x7,   0xd,   0x2,   0x2,
        0x122, 0x123,  0x7,    0xe,    0x2,    0x2,    0x123,  0x125,  0x5,    0x22,  0x12,  0x2,   0x124, 0x11f, 0x3,
        0x2,   0x2,    0x2,    0x124,  0x121,  0x3,    0x2,    0x2,    0x2,    0x125, 0x35,  0x3,   0x2,   0x2,   0x2,
        0x126, 0x127,  0x7,    0x1a,   0x2,    0x2,    0x127,  0x128,  0x5,    0x50,  0x29,  0x2,   0x128, 0x37,  0x3,
        0x2,   0x2,    0x2,    0x129,  0x12a,  0x7,    0x1a,   0x2,    0x2,    0x12a, 0x12b, 0x7,   0x3,   0x2,   0x2,
        0x12b, 0x12c,  0x5,    0x22,   0x12,   0x2,    0x12c,  0x12d,  0x7,    0x4,   0x2,   0x2,   0x12d, 0x39,  0x3,
        0x2,   0x2,    0x2,    0x12e,  0x136,  0x5,    0x3c,   0x1f,   0x2,    0x12f, 0x136, 0x5,   0x3e,  0x20,  0x2,
        0x130, 0x136,  0x5,    0x40,   0x21,   0x2,    0x131,  0x136,  0x5,    0x48,  0x25,  0x2,   0x132, 0x136, 0x5,
        0x4a,  0x26,   0x2,    0x133,  0x136,  0x5,    0x4c,   0x27,   0x2,    0x134, 0x136, 0x5,   0x4e,  0x28,  0x2,
        0x135, 0x12e,  0x3,    0x2,    0x2,    0x2,    0x135,  0x12f,  0x3,    0x2,   0x2,   0x2,   0x135, 0x130, 0x3,
        0x2,   0x2,    0x2,    0x135,  0x131,  0x3,    0x2,    0x2,    0x2,    0x135, 0x132, 0x3,   0x2,   0x2,   0x2,
        0x135, 0x133,  0x3,    0x2,    0x2,    0x2,    0x135,  0x134,  0x3,    0x2,   0x2,   0x2,   0x136, 0x3b,  0x3,
        0x2,   0x2,    0x2,    0x137,  0x139,  0x7,    0x36,   0x2,    0x2,    0x138, 0x137, 0x3,   0x2,   0x2,   0x2,
        0x138, 0x139,  0x3,    0x2,    0x2,    0x2,    0x139,  0x13a,  0x3,    0x2,   0x2,   0x2,   0x13a, 0x13b, 0x7,
        0x31,  0x2,    0x2,    0x13b,  0x3d,   0x3,    0x2,    0x2,    0x2,    0x13c, 0x13d, 0x7,   0x32,  0x2,   0x2,
        0x13d, 0x3f,   0x3,    0x2,    0x2,    0x2,    0x13e,  0x142,  0x5,    0x42,  0x22,  0x2,   0x13f, 0x142, 0x5,
        0x44,  0x23,   0x2,    0x140,  0x142,  0x5,    0x46,   0x24,   0x2,    0x141, 0x13e, 0x3,   0x2,   0x2,   0x2,
        0x141, 0x13f,  0x3,    0x2,    0x2,    0x2,    0x141,  0x140,  0x3,    0x2,   0x2,   0x2,   0x142, 0x41,  0x3,
        0x2,   0x2,    0x2,    0x143,  0x144,  0x7,    0x33,   0x2,    0x2,    0x144, 0x145, 0x7,   0xc,   0x2,   0x2,
        0x145, 0x146,  0x7,    0x33,   0x2,    0x2,    0x146,  0x43,   0x3,    0x2,   0x2,   0x2,   0x147, 0x148, 0x7,
        0x28,  0x2,    0x2,    0x148,  0x149,  0x7,    0xc,    0x2,    0x2,    0x149, 0x14a, 0x7,   0x33,  0x2,   0x2,
        0x14a, 0x45,   0x3,    0x2,    0x2,    0x2,    0x14b,  0x14c,  0x7,    0x29,  0x2,   0x2,   0x14c, 0x14d, 0x7,
        0xc,   0x2,    0x2,    0x14d,  0x155,  0x7,    0x33,   0x2,    0x2,    0x14e, 0x14f, 0x7,   0x2a,  0x2,   0x2,
        0x14f, 0x150,  0x7,    0xc,    0x2,    0x2,    0x150,  0x155,  0x7,    0x33,  0x2,   0x2,   0x151, 0x152, 0x7,
        0x2b,  0x2,    0x2,    0x152,  0x153,  0x7,    0xc,    0x2,    0x2,    0x153, 0x155, 0x7,   0x33,  0x2,   0x2,
        0x154, 0x14b,  0x3,    0x2,    0x2,    0x2,    0x154,  0x14e,  0x3,    0x2,   0x2,   0x2,   0x154, 0x151, 0x3,
        0x2,   0x2,    0x2,    0x155,  0x47,   0x3,    0x2,    0x2,    0x2,    0x156, 0x157, 0x9,   0x2,   0x2,   0x2,
        0x157, 0x49,   0x3,    0x2,    0x2,    0x2,    0x158,  0x15b,  0x7,    0x1b,  0x2,   0x2,   0x159, 0x15b, 0x7,
        0x1c,  0x2,    0x2,    0x15a,  0x158,  0x3,    0x2,    0x2,    0x2,    0x15a, 0x159, 0x3,   0x2,   0x2,   0x2,
        0x15b, 0x4b,   0x3,    0x2,    0x2,    0x2,    0x15c,  0x15f,  0x7,    0x33,  0x2,   0x2,   0x15d, 0x15e, 0x7,
        0xc,   0x2,    0x2,    0x15e,  0x160,  0x7,    0x1d,   0x2,    0x2,    0x15f, 0x15d, 0x3,   0x2,   0x2,   0x2,
        0x15f, 0x160,  0x3,    0x2,    0x2,    0x2,    0x160,  0x4d,   0x3,    0x2,   0x2,   0x2,   0x161, 0x164, 0x7,
        0x28,  0x2,    0x2,    0x162,  0x163,  0x7,    0xc,    0x2,    0x2,    0x163, 0x165, 0x7,   0x1e,  0x2,   0x2,
        0x164, 0x162,  0x3,    0x2,    0x2,    0x2,    0x164,  0x165,  0x3,    0x2,   0x2,   0x2,   0x165, 0x4f,  0x3,
        0x2,   0x2,    0x2,    0x166,  0x16e,  0x5,    0x52,   0x2a,   0x2,    0x167, 0x16e, 0x5,   0x54,  0x2b,  0x2,
        0x168, 0x16e,  0x5,    0x56,   0x2c,   0x2,    0x169,  0x16a,  0x7,    0x1f,  0x2,   0x2,   0x16a, 0x16e, 0x5,
        0x50,  0x29,   0x2,    0x16b,  0x16c,  0x7,    0x20,   0x2,    0x2,    0x16c, 0x16e, 0x5,   0x50,  0x29,  0x2,
        0x16d, 0x166,  0x3,    0x2,    0x2,    0x2,    0x16d,  0x167,  0x3,    0x2,   0x2,   0x2,   0x16d, 0x168, 0x3,
        0x2,   0x2,    0x2,    0x16d,  0x169,  0x3,    0x2,    0x2,    0x2,    0x16d, 0x16b, 0x3,   0x2,   0x2,   0x2,
        0x16e, 0x51,   0x3,    0x2,    0x2,    0x2,    0x16f,  0x170,  0x7,    0x27,  0x2,   0x2,   0x170, 0x53,  0x3,
        0x2,   0x2,    0x2,    0x171,  0x172,  0x7,    0x14,   0x2,    0x2,    0x172, 0x173, 0x5,   0x50,  0x29,  0x2,
        0x173, 0x174,  0x7,    0x37,   0x2,    0x2,    0x174,  0x175,  0x7,    0x33,  0x2,   0x2,   0x175, 0x176, 0x7,
        0x15,  0x2,    0x2,    0x176,  0x55,   0x3,    0x2,    0x2,    0x2,    0x177, 0x17b, 0x5,   0x58,  0x2d,  0x2,
        0x178, 0x17b,  0x5,    0x5a,   0x2e,   0x2,    0x179,  0x17b,  0x5,    0x5c,  0x2f,  0x2,   0x17a, 0x177, 0x3,
        0x2,   0x2,    0x2,    0x17a,  0x178,  0x3,    0x2,    0x2,    0x2,    0x17a, 0x179, 0x3,   0x2,   0x2,   0x2,
        0x17b, 0x57,   0x3,    0x2,    0x2,    0x2,    0x17c,  0x17d,  0x9,    0x3,   0x2,   0x2,   0x17d, 0x59,  0x3,
        0x2,   0x2,    0x2,    0x17e,  0x17f,  0x9,    0x4,    0x2,    0x2,    0x17f, 0x5b,  0x3,   0x2,   0x2,   0x2,
        0x180, 0x181,  0x7,    0x26,   0x2,    0x2,    0x181,  0x5d,   0x3,    0x2,   0x2,   0x2,   0x21,  0x60,  0x62,
        0x69,  0x70,   0x7e,   0x8b,   0x92,   0x95,   0x9c,   0xa4,   0xae,   0xc3,  0xcd,  0xd1,  0xd8,  0xea,  0xf3,
        0x102, 0x105,  0x10e,  0x115,  0x124,  0x135,  0x138,  0x141,  0x154,  0x15a, 0x15f, 0x164, 0x16d, 0x17a,
    };

    atn::ATNDeserializer deserializer;
    _atn = deserializer.deserialize(_serializedATN);

    size_t count = _atn.getNumberOfDecisions();
    _decisionToDFA.reserve(count);
    for (size_t i = 0; i < count; i++) { _decisionToDFA.emplace_back(_atn.getDecisionState(i), i); }
}

anceParser::Initializer anceParser::_init;
