
// Generated from ./src/grammar/ance.g4 by ANTLR 4.9.3

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

std::vector<anceParser::TypeDefinitionContext*> anceParser::FileContext::typeDefinition()
{
    return getRuleContexts<anceParser::TypeDefinitionContext>();
}

anceParser::TypeDefinitionContext* anceParser::FileContext::typeDefinition(size_t i)
{
    return getRuleContext<anceParser::TypeDefinitionContext>(i);
}

size_t anceParser::FileContext::getRuleIndex() const
{
    return anceParser::RuleFile;
}

antlrcpp::Any anceParser::FileContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitFile(this);
    else return visitor->visitChildren(this);
}

anceParser::FileContext* anceParser::file()
{
    FileContext* _localctx = _tracker.createInstance<FileContext>(_ctx, getState());
    enterRule(_localctx, 0, anceParser::RuleFile);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(125);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~0x3fULL) == 0)
                && ((1ULL << _la)
                    & ((1ULL << anceParser::T__5) | (1ULL << anceParser::T__7) | (1ULL << anceParser::T__10)
                       | (1ULL << anceParser::T__11)))
                       != 0))
        {
            setState(123);
            _errHandler->sync(this);
            switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx))
            {
                case 1:
                {
                    setState(120);
                    variableDeclaration();
                    break;
                }

                case 2:
                {
                    setState(121);
                    function();
                    break;
                }

                case 3:
                {
                    setState(122);
                    typeDefinition();
                    break;
                }

                default:
                    break;
            }
            setState(127);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(128);
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

tree::TerminalNode* anceParser::VariableDeclarationContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::TypeContext* anceParser::VariableDeclarationContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitVariableDeclaration(this);
    else return visitor->visitChildren(this);
}

anceParser::VariableDeclarationContext* anceParser::variableDeclaration()
{
    VariableDeclarationContext* _localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
    enterRule(_localctx, 2, anceParser::RuleVariableDeclaration);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(130);
        accessModifier();
        setState(132);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::CONST)
        {
            setState(131);
            match(anceParser::CONST);
        }
        setState(134);
        match(anceParser::IDENTIFIER);
        setState(135);
        match(anceParser::T__0);
        setState(136);
        type();
        setState(140);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0)
             && ((1ULL << _la)
                 & ((1ULL << anceParser::T__16) | (1ULL << anceParser::T__17) | (1ULL << anceParser::T__18)))
                    != 0))
        {
            setState(137);
            assigner();
            setState(138);
            literalExpression();
        }
        setState(142);
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

anceParser::TypeContext* anceParser::ExternFunctionDeclarationContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::ExternFunctionDeclarationContext::ExternFunctionDeclarationContext(FunctionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::ExternFunctionDeclarationContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitExternFunctionDeclaration(this);
    else return visitor->visitChildren(this);
}
//----------------- FunctionDefinitionContext ------------------------------------------------------------------

anceParser::AccessModifierContext* anceParser::FunctionDefinitionContext::accessModifier()
{
    return getRuleContext<anceParser::AccessModifierContext>(0);
}

tree::TerminalNode* anceParser::FunctionDefinitionContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::ParametersContext* anceParser::FunctionDefinitionContext::parameters()
{
    return getRuleContext<anceParser::ParametersContext>(0);
}

anceParser::TypeContext* anceParser::FunctionDefinitionContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

std::vector<anceParser::CodeContext*> anceParser::FunctionDefinitionContext::code()
{
    return getRuleContexts<anceParser::CodeContext>();
}

anceParser::CodeContext* anceParser::FunctionDefinitionContext::code(size_t i)
{
    return getRuleContext<anceParser::CodeContext>(i);
}

anceParser::FunctionDefinitionContext::FunctionDefinitionContext(FunctionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitFunctionDefinition(this);
    else return visitor->visitChildren(this);
}
anceParser::FunctionContext* anceParser::function()
{
    FunctionContext* _localctx = _tracker.createInstance<FunctionContext>(_ctx, getState());
    enterRule(_localctx, 4, anceParser::RuleFunction);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(173);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__10:
            case anceParser::T__11:
            {
                _localctx = _tracker.createInstance<anceParser::FunctionDefinitionContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(144);
                accessModifier();
                setState(145);
                match(anceParser::IDENTIFIER);
                setState(146);
                match(anceParser::T__1);
                setState(147);
                parameters();
                setState(148);
                match(anceParser::T__2);
                setState(151);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == anceParser::T__0)
                {
                    setState(149);
                    match(anceParser::T__0);
                    setState(150);
                    type();
                }
                setState(153);
                match(anceParser::T__3);
                setState(157);
                _errHandler->sync(this);
                _la = _input->LA(1);
                while ((((_la & ~0x3fULL) == 0)
                        && ((1ULL << _la)
                            & ((1ULL << anceParser::T__1) | (1ULL << anceParser::T__3) | (1ULL << anceParser::T__12)
                               | (1ULL << anceParser::T__13) | (1ULL << anceParser::T__15) | (1ULL << anceParser::T__19)
                               | (1ULL << anceParser::T__20) | (1ULL << anceParser::T__21) | (1ULL << anceParser::T__22)
                               | (1ULL << anceParser::T__25) | (1ULL << anceParser::T__27) | (1ULL << anceParser::T__45)
                               | (1ULL << anceParser::T__48) | (1ULL << anceParser::T__49) | (1ULL << anceParser::T__50)
                               | (1ULL << anceParser::T__51)))
                               != 0)
                       || ((((_la - 64) & ~0x3fULL) == 0)
                           && ((1ULL << (_la - 64))
                               & ((1ULL << (anceParser::SIGNED_INTEGER - 64)) | (1ULL << (anceParser::HEX_INTEGER - 64))
                                  | (1ULL << (anceParser::BIN_INTEGER - 64)) | (1ULL << (anceParser::OCT_INTEGER - 64))
                                  | (1ULL << (anceParser::HALF - 64)) | (1ULL << (anceParser::SINGLE - 64))
                                  | (1ULL << (anceParser::DOUBLE - 64)) | (1ULL << (anceParser::QUAD - 64))
                                  | (1ULL << (anceParser::STRING - 64)) | (1ULL << (anceParser::BYTE - 64))
                                  | (1ULL << (anceParser::INTEGER - 64)) | (1ULL << (anceParser::IDENTIFIER - 64))))
                                  != 0))
                {
                    setState(154);
                    code();
                    setState(159);
                    _errHandler->sync(this);
                    _la = _input->LA(1);
                }
                setState(160);
                match(anceParser::T__4);
                break;
            }

            case anceParser::T__5:
            {
                _localctx = _tracker.createInstance<anceParser::ExternFunctionDeclarationContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(162);
                match(anceParser::T__5);
                setState(163);
                match(anceParser::IDENTIFIER);
                setState(164);
                match(anceParser::T__1);
                setState(165);
                parameters();
                setState(166);
                match(anceParser::T__2);
                setState(169);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == anceParser::T__0)
                {
                    setState(167);
                    match(anceParser::T__0);
                    setState(168);
                    type();
                }
                setState(171);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitParameters(this);
    else return visitor->visitChildren(this);
}

anceParser::ParametersContext* anceParser::parameters()
{
    ParametersContext* _localctx = _tracker.createInstance<ParametersContext>(_ctx, getState());
    enterRule(_localctx, 6, anceParser::RuleParameters);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(183);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::IDENTIFIER)
        {
            setState(175);
            parameter();
            setState(180);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == anceParser::T__6)
            {
                setState(176);
                match(anceParser::T__6);
                setState(177);
                parameter();
                setState(182);
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

tree::TerminalNode* anceParser::ParameterContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::TypeContext* anceParser::ParameterContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

size_t anceParser::ParameterContext::getRuleIndex() const
{
    return anceParser::RuleParameter;
}

antlrcpp::Any anceParser::ParameterContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitParameter(this);
    else return visitor->visitChildren(this);
}

anceParser::ParameterContext* anceParser::parameter()
{
    ParameterContext* _localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
    enterRule(_localctx, 8, anceParser::RuleParameter);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(185);
        match(anceParser::IDENTIFIER);
        setState(186);
        match(anceParser::T__0);
        setState(187);
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

//----------------- TypeDefinitionContext ------------------------------------------------------------------

anceParser::TypeDefinitionContext::TypeDefinitionContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::DefineAsContext* anceParser::TypeDefinitionContext::defineAs()
{
    return getRuleContext<anceParser::DefineAsContext>(0);
}

anceParser::DefineAliasContext* anceParser::TypeDefinitionContext::defineAlias()
{
    return getRuleContext<anceParser::DefineAliasContext>(0);
}

size_t anceParser::TypeDefinitionContext::getRuleIndex() const
{
    return anceParser::RuleTypeDefinition;
}

antlrcpp::Any anceParser::TypeDefinitionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitTypeDefinition(this);
    else return visitor->visitChildren(this);
}

anceParser::TypeDefinitionContext* anceParser::typeDefinition()
{
    TypeDefinitionContext* _localctx = _tracker.createInstance<TypeDefinitionContext>(_ctx, getState());
    enterRule(_localctx, 10, anceParser::RuleTypeDefinition);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(191);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx))
        {
            case 1:
            {
                enterOuterAlt(_localctx, 1);
                setState(189);
                defineAs();
                break;
            }

            case 2:
            {
                enterOuterAlt(_localctx, 2);
                setState(190);
                defineAlias();
                break;
            }

            default:
                break;
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

//----------------- DefineAsContext ------------------------------------------------------------------

anceParser::DefineAsContext::DefineAsContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::DefineAsContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::TypeContext* anceParser::DefineAsContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::DefineAsContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

size_t anceParser::DefineAsContext::getRuleIndex() const
{
    return anceParser::RuleDefineAs;
}

antlrcpp::Any anceParser::DefineAsContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitDefineAs(this);
    else return visitor->visitChildren(this);
}

anceParser::DefineAsContext* anceParser::defineAs()
{
    DefineAsContext* _localctx = _tracker.createInstance<DefineAsContext>(_ctx, getState());
    enterRule(_localctx, 12, anceParser::RuleDefineAs);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(193);
        match(anceParser::T__7);
        setState(194);
        match(anceParser::IDENTIFIER);
        setState(195);
        match(anceParser::T__8);
        setState(196);
        type();
        setState(197);
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

//----------------- DefineAliasContext ------------------------------------------------------------------

anceParser::DefineAliasContext::DefineAliasContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::DefineAliasContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::TypeContext* anceParser::DefineAliasContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::DefineAliasContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

size_t anceParser::DefineAliasContext::getRuleIndex() const
{
    return anceParser::RuleDefineAlias;
}

antlrcpp::Any anceParser::DefineAliasContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitDefineAlias(this);
    else return visitor->visitChildren(this);
}

anceParser::DefineAliasContext* anceParser::defineAlias()
{
    DefineAliasContext* _localctx = _tracker.createInstance<DefineAliasContext>(_ctx, getState());
    enterRule(_localctx, 14, anceParser::RuleDefineAlias);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(199);
        match(anceParser::T__7);
        setState(200);
        match(anceParser::IDENTIFIER);
        setState(201);
        match(anceParser::T__9);
        setState(202);
        type();
        setState(203);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitPrivate(this);
    else return visitor->visitChildren(this);
}
//----------------- PublicContext ------------------------------------------------------------------

anceParser::PublicContext::PublicContext(AccessModifierContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::PublicContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitPublic(this);
    else return visitor->visitChildren(this);
}
anceParser::AccessModifierContext* anceParser::accessModifier()
{
    AccessModifierContext* _localctx = _tracker.createInstance<AccessModifierContext>(_ctx, getState());
    enterRule(_localctx, 16, anceParser::RuleAccessModifier);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(207);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__10:
            {
                _localctx = _tracker.createInstance<anceParser::PublicContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(205);
                match(anceParser::T__10);
                break;
            }

            case anceParser::T__11:
            {
                _localctx = _tracker.createInstance<anceParser::PrivateContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(206);
                match(anceParser::T__11);
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

//----------------- CodeContext ------------------------------------------------------------------

anceParser::CodeContext::CodeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::StatementContext* anceParser::CodeContext::statement()
{
    return getRuleContext<anceParser::StatementContext>(0);
}

anceParser::BlockContext* anceParser::CodeContext::block()
{
    return getRuleContext<anceParser::BlockContext>(0);
}

size_t anceParser::CodeContext::getRuleIndex() const
{
    return anceParser::RuleCode;
}

antlrcpp::Any anceParser::CodeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitCode(this);
    else return visitor->visitChildren(this);
}

anceParser::CodeContext* anceParser::code()
{
    CodeContext* _localctx = _tracker.createInstance<CodeContext>(_ctx, getState());
    enterRule(_localctx, 18, anceParser::RuleCode);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(211);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__1:
            case anceParser::T__12:
            case anceParser::T__13:
            case anceParser::T__15:
            case anceParser::T__19:
            case anceParser::T__20:
            case anceParser::T__21:
            case anceParser::T__22:
            case anceParser::T__25:
            case anceParser::T__27:
            case anceParser::T__45:
            case anceParser::T__48:
            case anceParser::T__49:
            case anceParser::T__50:
            case anceParser::T__51:
            case anceParser::SIGNED_INTEGER:
            case anceParser::HEX_INTEGER:
            case anceParser::BIN_INTEGER:
            case anceParser::OCT_INTEGER:
            case anceParser::HALF:
            case anceParser::SINGLE:
            case anceParser::DOUBLE:
            case anceParser::QUAD:
            case anceParser::STRING:
            case anceParser::BYTE:
            case anceParser::INTEGER:
            case anceParser::IDENTIFIER:
            {
                enterOuterAlt(_localctx, 1);
                setState(209);
                statement();
                break;
            }

            case anceParser::T__3:
            {
                enterOuterAlt(_localctx, 2);
                setState(210);
                block();
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

//----------------- BlockContext ------------------------------------------------------------------

anceParser::BlockContext::BlockContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

std::vector<anceParser::CodeContext*> anceParser::BlockContext::code()
{
    return getRuleContexts<anceParser::CodeContext>();
}

anceParser::CodeContext* anceParser::BlockContext::code(size_t i)
{
    return getRuleContext<anceParser::CodeContext>(i);
}

size_t anceParser::BlockContext::getRuleIndex() const
{
    return anceParser::RuleBlock;
}

antlrcpp::Any anceParser::BlockContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitBlock(this);
    else return visitor->visitChildren(this);
}

anceParser::BlockContext* anceParser::block()
{
    BlockContext* _localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
    enterRule(_localctx, 20, anceParser::RuleBlock);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(213);
        match(anceParser::T__3);
        setState(217);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~0x3fULL) == 0)
                && ((1ULL << _la)
                    & ((1ULL << anceParser::T__1) | (1ULL << anceParser::T__3) | (1ULL << anceParser::T__12)
                       | (1ULL << anceParser::T__13) | (1ULL << anceParser::T__15) | (1ULL << anceParser::T__19)
                       | (1ULL << anceParser::T__20) | (1ULL << anceParser::T__21) | (1ULL << anceParser::T__22)
                       | (1ULL << anceParser::T__25) | (1ULL << anceParser::T__27) | (1ULL << anceParser::T__45)
                       | (1ULL << anceParser::T__48) | (1ULL << anceParser::T__49) | (1ULL << anceParser::T__50)
                       | (1ULL << anceParser::T__51)))
                       != 0)
               || ((((_la - 64) & ~0x3fULL) == 0)
                   && ((1ULL << (_la - 64))
                       & ((1ULL << (anceParser::SIGNED_INTEGER - 64)) | (1ULL << (anceParser::HEX_INTEGER - 64))
                          | (1ULL << (anceParser::BIN_INTEGER - 64)) | (1ULL << (anceParser::OCT_INTEGER - 64))
                          | (1ULL << (anceParser::HALF - 64)) | (1ULL << (anceParser::SINGLE - 64))
                          | (1ULL << (anceParser::DOUBLE - 64)) | (1ULL << (anceParser::QUAD - 64))
                          | (1ULL << (anceParser::STRING - 64)) | (1ULL << (anceParser::BYTE - 64))
                          | (1ULL << (anceParser::INTEGER - 64)) | (1ULL << (anceParser::IDENTIFIER - 64))))
                          != 0))
        {
            setState(214);
            code();
            setState(219);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(220);
        match(anceParser::T__4);
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

anceParser::DropStatementContext* anceParser::StatementContext::dropStatement()
{
    return getRuleContext<anceParser::DropStatementContext>(0);
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

anceParser::AssertStatementContext* anceParser::StatementContext::assertStatement()
{
    return getRuleContext<anceParser::AssertStatementContext>(0);
}

anceParser::IfStatementContext* anceParser::StatementContext::ifStatement()
{
    return getRuleContext<anceParser::IfStatementContext>(0);
}

anceParser::WhileStatementContext* anceParser::StatementContext::whileStatement()
{
    return getRuleContext<anceParser::WhileStatementContext>(0);
}

anceParser::MatchStatementContext* anceParser::StatementContext::matchStatement()
{
    return getRuleContext<anceParser::MatchStatementContext>(0);
}

size_t anceParser::StatementContext::getRuleIndex() const
{
    return anceParser::RuleStatement;
}

antlrcpp::Any anceParser::StatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitStatement(this);
    else return visitor->visitChildren(this);
}

anceParser::StatementContext* anceParser::statement()
{
    StatementContext* _localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
    enterRule(_localctx, 22, anceParser::RuleStatement);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(233);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx))
        {
            case 1:
            {
                enterOuterAlt(_localctx, 1);
                setState(222);
                expressionStatement();
                break;
            }

            case 2:
            {
                enterOuterAlt(_localctx, 2);
                setState(223);
                localVariableDefinition();
                break;
            }

            case 3:
            {
                enterOuterAlt(_localctx, 3);
                setState(224);
                localReferenceDefinition();
                break;
            }

            case 4:
            {
                enterOuterAlt(_localctx, 4);
                setState(225);
                dropStatement();
                break;
            }

            case 5:
            {
                enterOuterAlt(_localctx, 5);
                setState(226);
                assignment();
                break;
            }

            case 6:
            {
                enterOuterAlt(_localctx, 6);
                setState(227);
                deleteStatement();
                break;
            }

            case 7:
            {
                enterOuterAlt(_localctx, 7);
                setState(228);
                returnStatement();
                break;
            }

            case 8:
            {
                enterOuterAlt(_localctx, 8);
                setState(229);
                assertStatement();
                break;
            }

            case 9:
            {
                enterOuterAlt(_localctx, 9);
                setState(230);
                ifStatement();
                break;
            }

            case 10:
            {
                enterOuterAlt(_localctx, 10);
                setState(231);
                whileStatement();
                break;
            }

            case 11:
            {
                enterOuterAlt(_localctx, 11);
                setState(232);
                matchStatement();
                break;
            }

            default:
                break;
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitExpressionStatement(this);
    else return visitor->visitChildren(this);
}

anceParser::ExpressionStatementContext* anceParser::expressionStatement()
{
    ExpressionStatementContext* _localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
    enterRule(_localctx, 24, anceParser::RuleExpressionStatement);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(235);
        independentExpression();
        setState(236);
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

tree::TerminalNode* anceParser::LocalVariableDefinitionContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::TypeContext* anceParser::LocalVariableDefinitionContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
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
    else return visitor->visitChildren(this);
}

anceParser::LocalVariableDefinitionContext* anceParser::localVariableDefinition()
{
    LocalVariableDefinitionContext* _localctx =
        _tracker.createInstance<LocalVariableDefinitionContext>(_ctx, getState());
    enterRule(_localctx, 26, anceParser::RuleLocalVariableDefinition);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(238);
        match(anceParser::T__12);
        setState(239);
        match(anceParser::IDENTIFIER);
        setState(240);
        match(anceParser::T__0);
        setState(241);
        type();
        setState(245);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0)
             && ((1ULL << _la)
                 & ((1ULL << anceParser::T__16) | (1ULL << anceParser::T__17) | (1ULL << anceParser::T__18)))
                    != 0))
        {
            setState(242);
            assigner();
            setState(243);
            expression(0);
        }
        setState(247);
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
    else return visitor->visitChildren(this);
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
    else return visitor->visitChildren(this);
}
anceParser::LocalReferenceDefinitionContext* anceParser::localReferenceDefinition()
{
    LocalReferenceDefinitionContext* _localctx =
        _tracker.createInstance<LocalReferenceDefinitionContext>(_ctx, getState());
    enterRule(_localctx, 28, anceParser::RuleLocalReferenceDefinition);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(266);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx))
        {
            case 1:
            {
                _localctx = _tracker.createInstance<anceParser::LocalReferenceToValueDefinitionContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(249);
                match(anceParser::T__12);
                setState(250);
                match(anceParser::IDENTIFIER);
                setState(251);
                match(anceParser::T__0);
                setState(252);
                type();
                setState(253);
                match(anceParser::T__13);
                setState(254);
                expression(0);
                setState(255);
                match(anceParser::SEMICOLON);
                break;
            }

            case 2:
            {
                _localctx = _tracker.createInstance<anceParser::LocalReferenceToPointerDefinitionContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(257);
                match(anceParser::T__12);
                setState(258);
                match(anceParser::IDENTIFIER);
                setState(259);
                match(anceParser::T__0);
                setState(260);
                type();
                setState(261);
                match(anceParser::T__13);
                setState(262);
                match(anceParser::T__14);
                setState(263);
                expression(0);
                setState(264);
                match(anceParser::SEMICOLON);
                break;
            }

            default:
                break;
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

//----------------- DropStatementContext ------------------------------------------------------------------

anceParser::DropStatementContext::DropStatementContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::DropStatementContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::DropStatementContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

size_t anceParser::DropStatementContext::getRuleIndex() const
{
    return anceParser::RuleDropStatement;
}

antlrcpp::Any anceParser::DropStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitDropStatement(this);
    else return visitor->visitChildren(this);
}

anceParser::DropStatementContext* anceParser::dropStatement()
{
    DropStatementContext* _localctx = _tracker.createInstance<DropStatementContext>(_ctx, getState());
    enterRule(_localctx, 30, anceParser::RuleDropStatement);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(268);
        match(anceParser::T__15);
        setState(269);
        match(anceParser::IDENTIFIER);
        setState(270);
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

//----------------- AssignmentContext ------------------------------------------------------------------

anceParser::AssignmentContext::AssignmentContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::AssignerContext* anceParser::AssignmentContext::assigner()
{
    return getRuleContext<anceParser::AssignerContext>(0);
}

tree::TerminalNode* anceParser::AssignmentContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

std::vector<anceParser::ExpressionContext*> anceParser::AssignmentContext::expression()
{
    return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::AssignmentContext::expression(size_t i)
{
    return getRuleContext<anceParser::ExpressionContext>(i);
}

size_t anceParser::AssignmentContext::getRuleIndex() const
{
    return anceParser::RuleAssignment;
}

antlrcpp::Any anceParser::AssignmentContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitAssignment(this);
    else return visitor->visitChildren(this);
}

anceParser::AssignmentContext* anceParser::assignment()
{
    AssignmentContext* _localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
    enterRule(_localctx, 32, anceParser::RuleAssignment);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(272);
        antlrcpp::downCast<AssignmentContext*>(_localctx)->assignable = expression(0);
        setState(273);
        assigner();
        setState(274);
        antlrcpp::downCast<AssignmentContext*>(_localctx)->assigned = expression(0);
        setState(275);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitMoveAssignment(this);
    else return visitor->visitChildren(this);
}
//----------------- FinalCopyAssignmentContext ------------------------------------------------------------------

anceParser::FinalCopyAssignmentContext::FinalCopyAssignmentContext(AssignerContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::FinalCopyAssignmentContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitFinalCopyAssignment(this);
    else return visitor->visitChildren(this);
}
//----------------- CopyAssignmentContext ------------------------------------------------------------------

anceParser::CopyAssignmentContext::CopyAssignmentContext(AssignerContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::CopyAssignmentContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitCopyAssignment(this);
    else return visitor->visitChildren(this);
}
anceParser::AssignerContext* anceParser::assigner()
{
    AssignerContext* _localctx = _tracker.createInstance<AssignerContext>(_ctx, getState());
    enterRule(_localctx, 34, anceParser::RuleAssigner);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(280);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__16:
            {
                _localctx = _tracker.createInstance<anceParser::CopyAssignmentContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(277);
                match(anceParser::T__16);
                break;
            }

            case anceParser::T__17:
            {
                _localctx = _tracker.createInstance<anceParser::MoveAssignmentContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(278);
                match(anceParser::T__17);
                break;
            }

            case anceParser::T__18:
            {
                _localctx = _tracker.createInstance<anceParser::FinalCopyAssignmentContext>(_localctx);
                enterOuterAlt(_localctx, 3);
                setState(279);
                match(anceParser::T__18);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitDeleteStatement(this);
    else return visitor->visitChildren(this);
}

anceParser::DeleteStatementContext* anceParser::deleteStatement()
{
    DeleteStatementContext* _localctx = _tracker.createInstance<DeleteStatementContext>(_ctx, getState());
    enterRule(_localctx, 36, anceParser::RuleDeleteStatement);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(282);
        match(anceParser::T__19);
        setState(284);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::BUFFER)
        {
            setState(283);
            match(anceParser::BUFFER);
        }
        setState(286);
        expression(0);
        setState(287);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitReturnStatement(this);
    else return visitor->visitChildren(this);
}

anceParser::ReturnStatementContext* anceParser::returnStatement()
{
    ReturnStatementContext* _localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
    enterRule(_localctx, 38, anceParser::RuleReturnStatement);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(289);
        match(anceParser::T__20);
        setState(291);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0)
             && ((1ULL << _la)
                 & ((1ULL << anceParser::T__1) | (1ULL << anceParser::T__13) | (1ULL << anceParser::T__45)
                    | (1ULL << anceParser::T__48) | (1ULL << anceParser::T__49) | (1ULL << anceParser::T__50)
                    | (1ULL << anceParser::T__51)))
                    != 0)
            || ((((_la - 64) & ~0x3fULL) == 0)
                && ((1ULL << (_la - 64))
                    & ((1ULL << (anceParser::SIGNED_INTEGER - 64)) | (1ULL << (anceParser::HEX_INTEGER - 64))
                       | (1ULL << (anceParser::BIN_INTEGER - 64)) | (1ULL << (anceParser::OCT_INTEGER - 64))
                       | (1ULL << (anceParser::HALF - 64)) | (1ULL << (anceParser::SINGLE - 64))
                       | (1ULL << (anceParser::DOUBLE - 64)) | (1ULL << (anceParser::QUAD - 64))
                       | (1ULL << (anceParser::STRING - 64)) | (1ULL << (anceParser::BYTE - 64))
                       | (1ULL << (anceParser::INTEGER - 64)) | (1ULL << (anceParser::IDENTIFIER - 64))))
                       != 0))
        {
            setState(290);
            expression(0);
        }
        setState(293);
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

//----------------- AssertStatementContext ------------------------------------------------------------------

anceParser::AssertStatementContext::AssertStatementContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::ExpressionContext* anceParser::AssertStatementContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

tree::TerminalNode* anceParser::AssertStatementContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

size_t anceParser::AssertStatementContext::getRuleIndex() const
{
    return anceParser::RuleAssertStatement;
}

antlrcpp::Any anceParser::AssertStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitAssertStatement(this);
    else return visitor->visitChildren(this);
}

anceParser::AssertStatementContext* anceParser::assertStatement()
{
    AssertStatementContext* _localctx = _tracker.createInstance<AssertStatementContext>(_ctx, getState());
    enterRule(_localctx, 40, anceParser::RuleAssertStatement);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(295);
        match(anceParser::T__21);
        setState(296);
        expression(0);
        setState(297);
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

//----------------- IfStatementContext ------------------------------------------------------------------

anceParser::IfStatementContext::IfStatementContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::ExpressionContext* anceParser::IfStatementContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

std::vector<anceParser::CodeContext*> anceParser::IfStatementContext::code()
{
    return getRuleContexts<anceParser::CodeContext>();
}

anceParser::CodeContext* anceParser::IfStatementContext::code(size_t i)
{
    return getRuleContext<anceParser::CodeContext>(i);
}

size_t anceParser::IfStatementContext::getRuleIndex() const
{
    return anceParser::RuleIfStatement;
}

antlrcpp::Any anceParser::IfStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitIfStatement(this);
    else return visitor->visitChildren(this);
}

anceParser::IfStatementContext* anceParser::ifStatement()
{
    IfStatementContext* _localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
    enterRule(_localctx, 42, anceParser::RuleIfStatement);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(299);
        match(anceParser::T__22);
        setState(300);
        expression(0);
        setState(301);
        match(anceParser::T__23);
        setState(302);
        antlrcpp::downCast<IfStatementContext*>(_localctx)->ifBlock = code();
        setState(305);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx))
        {
            case 1:
            {
                setState(303);
                match(anceParser::T__24);
                setState(304);
                antlrcpp::downCast<IfStatementContext*>(_localctx)->elseBlock = code();
                break;
            }

            default:
                break;
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

//----------------- WhileStatementContext ------------------------------------------------------------------

anceParser::WhileStatementContext::WhileStatementContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::ExpressionContext* anceParser::WhileStatementContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::CodeContext* anceParser::WhileStatementContext::code()
{
    return getRuleContext<anceParser::CodeContext>(0);
}

size_t anceParser::WhileStatementContext::getRuleIndex() const
{
    return anceParser::RuleWhileStatement;
}

antlrcpp::Any anceParser::WhileStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitWhileStatement(this);
    else return visitor->visitChildren(this);
}

anceParser::WhileStatementContext* anceParser::whileStatement()
{
    WhileStatementContext* _localctx = _tracker.createInstance<WhileStatementContext>(_ctx, getState());
    enterRule(_localctx, 44, anceParser::RuleWhileStatement);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(307);
        match(anceParser::T__25);
        setState(308);
        expression(0);
        setState(309);
        match(anceParser::T__26);
        setState(310);
        code();
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- MatchStatementContext ------------------------------------------------------------------

anceParser::MatchStatementContext::MatchStatementContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::ExpressionContext* anceParser::MatchStatementContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

std::vector<anceParser::MatchCaseContext*> anceParser::MatchStatementContext::matchCase()
{
    return getRuleContexts<anceParser::MatchCaseContext>();
}

anceParser::MatchCaseContext* anceParser::MatchStatementContext::matchCase(size_t i)
{
    return getRuleContext<anceParser::MatchCaseContext>(i);
}

size_t anceParser::MatchStatementContext::getRuleIndex() const
{
    return anceParser::RuleMatchStatement;
}

antlrcpp::Any anceParser::MatchStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitMatchStatement(this);
    else return visitor->visitChildren(this);
}

anceParser::MatchStatementContext* anceParser::matchStatement()
{
    MatchStatementContext* _localctx = _tracker.createInstance<MatchStatementContext>(_ctx, getState());
    enterRule(_localctx, 46, anceParser::RuleMatchStatement);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(312);
        match(anceParser::T__27);
        setState(313);
        expression(0);
        setState(314);
        match(anceParser::T__28);
        setState(315);
        match(anceParser::T__3);
        setState(319);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (((((_la - 32) & ~0x3fULL) == 0)
                && ((1ULL << (_la - 32))
                    & ((1ULL << (anceParser::T__31 - 32)) | (1ULL << (anceParser::T__50 - 32))
                       | (1ULL << (anceParser::T__51 - 32)) | (1ULL << (anceParser::SIGNED_INTEGER - 32))
                       | (1ULL << (anceParser::HEX_INTEGER - 32)) | (1ULL << (anceParser::BIN_INTEGER - 32))
                       | (1ULL << (anceParser::OCT_INTEGER - 32)) | (1ULL << (anceParser::HALF - 32))
                       | (1ULL << (anceParser::SINGLE - 32)) | (1ULL << (anceParser::DOUBLE - 32))
                       | (1ULL << (anceParser::QUAD - 32)) | (1ULL << (anceParser::STRING - 32))
                       | (1ULL << (anceParser::BYTE - 32)) | (1ULL << (anceParser::INTEGER - 32))
                       | (1ULL << (anceParser::IDENTIFIER - 32))))
                       != 0))
        {
            setState(316);
            matchCase();
            setState(321);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(322);
        match(anceParser::T__4);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- MatchCaseContext ------------------------------------------------------------------

anceParser::MatchCaseContext::MatchCaseContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::MatchCaseContext::getRuleIndex() const
{
    return anceParser::RuleMatchCase;
}

void anceParser::MatchCaseContext::copyFrom(MatchCaseContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- LiteralCaseContext ------------------------------------------------------------------

std::vector<anceParser::LiteralExpressionContext*> anceParser::LiteralCaseContext::literalExpression()
{
    return getRuleContexts<anceParser::LiteralExpressionContext>();
}

anceParser::LiteralExpressionContext* anceParser::LiteralCaseContext::literalExpression(size_t i)
{
    return getRuleContext<anceParser::LiteralExpressionContext>(i);
}

anceParser::CodeContext* anceParser::LiteralCaseContext::code()
{
    return getRuleContext<anceParser::CodeContext>(0);
}

anceParser::LiteralCaseContext::LiteralCaseContext(MatchCaseContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::LiteralCaseContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitLiteralCase(this);
    else return visitor->visitChildren(this);
}
//----------------- DefaultCaseContext ------------------------------------------------------------------

anceParser::CodeContext* anceParser::DefaultCaseContext::code()
{
    return getRuleContext<anceParser::CodeContext>(0);
}

anceParser::DefaultCaseContext::DefaultCaseContext(MatchCaseContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::DefaultCaseContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitDefaultCase(this);
    else return visitor->visitChildren(this);
}
anceParser::MatchCaseContext* anceParser::matchCase()
{
    MatchCaseContext* _localctx = _tracker.createInstance<MatchCaseContext>(_ctx, getState());
    enterRule(_localctx, 48, anceParser::RuleMatchCase);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(338);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__50:
            case anceParser::T__51:
            case anceParser::SIGNED_INTEGER:
            case anceParser::HEX_INTEGER:
            case anceParser::BIN_INTEGER:
            case anceParser::OCT_INTEGER:
            case anceParser::HALF:
            case anceParser::SINGLE:
            case anceParser::DOUBLE:
            case anceParser::QUAD:
            case anceParser::STRING:
            case anceParser::BYTE:
            case anceParser::INTEGER:
            case anceParser::IDENTIFIER:
            {
                _localctx = _tracker.createInstance<anceParser::LiteralCaseContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(324);
                literalExpression();
                setState(329);
                _errHandler->sync(this);
                _la = _input->LA(1);
                while (_la == anceParser::T__29)
                {
                    setState(325);
                    match(anceParser::T__29);
                    setState(326);
                    literalExpression();
                    setState(331);
                    _errHandler->sync(this);
                    _la = _input->LA(1);
                }
                setState(332);
                match(anceParser::T__30);
                setState(333);
                code();
                break;
            }

            case anceParser::T__31:
            {
                _localctx = _tracker.createInstance<anceParser::DefaultCaseContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(335);
                match(anceParser::T__31);
                setState(336);
                match(anceParser::T__30);
                setState(337);
                code();
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitRef(this);
    else return visitor->visitChildren(this);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitIndependent(this);
    else return visitor->visitChildren(this);
}
//----------------- ParenthesisContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::ParenthesisContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::ParenthesisContext::ParenthesisContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::ParenthesisContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitParenthesis(this);
    else return visitor->visitChildren(this);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitVariable(this);
    else return visitor->visitChildren(this);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitAlloc(this);
    else return visitor->visitChildren(this);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitAdressOf(this);
    else return visitor->visitChildren(this);
}
//----------------- BinaryOperationContext ------------------------------------------------------------------

anceParser::BinaryOperatorMultiplicativeContext* anceParser::BinaryOperationContext::binaryOperatorMultiplicative()
{
    return getRuleContext<anceParser::BinaryOperatorMultiplicativeContext>(0);
}

std::vector<anceParser::ExpressionContext*> anceParser::BinaryOperationContext::expression()
{
    return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::BinaryOperationContext::expression(size_t i)
{
    return getRuleContext<anceParser::ExpressionContext>(i);
}

anceParser::BinaryOperatorAdditiveContext* anceParser::BinaryOperationContext::binaryOperatorAdditive()
{
    return getRuleContext<anceParser::BinaryOperatorAdditiveContext>(0);
}

anceParser::BinaryOperatorRelationalContext* anceParser::BinaryOperationContext::binaryOperatorRelational()
{
    return getRuleContext<anceParser::BinaryOperatorRelationalContext>(0);
}

anceParser::BinaryOperatorEqualityContext* anceParser::BinaryOperationContext::binaryOperatorEquality()
{
    return getRuleContext<anceParser::BinaryOperatorEqualityContext>(0);
}

anceParser::BinaryOperationContext::BinaryOperationContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::BinaryOperationContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitBinaryOperation(this);
    else return visitor->visitChildren(this);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitLiteral(this);
    else return visitor->visitChildren(this);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitSizeOf(this);
    else return visitor->visitChildren(this);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitSubscript(this);
    else return visitor->visitChildren(this);
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
    size_t startState = 50;
    enterRecursionRule(_localctx, 50, anceParser::RuleExpression, precedence);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        unrollRecursionContexts(parentContext);
    });
    try
    {
        size_t alt;
        enterOuterAlt(_localctx, 1);
        setState(353);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx))
        {
            case 1:
            {
                _localctx       = _tracker.createInstance<VariableContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;

                setState(341);
                variableAccess();
                break;
            }

            case 2:
            {
                _localctx       = _tracker.createInstance<AllocContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(342);
                allocation();
                break;
            }

            case 3:
            {
                _localctx       = _tracker.createInstance<AdressOfContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(343);
                addressof();
                break;
            }

            case 4:
            {
                _localctx       = _tracker.createInstance<RefContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(344);
                bindRef();
                break;
            }

            case 5:
            {
                _localctx       = _tracker.createInstance<SizeOfContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(345);
                sizeofType();
                break;
            }

            case 6:
            {
                _localctx       = _tracker.createInstance<SizeOfContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(346);
                sizeofExpression();
                break;
            }

            case 7:
            {
                _localctx       = _tracker.createInstance<LiteralContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(347);
                literalExpression();
                break;
            }

            case 8:
            {
                _localctx       = _tracker.createInstance<IndependentContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(348);
                independentExpression();
                break;
            }

            case 9:
            {
                _localctx       = _tracker.createInstance<ParenthesisContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(349);
                match(anceParser::T__1);
                setState(350);
                expression(0);
                setState(351);
                match(anceParser::T__2);
                break;
            }

            default:
                break;
        }
        _ctx->stop = _input->LT(-1);
        setState(378);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER)
        {
            if (alt == 1)
            {
                if (!_parseListeners.empty()) triggerExitRuleEvent();
                previousContext = _localctx;
                setState(376);
                _errHandler->sync(this);
                switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx))
                {
                    case 1:
                    {
                        auto newContext = _tracker.createInstance<BinaryOperationContext>(
                            _tracker.createInstance<ExpressionContext>(parentContext, parentState));
                        _localctx        = newContext;
                        newContext->left = previousContext;
                        pushNewRecursionContext(newContext, startState, RuleExpression);
                        setState(355);

                        if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
                        setState(356);
                        binaryOperatorMultiplicative();
                        setState(357);
                        antlrcpp::downCast<BinaryOperationContext*>(_localctx)->right = expression(5);
                        break;
                    }

                    case 2:
                    {
                        auto newContext = _tracker.createInstance<BinaryOperationContext>(
                            _tracker.createInstance<ExpressionContext>(parentContext, parentState));
                        _localctx        = newContext;
                        newContext->left = previousContext;
                        pushNewRecursionContext(newContext, startState, RuleExpression);
                        setState(359);

                        if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
                        setState(360);
                        binaryOperatorAdditive();
                        setState(361);
                        antlrcpp::downCast<BinaryOperationContext*>(_localctx)->right = expression(4);
                        break;
                    }

                    case 3:
                    {
                        auto newContext = _tracker.createInstance<BinaryOperationContext>(
                            _tracker.createInstance<ExpressionContext>(parentContext, parentState));
                        _localctx        = newContext;
                        newContext->left = previousContext;
                        pushNewRecursionContext(newContext, startState, RuleExpression);
                        setState(363);

                        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
                        setState(364);
                        binaryOperatorRelational();
                        setState(365);
                        antlrcpp::downCast<BinaryOperationContext*>(_localctx)->right = expression(3);
                        break;
                    }

                    case 4:
                    {
                        auto newContext = _tracker.createInstance<BinaryOperationContext>(
                            _tracker.createInstance<ExpressionContext>(parentContext, parentState));
                        _localctx        = newContext;
                        newContext->left = previousContext;
                        pushNewRecursionContext(newContext, startState, RuleExpression);
                        setState(367);

                        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
                        setState(368);
                        binaryOperatorEquality();
                        setState(369);
                        antlrcpp::downCast<BinaryOperationContext*>(_localctx)->right = expression(2);
                        break;
                    }

                    case 5:
                    {
                        auto newContext = _tracker.createInstance<SubscriptContext>(
                            _tracker.createInstance<ExpressionContext>(parentContext, parentState));
                        _localctx           = newContext;
                        newContext->indexed = previousContext;
                        pushNewRecursionContext(newContext, startState, RuleExpression);
                        setState(371);

                        if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
                        setState(372);
                        match(anceParser::T__32);
                        setState(373);
                        antlrcpp::downCast<SubscriptContext*>(_localctx)->index = expression(0);
                        setState(374);
                        match(anceParser::T__33);
                        break;
                    }

                    default:
                        break;
                }
            }
            setState(380);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
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

//----------------- BinaryOperatorMultiplicativeContext ------------------------------------------------------------------

anceParser::BinaryOperatorMultiplicativeContext::BinaryOperatorMultiplicativeContext(ParserRuleContext* parent,
                                                                                     size_t             invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::BinaryOperatorMultiplicativeContext::getRuleIndex() const
{
    return anceParser::RuleBinaryOperatorMultiplicative;
}

void anceParser::BinaryOperatorMultiplicativeContext::copyFrom(BinaryOperatorMultiplicativeContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- MultiplicationContext ------------------------------------------------------------------

anceParser::MultiplicationContext::MultiplicationContext(BinaryOperatorMultiplicativeContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::MultiplicationContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitMultiplication(this);
    else return visitor->visitChildren(this);
}
//----------------- DivisionContext ------------------------------------------------------------------

anceParser::DivisionContext::DivisionContext(BinaryOperatorMultiplicativeContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::DivisionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitDivision(this);
    else return visitor->visitChildren(this);
}
//----------------- RemainderContext ------------------------------------------------------------------

anceParser::RemainderContext::RemainderContext(BinaryOperatorMultiplicativeContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::RemainderContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitRemainder(this);
    else return visitor->visitChildren(this);
}
anceParser::BinaryOperatorMultiplicativeContext* anceParser::binaryOperatorMultiplicative()
{
    BinaryOperatorMultiplicativeContext* _localctx =
        _tracker.createInstance<BinaryOperatorMultiplicativeContext>(_ctx, getState());
    enterRule(_localctx, 52, anceParser::RuleBinaryOperatorMultiplicative);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(384);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__34:
            {
                _localctx = _tracker.createInstance<anceParser::MultiplicationContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(381);
                match(anceParser::T__34);
                break;
            }

            case anceParser::T__35:
            {
                _localctx = _tracker.createInstance<anceParser::DivisionContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(382);
                match(anceParser::T__35);
                break;
            }

            case anceParser::T__36:
            {
                _localctx = _tracker.createInstance<anceParser::RemainderContext>(_localctx);
                enterOuterAlt(_localctx, 3);
                setState(383);
                match(anceParser::T__36);
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

//----------------- BinaryOperatorAdditiveContext ------------------------------------------------------------------

anceParser::BinaryOperatorAdditiveContext::BinaryOperatorAdditiveContext(ParserRuleContext* parent,
                                                                         size_t             invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::BinaryOperatorAdditiveContext::getRuleIndex() const
{
    return anceParser::RuleBinaryOperatorAdditive;
}

void anceParser::BinaryOperatorAdditiveContext::copyFrom(BinaryOperatorAdditiveContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- AdditionContext ------------------------------------------------------------------

anceParser::AdditionContext::AdditionContext(BinaryOperatorAdditiveContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::AdditionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitAddition(this);
    else return visitor->visitChildren(this);
}
//----------------- SubtractionContext ------------------------------------------------------------------

anceParser::SubtractionContext::SubtractionContext(BinaryOperatorAdditiveContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::SubtractionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitSubtraction(this);
    else return visitor->visitChildren(this);
}
anceParser::BinaryOperatorAdditiveContext* anceParser::binaryOperatorAdditive()
{
    BinaryOperatorAdditiveContext* _localctx = _tracker.createInstance<BinaryOperatorAdditiveContext>(_ctx, getState());
    enterRule(_localctx, 54, anceParser::RuleBinaryOperatorAdditive);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(388);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__37:
            {
                _localctx = _tracker.createInstance<anceParser::AdditionContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(386);
                match(anceParser::T__37);
                break;
            }

            case anceParser::T__38:
            {
                _localctx = _tracker.createInstance<anceParser::SubtractionContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(387);
                match(anceParser::T__38);
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

//----------------- BinaryOperatorRelationalContext ------------------------------------------------------------------

anceParser::BinaryOperatorRelationalContext::BinaryOperatorRelationalContext(ParserRuleContext* parent,
                                                                             size_t             invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::BinaryOperatorRelationalContext::getRuleIndex() const
{
    return anceParser::RuleBinaryOperatorRelational;
}

void anceParser::BinaryOperatorRelationalContext::copyFrom(BinaryOperatorRelationalContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- LessThanContext ------------------------------------------------------------------

anceParser::LessThanContext::LessThanContext(BinaryOperatorRelationalContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::LessThanContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitLessThan(this);
    else return visitor->visitChildren(this);
}
//----------------- LessThanOrEqualContext ------------------------------------------------------------------

anceParser::LessThanOrEqualContext::LessThanOrEqualContext(BinaryOperatorRelationalContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::LessThanOrEqualContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitLessThanOrEqual(this);
    else return visitor->visitChildren(this);
}
//----------------- GreaterThanContext ------------------------------------------------------------------

anceParser::GreaterThanContext::GreaterThanContext(BinaryOperatorRelationalContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::GreaterThanContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitGreaterThan(this);
    else return visitor->visitChildren(this);
}
//----------------- GreaterThanOrEqualContext ------------------------------------------------------------------

anceParser::GreaterThanOrEqualContext::GreaterThanOrEqualContext(BinaryOperatorRelationalContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::GreaterThanOrEqualContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitGreaterThanOrEqual(this);
    else return visitor->visitChildren(this);
}
anceParser::BinaryOperatorRelationalContext* anceParser::binaryOperatorRelational()
{
    BinaryOperatorRelationalContext* _localctx =
        _tracker.createInstance<BinaryOperatorRelationalContext>(_ctx, getState());
    enterRule(_localctx, 56, anceParser::RuleBinaryOperatorRelational);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(394);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__39:
            {
                _localctx = _tracker.createInstance<anceParser::LessThanContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(390);
                match(anceParser::T__39);
                break;
            }

            case anceParser::T__40:
            {
                _localctx = _tracker.createInstance<anceParser::LessThanOrEqualContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(391);
                match(anceParser::T__40);
                break;
            }

            case anceParser::T__41:
            {
                _localctx = _tracker.createInstance<anceParser::GreaterThanContext>(_localctx);
                enterOuterAlt(_localctx, 3);
                setState(392);
                match(anceParser::T__41);
                break;
            }

            case anceParser::T__42:
            {
                _localctx = _tracker.createInstance<anceParser::GreaterThanOrEqualContext>(_localctx);
                enterOuterAlt(_localctx, 4);
                setState(393);
                match(anceParser::T__42);
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

//----------------- BinaryOperatorEqualityContext ------------------------------------------------------------------

anceParser::BinaryOperatorEqualityContext::BinaryOperatorEqualityContext(ParserRuleContext* parent,
                                                                         size_t             invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::BinaryOperatorEqualityContext::getRuleIndex() const
{
    return anceParser::RuleBinaryOperatorEquality;
}

void anceParser::BinaryOperatorEqualityContext::copyFrom(BinaryOperatorEqualityContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- NotEqualContext ------------------------------------------------------------------

anceParser::NotEqualContext::NotEqualContext(BinaryOperatorEqualityContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::NotEqualContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitNotEqual(this);
    else return visitor->visitChildren(this);
}
//----------------- EqualContext ------------------------------------------------------------------

anceParser::EqualContext::EqualContext(BinaryOperatorEqualityContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::EqualContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitEqual(this);
    else return visitor->visitChildren(this);
}
anceParser::BinaryOperatorEqualityContext* anceParser::binaryOperatorEquality()
{
    BinaryOperatorEqualityContext* _localctx = _tracker.createInstance<BinaryOperatorEqualityContext>(_ctx, getState());
    enterRule(_localctx, 58, anceParser::RuleBinaryOperatorEquality);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(398);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__43:
            {
                _localctx = _tracker.createInstance<anceParser::EqualContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(396);
                match(anceParser::T__43);
                break;
            }

            case anceParser::T__44:
            {
                _localctx = _tracker.createInstance<anceParser::NotEqualContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(397);
                match(anceParser::T__44);
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
    else return visitor->visitChildren(this);
}

anceParser::IndependentExpressionContext* anceParser::independentExpression()
{
    IndependentExpressionContext* _localctx = _tracker.createInstance<IndependentExpressionContext>(_ctx, getState());
    enterRule(_localctx, 60, anceParser::RuleIndependentExpression);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(400);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitFunctionCall(this);
    else return visitor->visitChildren(this);
}

anceParser::FunctionCallContext* anceParser::functionCall()
{
    FunctionCallContext* _localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
    enterRule(_localctx, 62, anceParser::RuleFunctionCall);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(402);
        match(anceParser::IDENTIFIER);
        setState(403);
        match(anceParser::T__1);
        setState(404);
        arguments();
        setState(405);
        match(anceParser::T__2);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitArguments(this);
    else return visitor->visitChildren(this);
}

anceParser::ArgumentsContext* anceParser::arguments()
{
    ArgumentsContext* _localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
    enterRule(_localctx, 64, anceParser::RuleArguments);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(415);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0)
             && ((1ULL << _la)
                 & ((1ULL << anceParser::T__1) | (1ULL << anceParser::T__13) | (1ULL << anceParser::T__45)
                    | (1ULL << anceParser::T__48) | (1ULL << anceParser::T__49) | (1ULL << anceParser::T__50)
                    | (1ULL << anceParser::T__51)))
                    != 0)
            || ((((_la - 64) & ~0x3fULL) == 0)
                && ((1ULL << (_la - 64))
                    & ((1ULL << (anceParser::SIGNED_INTEGER - 64)) | (1ULL << (anceParser::HEX_INTEGER - 64))
                       | (1ULL << (anceParser::BIN_INTEGER - 64)) | (1ULL << (anceParser::OCT_INTEGER - 64))
                       | (1ULL << (anceParser::HALF - 64)) | (1ULL << (anceParser::SINGLE - 64))
                       | (1ULL << (anceParser::DOUBLE - 64)) | (1ULL << (anceParser::QUAD - 64))
                       | (1ULL << (anceParser::STRING - 64)) | (1ULL << (anceParser::BYTE - 64))
                       | (1ULL << (anceParser::INTEGER - 64)) | (1ULL << (anceParser::IDENTIFIER - 64))))
                       != 0))
        {
            setState(407);
            expression(0);
            setState(412);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == anceParser::T__6)
            {
                setState(408);
                match(anceParser::T__6);
                setState(409);
                expression(0);
                setState(414);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitVariableAccess(this);
    else return visitor->visitChildren(this);
}

anceParser::VariableAccessContext* anceParser::variableAccess()
{
    VariableAccessContext* _localctx = _tracker.createInstance<VariableAccessContext>(_ctx, getState());
    enterRule(_localctx, 66, anceParser::RuleVariableAccess);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(417);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitAllocation(this);
    else return visitor->visitChildren(this);
}

anceParser::AllocationContext* anceParser::allocation()
{
    AllocationContext* _localctx = _tracker.createInstance<AllocationContext>(_ctx, getState());
    enterRule(_localctx, 68, anceParser::RuleAllocation);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(419);
        match(anceParser::T__45);
        setState(424);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::T__32)
        {
            setState(420);
            match(anceParser::T__32);
            setState(421);
            expression(0);
            setState(422);
            match(anceParser::T__33);
        }
        setState(426);
        allocator();
        setState(427);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitDynamic(this);
    else return visitor->visitChildren(this);
}
//----------------- AutomaticContext ------------------------------------------------------------------

anceParser::AutomaticContext::AutomaticContext(AllocatorContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::AutomaticContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitAutomatic(this);
    else return visitor->visitChildren(this);
}
anceParser::AllocatorContext* anceParser::allocator()
{
    AllocatorContext* _localctx = _tracker.createInstance<AllocatorContext>(_ctx, getState());
    enterRule(_localctx, 70, anceParser::RuleAllocator);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(431);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__46:
            {
                _localctx = _tracker.createInstance<anceParser::DynamicContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(429);
                match(anceParser::T__46);
                break;
            }

            case anceParser::T__47:
            {
                _localctx = _tracker.createInstance<anceParser::AutomaticContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(430);
                match(anceParser::T__47);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitAddressof(this);
    else return visitor->visitChildren(this);
}

anceParser::AddressofContext* anceParser::addressof()
{
    AddressofContext* _localctx = _tracker.createInstance<AddressofContext>(_ctx, getState());
    enterRule(_localctx, 72, anceParser::RuleAddressof);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(433);
        match(anceParser::T__48);
        setState(434);
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
    else return visitor->visitChildren(this);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitBindReference(this);
    else return visitor->visitChildren(this);
}
anceParser::BindRefContext* anceParser::bindRef()
{
    BindRefContext* _localctx = _tracker.createInstance<BindRefContext>(_ctx, getState());
    enterRule(_localctx, 74, anceParser::RuleBindRef);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(441);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx))
        {
            case 1:
            {
                _localctx = _tracker.createInstance<anceParser::BindReferenceContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(436);
                match(anceParser::T__13);
                setState(437);
                expression(0);
                break;
            }

            case 2:
            {
                _localctx = _tracker.createInstance<anceParser::BindReferenceToAddressContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(438);
                match(anceParser::T__13);
                setState(439);
                match(anceParser::T__14);
                setState(440);
                expression(0);
                break;
            }

            default:
                break;
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitSizeofType(this);
    else return visitor->visitChildren(this);
}

anceParser::SizeofTypeContext* anceParser::sizeofType()
{
    SizeofTypeContext* _localctx = _tracker.createInstance<SizeofTypeContext>(_ctx, getState());
    enterRule(_localctx, 76, anceParser::RuleSizeofType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(443);
        match(anceParser::T__49);
        setState(444);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitSizeofExpression(this);
    else return visitor->visitChildren(this);
}

anceParser::SizeofExpressionContext* anceParser::sizeofExpression()
{
    SizeofExpressionContext* _localctx = _tracker.createInstance<SizeofExpressionContext>(_ctx, getState());
    enterRule(_localctx, 78, anceParser::RuleSizeofExpression);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(446);
        match(anceParser::T__49);
        setState(447);
        match(anceParser::T__1);
        setState(448);
        expression(0);
        setState(449);
        match(anceParser::T__2);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitLiteralExpression(this);
    else return visitor->visitChildren(this);
}

anceParser::LiteralExpressionContext* anceParser::literalExpression()
{
    LiteralExpressionContext* _localctx = _tracker.createInstance<LiteralExpressionContext>(_ctx, getState());
    enterRule(_localctx, 80, anceParser::RuleLiteralExpression);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(458);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx))
        {
            case 1:
            {
                enterOuterAlt(_localctx, 1);
                setState(451);
                stringLiteral();
                break;
            }

            case 2:
            {
                enterOuterAlt(_localctx, 2);
                setState(452);
                byteLiteral();
                break;
            }

            case 3:
            {
                enterOuterAlt(_localctx, 3);
                setState(453);
                integerLiteral();
                break;
            }

            case 4:
            {
                enterOuterAlt(_localctx, 4);
                setState(454);
                floatingPointLiteral();
                break;
            }

            case 5:
            {
                enterOuterAlt(_localctx, 5);
                setState(455);
                booleanLiteral();
                break;
            }

            case 6:
            {
                enterOuterAlt(_localctx, 6);
                setState(456);
                sizeLiteral();
                break;
            }

            case 7:
            {
                enterOuterAlt(_localctx, 7);
                setState(457);
                diffLiteral();
                break;
            }

            default:
                break;
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitStringLiteral(this);
    else return visitor->visitChildren(this);
}

anceParser::StringLiteralContext* anceParser::stringLiteral()
{
    StringLiteralContext* _localctx = _tracker.createInstance<StringLiteralContext>(_ctx, getState());
    enterRule(_localctx, 82, anceParser::RuleStringLiteral);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(461);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::IDENTIFIER)
        {
            setState(460);
            antlrcpp::downCast<StringLiteralContext*>(_localctx)->prefix = match(anceParser::IDENTIFIER);
        }
        setState(463);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitByteLiteral(this);
    else return visitor->visitChildren(this);
}

anceParser::ByteLiteralContext* anceParser::byteLiteral()
{
    ByteLiteralContext* _localctx = _tracker.createInstance<ByteLiteralContext>(_ctx, getState());
    enterRule(_localctx, 84, anceParser::RuleByteLiteral);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(465);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitIntegerLiteral(this);
    else return visitor->visitChildren(this);
}

anceParser::IntegerLiteralContext* anceParser::integerLiteral()
{
    IntegerLiteralContext* _localctx = _tracker.createInstance<IntegerLiteralContext>(_ctx, getState());
    enterRule(_localctx, 86, anceParser::RuleIntegerLiteral);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(470);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::INTEGER:
            {
                enterOuterAlt(_localctx, 1);
                setState(467);
                unsignedInteger();
                break;
            }

            case anceParser::SIGNED_INTEGER:
            {
                enterOuterAlt(_localctx, 2);
                setState(468);
                signedInteger();
                break;
            }

            case anceParser::HEX_INTEGER:
            case anceParser::BIN_INTEGER:
            case anceParser::OCT_INTEGER:
            {
                enterOuterAlt(_localctx, 3);
                setState(469);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitUnsignedInteger(this);
    else return visitor->visitChildren(this);
}

anceParser::UnsignedIntegerContext* anceParser::unsignedInteger()
{
    UnsignedIntegerContext* _localctx = _tracker.createInstance<UnsignedIntegerContext>(_ctx, getState());
    enterRule(_localctx, 88, anceParser::RuleUnsignedInteger);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(472);
        antlrcpp::downCast<UnsignedIntegerContext*>(_localctx)->value = match(anceParser::INTEGER);
        setState(473);
        match(anceParser::T__0);
        setState(474);
        antlrcpp::downCast<UnsignedIntegerContext*>(_localctx)->width = match(anceParser::INTEGER);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitSignedInteger(this);
    else return visitor->visitChildren(this);
}

anceParser::SignedIntegerContext* anceParser::signedInteger()
{
    SignedIntegerContext* _localctx = _tracker.createInstance<SignedIntegerContext>(_ctx, getState());
    enterRule(_localctx, 90, anceParser::RuleSignedInteger);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(476);
        antlrcpp::downCast<SignedIntegerContext*>(_localctx)->value = match(anceParser::SIGNED_INTEGER);
        setState(477);
        match(anceParser::T__0);
        setState(478);
        antlrcpp::downCast<SignedIntegerContext*>(_localctx)->width = match(anceParser::INTEGER);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitSpecialInteger(this);
    else return visitor->visitChildren(this);
}

anceParser::SpecialIntegerContext* anceParser::specialInteger()
{
    SpecialIntegerContext* _localctx = _tracker.createInstance<SpecialIntegerContext>(_ctx, getState());
    enterRule(_localctx, 92, anceParser::RuleSpecialInteger);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(489);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::HEX_INTEGER:
            {
                enterOuterAlt(_localctx, 1);
                setState(480);
                match(anceParser::HEX_INTEGER);
                setState(481);
                match(anceParser::T__0);
                setState(482);
                antlrcpp::downCast<SpecialIntegerContext*>(_localctx)->width = match(anceParser::INTEGER);
                break;
            }

            case anceParser::BIN_INTEGER:
            {
                enterOuterAlt(_localctx, 2);
                setState(483);
                match(anceParser::BIN_INTEGER);
                setState(484);
                match(anceParser::T__0);
                setState(485);
                antlrcpp::downCast<SpecialIntegerContext*>(_localctx)->width = match(anceParser::INTEGER);
                break;
            }

            case anceParser::OCT_INTEGER:
            {
                enterOuterAlt(_localctx, 3);
                setState(486);
                match(anceParser::OCT_INTEGER);
                setState(487);
                match(anceParser::T__0);
                setState(488);
                antlrcpp::downCast<SpecialIntegerContext*>(_localctx)->width = match(anceParser::INTEGER);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitFloatingPointLiteral(this);
    else return visitor->visitChildren(this);
}

anceParser::FloatingPointLiteralContext* anceParser::floatingPointLiteral()
{
    FloatingPointLiteralContext* _localctx = _tracker.createInstance<FloatingPointLiteralContext>(_ctx, getState());
    enterRule(_localctx, 94, anceParser::RuleFloatingPointLiteral);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(491);
        _la = _input->LA(1);
        if (!(((((_la - 68) & ~0x3fULL) == 0)
               && ((1ULL << (_la - 68))
                   & ((1ULL << (anceParser::HALF - 68)) | (1ULL << (anceParser::SINGLE - 68))
                      | (1ULL << (anceParser::DOUBLE - 68)) | (1ULL << (anceParser::QUAD - 68))))
                      != 0)))
        {
            _errHandler->recoverInline(this);
        }
        else {
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitTrue(this);
    else return visitor->visitChildren(this);
}
//----------------- FalseContext ------------------------------------------------------------------

anceParser::FalseContext::FalseContext(BooleanLiteralContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::FalseContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitFalse(this);
    else return visitor->visitChildren(this);
}
anceParser::BooleanLiteralContext* anceParser::booleanLiteral()
{
    BooleanLiteralContext* _localctx = _tracker.createInstance<BooleanLiteralContext>(_ctx, getState());
    enterRule(_localctx, 96, anceParser::RuleBooleanLiteral);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(495);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__50:
            {
                _localctx = _tracker.createInstance<anceParser::TrueContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(493);
                match(anceParser::T__50);
                break;
            }

            case anceParser::T__51:
            {
                _localctx = _tracker.createInstance<anceParser::FalseContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(494);
                match(anceParser::T__51);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitSizeLiteral(this);
    else return visitor->visitChildren(this);
}

anceParser::SizeLiteralContext* anceParser::sizeLiteral()
{
    SizeLiteralContext* _localctx = _tracker.createInstance<SizeLiteralContext>(_ctx, getState());
    enterRule(_localctx, 98, anceParser::RuleSizeLiteral);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(497);
        match(anceParser::INTEGER);
        setState(500);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx))
        {
            case 1:
            {
                setState(498);
                match(anceParser::T__0);
                setState(499);
                match(anceParser::T__52);
                break;
            }

            default:
                break;
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitDiffLiteral(this);
    else return visitor->visitChildren(this);
}

anceParser::DiffLiteralContext* anceParser::diffLiteral()
{
    DiffLiteralContext* _localctx = _tracker.createInstance<DiffLiteralContext>(_ctx, getState());
    enterRule(_localctx, 100, anceParser::RuleDiffLiteral);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(502);
        match(anceParser::SIGNED_INTEGER);
        setState(505);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx))
        {
            case 1:
            {
                setState(503);
                match(anceParser::T__0);
                setState(504);
                match(anceParser::T__53);
                break;
            }

            default:
                break;
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitInteger(this);
    else return visitor->visitChildren(this);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitArray(this);
    else return visitor->visitChildren(this);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitKeyword(this);
    else return visitor->visitChildren(this);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitReference(this);
    else return visitor->visitChildren(this);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitPointer(this);
    else return visitor->visitChildren(this);
}
//----------------- CustomContext ------------------------------------------------------------------

anceParser::CustomTypeContext* anceParser::CustomContext::customType()
{
    return getRuleContext<anceParser::CustomTypeContext>(0);
}

anceParser::CustomContext::CustomContext(TypeContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::CustomContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitCustom(this);
    else return visitor->visitChildren(this);
}
anceParser::TypeContext* anceParser::type()
{
    TypeContext* _localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
    enterRule(_localctx, 102, anceParser::RuleType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(515);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::NATIVE_INTEGER_TYPE:
            {
                _localctx = _tracker.createInstance<anceParser::IntegerContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(507);
                integerType();
                break;
            }

            case anceParser::T__32:
            {
                _localctx = _tracker.createInstance<anceParser::ArrayContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(508);
                arrayType();
                break;
            }

            case anceParser::T__52:
            case anceParser::T__53:
            case anceParser::T__55:
            case anceParser::T__56:
            case anceParser::T__57:
            case anceParser::T__58:
            case anceParser::T__59:
            case anceParser::T__60:
            case anceParser::T__61:
            {
                _localctx = _tracker.createInstance<anceParser::KeywordContext>(_localctx);
                enterOuterAlt(_localctx, 3);
                setState(509);
                keywordType();
                break;
            }

            case anceParser::T__34:
            {
                _localctx = _tracker.createInstance<anceParser::PointerContext>(_localctx);
                enterOuterAlt(_localctx, 4);
                setState(510);
                match(anceParser::T__34);
                setState(511);
                type();
                break;
            }

            case anceParser::T__54:
            {
                _localctx = _tracker.createInstance<anceParser::ReferenceContext>(_localctx);
                enterOuterAlt(_localctx, 5);
                setState(512);
                match(anceParser::T__54);
                setState(513);
                type();
                break;
            }

            case anceParser::IDENTIFIER:
            {
                _localctx = _tracker.createInstance<anceParser::CustomContext>(_localctx);
                enterOuterAlt(_localctx, 6);
                setState(514);
                customType();
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitIntegerType(this);
    else return visitor->visitChildren(this);
}

anceParser::IntegerTypeContext* anceParser::integerType()
{
    IntegerTypeContext* _localctx = _tracker.createInstance<IntegerTypeContext>(_ctx, getState());
    enterRule(_localctx, 104, anceParser::RuleIntegerType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(517);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitArrayType(this);
    else return visitor->visitChildren(this);
}

anceParser::ArrayTypeContext* anceParser::arrayType()
{
    ArrayTypeContext* _localctx = _tracker.createInstance<ArrayTypeContext>(_ctx, getState());
    enterRule(_localctx, 106, anceParser::RuleArrayType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(519);
        match(anceParser::T__32);
        setState(520);
        type();
        setState(521);
        match(anceParser::SEMICOLON);
        setState(522);
        match(anceParser::INTEGER);
        setState(523);
        match(anceParser::T__33);
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

anceParser::BooleanTypeContext* anceParser::KeywordTypeContext::booleanType()
{
    return getRuleContext<anceParser::BooleanTypeContext>(0);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitKeywordType(this);
    else return visitor->visitChildren(this);
}

anceParser::KeywordTypeContext* anceParser::keywordType()
{
    KeywordTypeContext* _localctx = _tracker.createInstance<KeywordTypeContext>(_ctx, getState());
    enterRule(_localctx, 108, anceParser::RuleKeywordType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(529);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__55:
            case anceParser::T__56:
            case anceParser::T__57:
            case anceParser::T__58:
            {
                enterOuterAlt(_localctx, 1);
                setState(525);
                floatingPointType();
                break;
            }

            case anceParser::T__52:
            case anceParser::T__53:
            case anceParser::T__59:
            {
                enterOuterAlt(_localctx, 2);
                setState(526);
                targetDependentType();
                break;
            }

            case anceParser::T__60:
            {
                enterOuterAlt(_localctx, 3);
                setState(527);
                booleanType();
                break;
            }

            case anceParser::T__61:
            {
                enterOuterAlt(_localctx, 4);
                setState(528);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitFloatingPointType(this);
    else return visitor->visitChildren(this);
}

anceParser::FloatingPointTypeContext* anceParser::floatingPointType()
{
    FloatingPointTypeContext* _localctx = _tracker.createInstance<FloatingPointTypeContext>(_ctx, getState());
    enterRule(_localctx, 110, anceParser::RuleFloatingPointType);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(531);
        _la = _input->LA(1);
        if (!((((_la & ~0x3fULL) == 0)
               && ((1ULL << _la)
                   & ((1ULL << anceParser::T__55) | (1ULL << anceParser::T__56) | (1ULL << anceParser::T__57)
                      | (1ULL << anceParser::T__58)))
                      != 0)))
        {
            _errHandler->recoverInline(this);
        }
        else {
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitTargetDependentType(this);
    else return visitor->visitChildren(this);
}

anceParser::TargetDependentTypeContext* anceParser::targetDependentType()
{
    TargetDependentTypeContext* _localctx = _tracker.createInstance<TargetDependentTypeContext>(_ctx, getState());
    enterRule(_localctx, 112, anceParser::RuleTargetDependentType);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(533);
        _la = _input->LA(1);
        if (!((((_la & ~0x3fULL) == 0)
               && ((1ULL << _la)
                   & ((1ULL << anceParser::T__52) | (1ULL << anceParser::T__53) | (1ULL << anceParser::T__59)))
                      != 0)))
        {
            _errHandler->recoverInline(this);
        }
        else {
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

//----------------- BooleanTypeContext ------------------------------------------------------------------

anceParser::BooleanTypeContext::BooleanTypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::BooleanTypeContext::getRuleIndex() const
{
    return anceParser::RuleBooleanType;
}

antlrcpp::Any anceParser::BooleanTypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitBooleanType(this);
    else return visitor->visitChildren(this);
}

anceParser::BooleanTypeContext* anceParser::booleanType()
{
    BooleanTypeContext* _localctx = _tracker.createInstance<BooleanTypeContext>(_ctx, getState());
    enterRule(_localctx, 114, anceParser::RuleBooleanType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(535);
        match(anceParser::T__60);
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitVoidType(this);
    else return visitor->visitChildren(this);
}

anceParser::VoidTypeContext* anceParser::voidType()
{
    VoidTypeContext* _localctx = _tracker.createInstance<VoidTypeContext>(_ctx, getState());
    enterRule(_localctx, 116, anceParser::RuleVoidType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(537);
        match(anceParser::T__61);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- CustomTypeContext ------------------------------------------------------------------

anceParser::CustomTypeContext::CustomTypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

tree::TerminalNode* anceParser::CustomTypeContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

size_t anceParser::CustomTypeContext::getRuleIndex() const
{
    return anceParser::RuleCustomType;
}

antlrcpp::Any anceParser::CustomTypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitCustomType(this);
    else return visitor->visitChildren(this);
}

anceParser::CustomTypeContext* anceParser::customType()
{
    CustomTypeContext* _localctx = _tracker.createInstance<CustomTypeContext>(_ctx, getState());
    enterRule(_localctx, 118, anceParser::RuleCustomType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(539);
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

bool anceParser::sempred(RuleContext* context, size_t ruleIndex, size_t predicateIndex)
{
    switch (ruleIndex)
    {
        case 25:
            return expressionSempred(antlrcpp::downCast<ExpressionContext*>(context), predicateIndex);

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
            return precpred(_ctx, 4);
        case 1:
            return precpred(_ctx, 3);
        case 2:
            return precpred(_ctx, 2);
        case 3:
            return precpred(_ctx, 1);
        case 4:
            return precpred(_ctx, 7);

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
                                                   "typeDefinition",
                                                   "defineAs",
                                                   "defineAlias",
                                                   "accessModifier",
                                                   "code",
                                                   "block",
                                                   "statement",
                                                   "expressionStatement",
                                                   "localVariableDefinition",
                                                   "localReferenceDefinition",
                                                   "dropStatement",
                                                   "assignment",
                                                   "assigner",
                                                   "deleteStatement",
                                                   "returnStatement",
                                                   "assertStatement",
                                                   "ifStatement",
                                                   "whileStatement",
                                                   "matchStatement",
                                                   "matchCase",
                                                   "expression",
                                                   "binaryOperatorMultiplicative",
                                                   "binaryOperatorAdditive",
                                                   "binaryOperatorRelational",
                                                   "binaryOperatorEquality",
                                                   "independentExpression",
                                                   "functionCall",
                                                   "arguments",
                                                   "variableAccess",
                                                   "allocation",
                                                   "allocator",
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
                                                   "booleanType",
                                                   "voidType",
                                                   "customType"};

std::vector<std::string> anceParser::_literalNames = {"",
                                                      "':'",
                                                      "'('",
                                                      "')'",
                                                      "'{'",
                                                      "'}'",
                                                      "'extern'",
                                                      "','",
                                                      "'define'",
                                                      "'as'",
                                                      "'alias'",
                                                      "'public'",
                                                      "'private'",
                                                      "'let'",
                                                      "'ref'",
                                                      "'to'",
                                                      "'drop'",
                                                      "'<:'",
                                                      "'<-'",
                                                      "':='",
                                                      "'delete'",
                                                      "'return'",
                                                      "'assert'",
                                                      "'if'",
                                                      "'then'",
                                                      "'else'",
                                                      "'while'",
                                                      "'do'",
                                                      "'match'",
                                                      "'with'",
                                                      "'|'",
                                                      "'=>'",
                                                      "'default'",
                                                      "'['",
                                                      "']'",
                                                      "'*'",
                                                      "'/'",
                                                      "'%'",
                                                      "'+'",
                                                      "'-'",
                                                      "'<'",
                                                      "'<='",
                                                      "'>'",
                                                      "'>='",
                                                      "'=='",
                                                      "'!='",
                                                      "'new'",
                                                      "'dynamic'",
                                                      "'automatic'",
                                                      "'addressof'",
                                                      "'sizeof'",
                                                      "'true'",
                                                      "'false'",
                                                      "'size'",
                                                      "'diff'",
                                                      "'&'",
                                                      "'half'",
                                                      "'single'",
                                                      "'double'",
                                                      "'quad'",
                                                      "'uiptr'",
                                                      "'bool'",
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
        else {
            _tokenNames.push_back(name);
        }
    }

    static const uint16_t serializedATNSegment0[] = {
        0x3,   0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 0x3,   0x54,  0x220, 0x4,   0x2,   0x9,
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
        0x2f,  0x4,    0x30,   0x9,    0x30,   0x4,    0x31,   0x9,    0x31,   0x4,   0x32,  0x9,   0x32,  0x4,   0x33,
        0x9,   0x33,   0x4,    0x34,   0x9,    0x34,   0x4,    0x35,   0x9,    0x35,  0x4,   0x36,  0x9,   0x36,  0x4,
        0x37,  0x9,    0x37,   0x4,    0x38,   0x9,    0x38,   0x4,    0x39,   0x9,   0x39,  0x4,   0x3a,  0x9,   0x3a,
        0x4,   0x3b,   0x9,    0x3b,   0x4,    0x3c,   0x9,    0x3c,   0x4,    0x3d,  0x9,   0x3d,  0x3,   0x2,   0x3,
        0x2,   0x3,    0x2,    0x7,    0x2,    0x7e,   0xa,    0x2,    0xc,    0x2,   0xe,   0x2,   0x81,  0xb,   0x2,
        0x3,   0x2,    0x3,    0x2,    0x3,    0x3,    0x3,    0x3,    0x5,    0x3,   0x87,  0xa,   0x3,   0x3,   0x3,
        0x3,   0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,   0x5,   0x3,   0x8f,  0xa,   0x3,
        0x3,   0x3,    0x3,    0x3,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,   0x3,   0x4,   0x3,   0x4,   0x3,
        0x4,   0x3,    0x4,    0x5,    0x4,    0x9a,   0xa,    0x4,    0x3,    0x4,   0x3,   0x4,   0x7,   0x4,   0x9e,
        0xa,   0x4,    0xc,    0x4,    0xe,    0x4,    0xa1,   0xb,    0x4,    0x3,   0x4,   0x3,   0x4,   0x3,   0x4,
        0x3,   0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,   0x3,   0x4,   0x5,   0x4,   0xac,
        0xa,   0x4,    0x3,    0x4,    0x3,    0x4,    0x5,    0x4,    0xb0,   0xa,   0x4,   0x3,   0x5,   0x3,   0x5,
        0x3,   0x5,    0x7,    0x5,    0xb5,   0xa,    0x5,    0xc,    0x5,    0xe,   0x5,   0xb8,  0xb,   0x5,   0x5,
        0x5,   0xba,   0xa,    0x5,    0x3,    0x6,    0x3,    0x6,    0x3,    0x6,   0x3,   0x6,   0x3,   0x7,   0x3,
        0x7,   0x5,    0x7,    0xc2,   0xa,    0x7,    0x3,    0x8,    0x3,    0x8,   0x3,   0x8,   0x3,   0x8,   0x3,
        0x8,   0x3,    0x8,    0x3,    0x9,    0x3,    0x9,    0x3,    0x9,    0x3,   0x9,   0x3,   0x9,   0x3,   0x9,
        0x3,   0xa,    0x3,    0xa,    0x5,    0xa,    0xd2,   0xa,    0xa,    0x3,   0xb,   0x3,   0xb,   0x5,   0xb,
        0xd6,  0xa,    0xb,    0x3,    0xc,    0x3,    0xc,    0x7,    0xc,    0xda,  0xa,   0xc,   0xc,   0xc,   0xe,
        0xc,   0xdd,   0xb,    0xc,    0x3,    0xc,    0x3,    0xc,    0x3,    0xd,   0x3,   0xd,   0x3,   0xd,   0x3,
        0xd,   0x3,    0xd,    0x3,    0xd,    0x3,    0xd,    0x3,    0xd,    0x3,   0xd,   0x3,   0xd,   0x3,   0xd,
        0x5,   0xd,    0xec,   0xa,    0xd,    0x3,    0xe,    0x3,    0xe,    0x3,   0xe,   0x3,   0xf,   0x3,   0xf,
        0x3,   0xf,    0x3,    0xf,    0x3,    0xf,    0x3,    0xf,    0x3,    0xf,   0x5,   0xf,   0xf8,  0xa,   0xf,
        0x3,   0xf,    0x3,    0xf,    0x3,    0x10,   0x3,    0x10,   0x3,    0x10,  0x3,   0x10,  0x3,   0x10,  0x3,
        0x10,  0x3,    0x10,   0x3,    0x10,   0x3,    0x10,   0x3,    0x10,   0x3,   0x10,  0x3,   0x10,  0x3,   0x10,
        0x3,   0x10,   0x3,    0x10,   0x3,    0x10,   0x3,    0x10,   0x5,    0x10,  0x10d, 0xa,   0x10,  0x3,   0x11,
        0x3,   0x11,   0x3,    0x11,   0x3,    0x11,   0x3,    0x12,   0x3,    0x12,  0x3,   0x12,  0x3,   0x12,  0x3,
        0x12,  0x3,    0x13,   0x3,    0x13,   0x3,    0x13,   0x5,    0x13,   0x11b, 0xa,   0x13,  0x3,   0x14,  0x3,
        0x14,  0x5,    0x14,   0x11f,  0xa,    0x14,   0x3,    0x14,   0x3,    0x14,  0x3,   0x14,  0x3,   0x15,  0x3,
        0x15,  0x5,    0x15,   0x126,  0xa,    0x15,   0x3,    0x15,   0x3,    0x15,  0x3,   0x16,  0x3,   0x16,  0x3,
        0x16,  0x3,    0x16,   0x3,    0x17,   0x3,    0x17,   0x3,    0x17,   0x3,   0x17,  0x3,   0x17,  0x3,   0x17,
        0x5,   0x17,   0x134,  0xa,    0x17,   0x3,    0x18,   0x3,    0x18,   0x3,   0x18,  0x3,   0x18,  0x3,   0x18,
        0x3,   0x19,   0x3,    0x19,   0x3,    0x19,   0x3,    0x19,   0x3,    0x19,  0x7,   0x19,  0x140, 0xa,   0x19,
        0xc,   0x19,   0xe,    0x19,   0x143,  0xb,    0x19,   0x3,    0x19,   0x3,   0x19,  0x3,   0x1a,  0x3,   0x1a,
        0x3,   0x1a,   0x7,    0x1a,   0x14a,  0xa,    0x1a,   0xc,    0x1a,   0xe,   0x1a,  0x14d, 0xb,   0x1a,  0x3,
        0x1a,  0x3,    0x1a,   0x3,    0x1a,   0x3,    0x1a,   0x3,    0x1a,   0x3,   0x1a,  0x5,   0x1a,  0x155, 0xa,
        0x1a,  0x3,    0x1b,   0x3,    0x1b,   0x3,    0x1b,   0x3,    0x1b,   0x3,   0x1b,  0x3,   0x1b,  0x3,   0x1b,
        0x3,   0x1b,   0x3,    0x1b,   0x3,    0x1b,   0x3,    0x1b,   0x3,    0x1b,  0x3,   0x1b,  0x5,   0x1b,  0x164,
        0xa,   0x1b,   0x3,    0x1b,   0x3,    0x1b,   0x3,    0x1b,   0x3,    0x1b,  0x3,   0x1b,  0x3,   0x1b,  0x3,
        0x1b,  0x3,    0x1b,   0x3,    0x1b,   0x3,    0x1b,   0x3,    0x1b,   0x3,   0x1b,  0x3,   0x1b,  0x3,   0x1b,
        0x3,   0x1b,   0x3,    0x1b,   0x3,    0x1b,   0x3,    0x1b,   0x3,    0x1b,  0x3,   0x1b,  0x3,   0x1b,  0x7,
        0x1b,  0x17b,  0xa,    0x1b,   0xc,    0x1b,   0xe,    0x1b,   0x17e,  0xb,   0x1b,  0x3,   0x1c,  0x3,   0x1c,
        0x3,   0x1c,   0x5,    0x1c,   0x183,  0xa,    0x1c,   0x3,    0x1d,   0x3,   0x1d,  0x5,   0x1d,  0x187, 0xa,
        0x1d,  0x3,    0x1e,   0x3,    0x1e,   0x3,    0x1e,   0x3,    0x1e,   0x5,   0x1e,  0x18d, 0xa,   0x1e,  0x3,
        0x1f,  0x3,    0x1f,   0x5,    0x1f,   0x191,  0xa,    0x1f,   0x3,    0x20,  0x3,   0x20,  0x3,   0x21,  0x3,
        0x21,  0x3,    0x21,   0x3,    0x21,   0x3,    0x21,   0x3,    0x22,   0x3,   0x22,  0x3,   0x22,  0x7,   0x22,
        0x19d, 0xa,    0x22,   0xc,    0x22,   0xe,    0x22,   0x1a0,  0xb,    0x22,  0x5,   0x22,  0x1a2, 0xa,   0x22,
        0x3,   0x23,   0x3,    0x23,   0x3,    0x24,   0x3,    0x24,   0x3,    0x24,  0x3,   0x24,  0x3,   0x24,  0x5,
        0x24,  0x1ab,  0xa,    0x24,   0x3,    0x24,   0x3,    0x24,   0x3,    0x24,  0x3,   0x25,  0x3,   0x25,  0x5,
        0x25,  0x1b2,  0xa,    0x25,   0x3,    0x26,   0x3,    0x26,   0x3,    0x26,  0x3,   0x27,  0x3,   0x27,  0x3,
        0x27,  0x3,    0x27,   0x3,    0x27,   0x5,    0x27,   0x1bc,  0xa,    0x27,  0x3,   0x28,  0x3,   0x28,  0x3,
        0x28,  0x3,    0x29,   0x3,    0x29,   0x3,    0x29,   0x3,    0x29,   0x3,   0x29,  0x3,   0x2a,  0x3,   0x2a,
        0x3,   0x2a,   0x3,    0x2a,   0x3,    0x2a,   0x3,    0x2a,   0x3,    0x2a,  0x5,   0x2a,  0x1cd, 0xa,   0x2a,
        0x3,   0x2b,   0x5,    0x2b,   0x1d0,  0xa,    0x2b,   0x3,    0x2b,   0x3,   0x2b,  0x3,   0x2c,  0x3,   0x2c,
        0x3,   0x2d,   0x3,    0x2d,   0x3,    0x2d,   0x5,    0x2d,   0x1d9,  0xa,   0x2d,  0x3,   0x2e,  0x3,   0x2e,
        0x3,   0x2e,   0x3,    0x2e,   0x3,    0x2f,   0x3,    0x2f,   0x3,    0x2f,  0x3,   0x2f,  0x3,   0x30,  0x3,
        0x30,  0x3,    0x30,   0x3,    0x30,   0x3,    0x30,   0x3,    0x30,   0x3,   0x30,  0x3,   0x30,  0x3,   0x30,
        0x5,   0x30,   0x1ec,  0xa,    0x30,   0x3,    0x31,   0x3,    0x31,   0x3,   0x32,  0x3,   0x32,  0x5,   0x32,
        0x1f2, 0xa,    0x32,   0x3,    0x33,   0x3,    0x33,   0x3,    0x33,   0x5,   0x33,  0x1f7, 0xa,   0x33,  0x3,
        0x34,  0x3,    0x34,   0x3,    0x34,   0x5,    0x34,   0x1fc,  0xa,    0x34,  0x3,   0x35,  0x3,   0x35,  0x3,
        0x35,  0x3,    0x35,   0x3,    0x35,   0x3,    0x35,   0x3,    0x35,   0x3,   0x35,  0x5,   0x35,  0x206, 0xa,
        0x35,  0x3,    0x36,   0x3,    0x36,   0x3,    0x37,   0x3,    0x37,   0x3,   0x37,  0x3,   0x37,  0x3,   0x37,
        0x3,   0x37,   0x3,    0x38,   0x3,    0x38,   0x3,    0x38,   0x3,    0x38,  0x5,   0x38,  0x214, 0xa,   0x38,
        0x3,   0x39,   0x3,    0x39,   0x3,    0x3a,   0x3,    0x3a,   0x3,    0x3b,  0x3,   0x3b,  0x3,   0x3c,  0x3,
        0x3c,  0x3,    0x3d,   0x3,    0x3d,   0x3,    0x3d,   0x2,    0x3,    0x34,  0x3e,  0x2,   0x4,   0x6,   0x8,
        0xa,   0xc,    0xe,    0x10,   0x12,   0x14,   0x16,   0x18,   0x1a,   0x1c,  0x1e,  0x20,  0x22,  0x24,  0x26,
        0x28,  0x2a,   0x2c,   0x2e,   0x30,   0x32,   0x34,   0x36,   0x38,   0x3a,  0x3c,  0x3e,  0x40,  0x42,  0x44,
        0x46,  0x48,   0x4a,   0x4c,   0x4e,   0x50,   0x52,   0x54,   0x56,   0x58,  0x5a,  0x5c,  0x5e,  0x60,  0x62,
        0x64,  0x66,   0x68,   0x6a,   0x6c,   0x6e,   0x70,   0x72,   0x74,   0x76,  0x78,  0x2,   0x5,   0x3,   0x2,
        0x46,  0x49,   0x3,    0x2,    0x3a,   0x3d,   0x4,    0x2,    0x37,   0x38,  0x3e,  0x3e,  0x2,   0x235, 0x2,
        0x7f,  0x3,    0x2,    0x2,    0x2,    0x4,    0x84,   0x3,    0x2,    0x2,   0x2,   0x6,   0xaf,  0x3,   0x2,
        0x2,   0x2,    0x8,    0xb9,   0x3,    0x2,    0x2,    0x2,    0xa,    0xbb,  0x3,   0x2,   0x2,   0x2,   0xc,
        0xc1,  0x3,    0x2,    0x2,    0x2,    0xe,    0xc3,   0x3,    0x2,    0x2,   0x2,   0x10,  0xc9,  0x3,   0x2,
        0x2,   0x2,    0x12,   0xd1,   0x3,    0x2,    0x2,    0x2,    0x14,   0xd5,  0x3,   0x2,   0x2,   0x2,   0x16,
        0xd7,  0x3,    0x2,    0x2,    0x2,    0x18,   0xeb,   0x3,    0x2,    0x2,   0x2,   0x1a,  0xed,  0x3,   0x2,
        0x2,   0x2,    0x1c,   0xf0,   0x3,    0x2,    0x2,    0x2,    0x1e,   0x10c, 0x3,   0x2,   0x2,   0x2,   0x20,
        0x10e, 0x3,    0x2,    0x2,    0x2,    0x22,   0x112,  0x3,    0x2,    0x2,   0x2,   0x24,  0x11a, 0x3,   0x2,
        0x2,   0x2,    0x26,   0x11c,  0x3,    0x2,    0x2,    0x2,    0x28,   0x123, 0x3,   0x2,   0x2,   0x2,   0x2a,
        0x129, 0x3,    0x2,    0x2,    0x2,    0x2c,   0x12d,  0x3,    0x2,    0x2,   0x2,   0x2e,  0x135, 0x3,   0x2,
        0x2,   0x2,    0x30,   0x13a,  0x3,    0x2,    0x2,    0x2,    0x32,   0x154, 0x3,   0x2,   0x2,   0x2,   0x34,
        0x163, 0x3,    0x2,    0x2,    0x2,    0x36,   0x182,  0x3,    0x2,    0x2,   0x2,   0x38,  0x186, 0x3,   0x2,
        0x2,   0x2,    0x3a,   0x18c,  0x3,    0x2,    0x2,    0x2,    0x3c,   0x190, 0x3,   0x2,   0x2,   0x2,   0x3e,
        0x192, 0x3,    0x2,    0x2,    0x2,    0x40,   0x194,  0x3,    0x2,    0x2,   0x2,   0x42,  0x1a1, 0x3,   0x2,
        0x2,   0x2,    0x44,   0x1a3,  0x3,    0x2,    0x2,    0x2,    0x46,   0x1a5, 0x3,   0x2,   0x2,   0x2,   0x48,
        0x1b1, 0x3,    0x2,    0x2,    0x2,    0x4a,   0x1b3,  0x3,    0x2,    0x2,   0x2,   0x4c,  0x1bb, 0x3,   0x2,
        0x2,   0x2,    0x4e,   0x1bd,  0x3,    0x2,    0x2,    0x2,    0x50,   0x1c0, 0x3,   0x2,   0x2,   0x2,   0x52,
        0x1cc, 0x3,    0x2,    0x2,    0x2,    0x54,   0x1cf,  0x3,    0x2,    0x2,   0x2,   0x56,  0x1d3, 0x3,   0x2,
        0x2,   0x2,    0x58,   0x1d8,  0x3,    0x2,    0x2,    0x2,    0x5a,   0x1da, 0x3,   0x2,   0x2,   0x2,   0x5c,
        0x1de, 0x3,    0x2,    0x2,    0x2,    0x5e,   0x1eb,  0x3,    0x2,    0x2,   0x2,   0x60,  0x1ed, 0x3,   0x2,
        0x2,   0x2,    0x62,   0x1f1,  0x3,    0x2,    0x2,    0x2,    0x64,   0x1f3, 0x3,   0x2,   0x2,   0x2,   0x66,
        0x1f8, 0x3,    0x2,    0x2,    0x2,    0x68,   0x205,  0x3,    0x2,    0x2,   0x2,   0x6a,  0x207, 0x3,   0x2,
        0x2,   0x2,    0x6c,   0x209,  0x3,    0x2,    0x2,    0x2,    0x6e,   0x213, 0x3,   0x2,   0x2,   0x2,   0x70,
        0x215, 0x3,    0x2,    0x2,    0x2,    0x72,   0x217,  0x3,    0x2,    0x2,   0x2,   0x74,  0x219, 0x3,   0x2,
        0x2,   0x2,    0x76,   0x21b,  0x3,    0x2,    0x2,    0x2,    0x78,   0x21d, 0x3,   0x2,   0x2,   0x2,   0x7a,
        0x7e,  0x5,    0x4,    0x3,    0x2,    0x7b,   0x7e,   0x5,    0x6,    0x4,   0x2,   0x7c,  0x7e,  0x5,   0xc,
        0x7,   0x2,    0x7d,   0x7a,   0x3,    0x2,    0x2,    0x2,    0x7d,   0x7b,  0x3,   0x2,   0x2,   0x2,   0x7d,
        0x7c,  0x3,    0x2,    0x2,    0x2,    0x7e,   0x81,   0x3,    0x2,    0x2,   0x2,   0x7f,  0x7d,  0x3,   0x2,
        0x2,   0x2,    0x7f,   0x80,   0x3,    0x2,    0x2,    0x2,    0x80,   0x82,  0x3,   0x2,   0x2,   0x2,   0x81,
        0x7f,  0x3,    0x2,    0x2,    0x2,    0x82,   0x83,   0x7,    0x2,    0x2,   0x3,   0x83,  0x3,   0x3,   0x2,
        0x2,   0x2,    0x84,   0x86,   0x5,    0x12,   0xa,    0x2,    0x85,   0x87,  0x7,   0x4f,  0x2,   0x2,   0x86,
        0x85,  0x3,    0x2,    0x2,    0x2,    0x86,   0x87,   0x3,    0x2,    0x2,   0x2,   0x87,  0x88,  0x3,   0x2,
        0x2,   0x2,    0x88,   0x89,   0x7,    0x50,   0x2,    0x2,    0x89,   0x8a,  0x7,   0x3,   0x2,   0x2,   0x8a,
        0x8e,  0x5,    0x68,   0x35,   0x2,    0x8b,   0x8c,   0x5,    0x24,   0x13,  0x2,   0x8c,  0x8d,  0x5,   0x52,
        0x2a,  0x2,    0x8d,   0x8f,   0x3,    0x2,    0x2,    0x2,    0x8e,   0x8b,  0x3,   0x2,   0x2,   0x2,   0x8e,
        0x8f,  0x3,    0x2,    0x2,    0x2,    0x8f,   0x90,   0x3,    0x2,    0x2,   0x2,   0x90,  0x91,  0x7,   0x51,
        0x2,   0x2,    0x91,   0x5,    0x3,    0x2,    0x2,    0x2,    0x92,   0x93,  0x5,   0x12,  0xa,   0x2,   0x93,
        0x94,  0x7,    0x50,   0x2,    0x2,    0x94,   0x95,   0x7,    0x4,    0x2,   0x2,   0x95,  0x96,  0x5,   0x8,
        0x5,   0x2,    0x96,   0x99,   0x7,    0x5,    0x2,    0x2,    0x97,   0x98,  0x7,   0x3,   0x2,   0x2,   0x98,
        0x9a,  0x5,    0x68,   0x35,   0x2,    0x99,   0x97,   0x3,    0x2,    0x2,   0x2,   0x99,  0x9a,  0x3,   0x2,
        0x2,   0x2,    0x9a,   0x9b,   0x3,    0x2,    0x2,    0x2,    0x9b,   0x9f,  0x7,   0x6,   0x2,   0x2,   0x9c,
        0x9e,  0x5,    0x14,   0xb,    0x2,    0x9d,   0x9c,   0x3,    0x2,    0x2,   0x2,   0x9e,  0xa1,  0x3,   0x2,
        0x2,   0x2,    0x9f,   0x9d,   0x3,    0x2,    0x2,    0x2,    0x9f,   0xa0,  0x3,   0x2,   0x2,   0x2,   0xa0,
        0xa2,  0x3,    0x2,    0x2,    0x2,    0xa1,   0x9f,   0x3,    0x2,    0x2,   0x2,   0xa2,  0xa3,  0x7,   0x7,
        0x2,   0x2,    0xa3,   0xb0,   0x3,    0x2,    0x2,    0x2,    0xa4,   0xa5,  0x7,   0x8,   0x2,   0x2,   0xa5,
        0xa6,  0x7,    0x50,   0x2,    0x2,    0xa6,   0xa7,   0x7,    0x4,    0x2,   0x2,   0xa7,  0xa8,  0x5,   0x8,
        0x5,   0x2,    0xa8,   0xab,   0x7,    0x5,    0x2,    0x2,    0xa9,   0xaa,  0x7,   0x3,   0x2,   0x2,   0xaa,
        0xac,  0x5,    0x68,   0x35,   0x2,    0xab,   0xa9,   0x3,    0x2,    0x2,   0x2,   0xab,  0xac,  0x3,   0x2,
        0x2,   0x2,    0xac,   0xad,   0x3,    0x2,    0x2,    0x2,    0xad,   0xae,  0x7,   0x51,  0x2,   0x2,   0xae,
        0xb0,  0x3,    0x2,    0x2,    0x2,    0xaf,   0x92,   0x3,    0x2,    0x2,   0x2,   0xaf,  0xa4,  0x3,   0x2,
        0x2,   0x2,    0xb0,   0x7,    0x3,    0x2,    0x2,    0x2,    0xb1,   0xb6,  0x5,   0xa,   0x6,   0x2,   0xb2,
        0xb3,  0x7,    0x9,    0x2,    0x2,    0xb3,   0xb5,   0x5,    0xa,    0x6,   0x2,   0xb4,  0xb2,  0x3,   0x2,
        0x2,   0x2,    0xb5,   0xb8,   0x3,    0x2,    0x2,    0x2,    0xb6,   0xb4,  0x3,   0x2,   0x2,   0x2,   0xb6,
        0xb7,  0x3,    0x2,    0x2,    0x2,    0xb7,   0xba,   0x3,    0x2,    0x2,   0x2,   0xb8,  0xb6,  0x3,   0x2,
        0x2,   0x2,    0xb9,   0xb1,   0x3,    0x2,    0x2,    0x2,    0xb9,   0xba,  0x3,   0x2,   0x2,   0x2,   0xba,
        0x9,   0x3,    0x2,    0x2,    0x2,    0xbb,   0xbc,   0x7,    0x50,   0x2,   0x2,   0xbc,  0xbd,  0x7,   0x3,
        0x2,   0x2,    0xbd,   0xbe,   0x5,    0x68,   0x35,   0x2,    0xbe,   0xb,   0x3,   0x2,   0x2,   0x2,   0xbf,
        0xc2,  0x5,    0xe,    0x8,    0x2,    0xc0,   0xc2,   0x5,    0x10,   0x9,   0x2,   0xc1,  0xbf,  0x3,   0x2,
        0x2,   0x2,    0xc1,   0xc0,   0x3,    0x2,    0x2,    0x2,    0xc2,   0xd,   0x3,   0x2,   0x2,   0x2,   0xc3,
        0xc4,  0x7,    0xa,    0x2,    0x2,    0xc4,   0xc5,   0x7,    0x50,   0x2,   0x2,   0xc5,  0xc6,  0x7,   0xb,
        0x2,   0x2,    0xc6,   0xc7,   0x5,    0x68,   0x35,   0x2,    0xc7,   0xc8,  0x7,   0x51,  0x2,   0x2,   0xc8,
        0xf,   0x3,    0x2,    0x2,    0x2,    0xc9,   0xca,   0x7,    0xa,    0x2,   0x2,   0xca,  0xcb,  0x7,   0x50,
        0x2,   0x2,    0xcb,   0xcc,   0x7,    0xc,    0x2,    0x2,    0xcc,   0xcd,  0x5,   0x68,  0x35,  0x2,   0xcd,
        0xce,  0x7,    0x51,   0x2,    0x2,    0xce,   0x11,   0x3,    0x2,    0x2,   0x2,   0xcf,  0xd2,  0x7,   0xd,
        0x2,   0x2,    0xd0,   0xd2,   0x7,    0xe,    0x2,    0x2,    0xd1,   0xcf,  0x3,   0x2,   0x2,   0x2,   0xd1,
        0xd0,  0x3,    0x2,    0x2,    0x2,    0xd2,   0x13,   0x3,    0x2,    0x2,   0x2,   0xd3,  0xd6,  0x5,   0x18,
        0xd,   0x2,    0xd4,   0xd6,   0x5,    0x16,   0xc,    0x2,    0xd5,   0xd3,  0x3,   0x2,   0x2,   0x2,   0xd5,
        0xd4,  0x3,    0x2,    0x2,    0x2,    0xd6,   0x15,   0x3,    0x2,    0x2,   0x2,   0xd7,  0xdb,  0x7,   0x6,
        0x2,   0x2,    0xd8,   0xda,   0x5,    0x14,   0xb,    0x2,    0xd9,   0xd8,  0x3,   0x2,   0x2,   0x2,   0xda,
        0xdd,  0x3,    0x2,    0x2,    0x2,    0xdb,   0xd9,   0x3,    0x2,    0x2,   0x2,   0xdb,  0xdc,  0x3,   0x2,
        0x2,   0x2,    0xdc,   0xde,   0x3,    0x2,    0x2,    0x2,    0xdd,   0xdb,  0x3,   0x2,   0x2,   0x2,   0xde,
        0xdf,  0x7,    0x7,    0x2,    0x2,    0xdf,   0x17,   0x3,    0x2,    0x2,   0x2,   0xe0,  0xec,  0x5,   0x1a,
        0xe,   0x2,    0xe1,   0xec,   0x5,    0x1c,   0xf,    0x2,    0xe2,   0xec,  0x5,   0x1e,  0x10,  0x2,   0xe3,
        0xec,  0x5,    0x20,   0x11,   0x2,    0xe4,   0xec,   0x5,    0x22,   0x12,  0x2,   0xe5,  0xec,  0x5,   0x26,
        0x14,  0x2,    0xe6,   0xec,   0x5,    0x28,   0x15,   0x2,    0xe7,   0xec,  0x5,   0x2a,  0x16,  0x2,   0xe8,
        0xec,  0x5,    0x2c,   0x17,   0x2,    0xe9,   0xec,   0x5,    0x2e,   0x18,  0x2,   0xea,  0xec,  0x5,   0x30,
        0x19,  0x2,    0xeb,   0xe0,   0x3,    0x2,    0x2,    0x2,    0xeb,   0xe1,  0x3,   0x2,   0x2,   0x2,   0xeb,
        0xe2,  0x3,    0x2,    0x2,    0x2,    0xeb,   0xe3,   0x3,    0x2,    0x2,   0x2,   0xeb,  0xe4,  0x3,   0x2,
        0x2,   0x2,    0xeb,   0xe5,   0x3,    0x2,    0x2,    0x2,    0xeb,   0xe6,  0x3,   0x2,   0x2,   0x2,   0xeb,
        0xe7,  0x3,    0x2,    0x2,    0x2,    0xeb,   0xe8,   0x3,    0x2,    0x2,   0x2,   0xeb,  0xe9,  0x3,   0x2,
        0x2,   0x2,    0xeb,   0xea,   0x3,    0x2,    0x2,    0x2,    0xec,   0x19,  0x3,   0x2,   0x2,   0x2,   0xed,
        0xee,  0x5,    0x3e,   0x20,   0x2,    0xee,   0xef,   0x7,    0x51,   0x2,   0x2,   0xef,  0x1b,  0x3,   0x2,
        0x2,   0x2,    0xf0,   0xf1,   0x7,    0xf,    0x2,    0x2,    0xf1,   0xf2,  0x7,   0x50,  0x2,   0x2,   0xf2,
        0xf3,  0x7,    0x3,    0x2,    0x2,    0xf3,   0xf7,   0x5,    0x68,   0x35,  0x2,   0xf4,  0xf5,  0x5,   0x24,
        0x13,  0x2,    0xf5,   0xf6,   0x5,    0x34,   0x1b,   0x2,    0xf6,   0xf8,  0x3,   0x2,   0x2,   0x2,   0xf7,
        0xf4,  0x3,    0x2,    0x2,    0x2,    0xf7,   0xf8,   0x3,    0x2,    0x2,   0x2,   0xf8,  0xf9,  0x3,   0x2,
        0x2,   0x2,    0xf9,   0xfa,   0x7,    0x51,   0x2,    0x2,    0xfa,   0x1d,  0x3,   0x2,   0x2,   0x2,   0xfb,
        0xfc,  0x7,    0xf,    0x2,    0x2,    0xfc,   0xfd,   0x7,    0x50,   0x2,   0x2,   0xfd,  0xfe,  0x7,   0x3,
        0x2,   0x2,    0xfe,   0xff,   0x5,    0x68,   0x35,   0x2,    0xff,   0x100, 0x7,   0x10,  0x2,   0x2,   0x100,
        0x101, 0x5,    0x34,   0x1b,   0x2,    0x101,  0x102,  0x7,    0x51,   0x2,   0x2,   0x102, 0x10d, 0x3,   0x2,
        0x2,   0x2,    0x103,  0x104,  0x7,    0xf,    0x2,    0x2,    0x104,  0x105, 0x7,   0x50,  0x2,   0x2,   0x105,
        0x106, 0x7,    0x3,    0x2,    0x2,    0x106,  0x107,  0x5,    0x68,   0x35,  0x2,   0x107, 0x108, 0x7,   0x10,
        0x2,   0x2,    0x108,  0x109,  0x7,    0x11,   0x2,    0x2,    0x109,  0x10a, 0x5,   0x34,  0x1b,  0x2,   0x10a,
        0x10b, 0x7,    0x51,   0x2,    0x2,    0x10b,  0x10d,  0x3,    0x2,    0x2,   0x2,   0x10c, 0xfb,  0x3,   0x2,
        0x2,   0x2,    0x10c,  0x103,  0x3,    0x2,    0x2,    0x2,    0x10d,  0x1f,  0x3,   0x2,   0x2,   0x2,   0x10e,
        0x10f, 0x7,    0x12,   0x2,    0x2,    0x10f,  0x110,  0x7,    0x50,   0x2,   0x2,   0x110, 0x111, 0x7,   0x51,
        0x2,   0x2,    0x111,  0x21,   0x3,    0x2,    0x2,    0x2,    0x112,  0x113, 0x5,   0x34,  0x1b,  0x2,   0x113,
        0x114, 0x5,    0x24,   0x13,   0x2,    0x114,  0x115,  0x5,    0x34,   0x1b,  0x2,   0x115, 0x116, 0x7,   0x51,
        0x2,   0x2,    0x116,  0x23,   0x3,    0x2,    0x2,    0x2,    0x117,  0x11b, 0x7,   0x13,  0x2,   0x2,   0x118,
        0x11b, 0x7,    0x14,   0x2,    0x2,    0x119,  0x11b,  0x7,    0x15,   0x2,   0x2,   0x11a, 0x117, 0x3,   0x2,
        0x2,   0x2,    0x11a,  0x118,  0x3,    0x2,    0x2,    0x2,    0x11a,  0x119, 0x3,   0x2,   0x2,   0x2,   0x11b,
        0x25,  0x3,    0x2,    0x2,    0x2,    0x11c,  0x11e,  0x7,    0x16,   0x2,   0x2,   0x11d, 0x11f, 0x7,   0x4e,
        0x2,   0x2,    0x11e,  0x11d,  0x3,    0x2,    0x2,    0x2,    0x11e,  0x11f, 0x3,   0x2,   0x2,   0x2,   0x11f,
        0x120, 0x3,    0x2,    0x2,    0x2,    0x120,  0x121,  0x5,    0x34,   0x1b,  0x2,   0x121, 0x122, 0x7,   0x51,
        0x2,   0x2,    0x122,  0x27,   0x3,    0x2,    0x2,    0x2,    0x123,  0x125, 0x7,   0x17,  0x2,   0x2,   0x124,
        0x126, 0x5,    0x34,   0x1b,   0x2,    0x125,  0x124,  0x3,    0x2,    0x2,   0x2,   0x125, 0x126, 0x3,   0x2,
        0x2,   0x2,    0x126,  0x127,  0x3,    0x2,    0x2,    0x2,    0x127,  0x128, 0x7,   0x51,  0x2,   0x2,   0x128,
        0x29,  0x3,    0x2,    0x2,    0x2,    0x129,  0x12a,  0x7,    0x18,   0x2,   0x2,   0x12a, 0x12b, 0x5,   0x34,
        0x1b,  0x2,    0x12b,  0x12c,  0x7,    0x51,   0x2,    0x2,    0x12c,  0x2b,  0x3,   0x2,   0x2,   0x2,   0x12d,
        0x12e, 0x7,    0x19,   0x2,    0x2,    0x12e,  0x12f,  0x5,    0x34,   0x1b,  0x2,   0x12f, 0x130, 0x7,   0x1a,
        0x2,   0x2,    0x130,  0x133,  0x5,    0x14,   0xb,    0x2,    0x131,  0x132, 0x7,   0x1b,  0x2,   0x2,   0x132,
        0x134, 0x5,    0x14,   0xb,    0x2,    0x133,  0x131,  0x3,    0x2,    0x2,   0x2,   0x133, 0x134, 0x3,   0x2,
        0x2,   0x2,    0x134,  0x2d,   0x3,    0x2,    0x2,    0x2,    0x135,  0x136, 0x7,   0x1c,  0x2,   0x2,   0x136,
        0x137, 0x5,    0x34,   0x1b,   0x2,    0x137,  0x138,  0x7,    0x1d,   0x2,   0x2,   0x138, 0x139, 0x5,   0x14,
        0xb,   0x2,    0x139,  0x2f,   0x3,    0x2,    0x2,    0x2,    0x13a,  0x13b, 0x7,   0x1e,  0x2,   0x2,   0x13b,
        0x13c, 0x5,    0x34,   0x1b,   0x2,    0x13c,  0x13d,  0x7,    0x1f,   0x2,   0x2,   0x13d, 0x141, 0x7,   0x6,
        0x2,   0x2,    0x13e,  0x140,  0x5,    0x32,   0x1a,   0x2,    0x13f,  0x13e, 0x3,   0x2,   0x2,   0x2,   0x140,
        0x143, 0x3,    0x2,    0x2,    0x2,    0x141,  0x13f,  0x3,    0x2,    0x2,   0x2,   0x141, 0x142, 0x3,   0x2,
        0x2,   0x2,    0x142,  0x144,  0x3,    0x2,    0x2,    0x2,    0x143,  0x141, 0x3,   0x2,   0x2,   0x2,   0x144,
        0x145, 0x7,    0x7,    0x2,    0x2,    0x145,  0x31,   0x3,    0x2,    0x2,   0x2,   0x146, 0x14b, 0x5,   0x52,
        0x2a,  0x2,    0x147,  0x148,  0x7,    0x20,   0x2,    0x2,    0x148,  0x14a, 0x5,   0x52,  0x2a,  0x2,   0x149,
        0x147, 0x3,    0x2,    0x2,    0x2,    0x14a,  0x14d,  0x3,    0x2,    0x2,   0x2,   0x14b, 0x149, 0x3,   0x2,
        0x2,   0x2,    0x14b,  0x14c,  0x3,    0x2,    0x2,    0x2,    0x14c,  0x14e, 0x3,   0x2,   0x2,   0x2,   0x14d,
        0x14b, 0x3,    0x2,    0x2,    0x2,    0x14e,  0x14f,  0x7,    0x21,   0x2,   0x2,   0x14f, 0x150, 0x5,   0x14,
        0xb,   0x2,    0x150,  0x155,  0x3,    0x2,    0x2,    0x2,    0x151,  0x152, 0x7,   0x22,  0x2,   0x2,   0x152,
        0x153, 0x7,    0x21,   0x2,    0x2,    0x153,  0x155,  0x5,    0x14,   0xb,   0x2,   0x154, 0x146, 0x3,   0x2,
        0x2,   0x2,    0x154,  0x151,  0x3,    0x2,    0x2,    0x2,    0x155,  0x33,  0x3,   0x2,   0x2,   0x2,   0x156,
        0x157, 0x8,    0x1b,   0x1,    0x2,    0x157,  0x164,  0x5,    0x44,   0x23,  0x2,   0x158, 0x164, 0x5,   0x46,
        0x24,  0x2,    0x159,  0x164,  0x5,    0x4a,   0x26,   0x2,    0x15a,  0x164, 0x5,   0x4c,  0x27,  0x2,   0x15b,
        0x164, 0x5,    0x4e,   0x28,   0x2,    0x15c,  0x164,  0x5,    0x50,   0x29,  0x2,   0x15d, 0x164, 0x5,   0x52,
        0x2a,  0x2,    0x15e,  0x164,  0x5,    0x3e,   0x20,   0x2,    0x15f,  0x160, 0x7,   0x4,   0x2,   0x2,   0x160,
        0x161, 0x5,    0x34,   0x1b,   0x2,    0x161,  0x162,  0x7,    0x5,    0x2,   0x2,   0x162, 0x164, 0x3,   0x2,
        0x2,   0x2,    0x163,  0x156,  0x3,    0x2,    0x2,    0x2,    0x163,  0x158, 0x3,   0x2,   0x2,   0x2,   0x163,
        0x159, 0x3,    0x2,    0x2,    0x2,    0x163,  0x15a,  0x3,    0x2,    0x2,   0x2,   0x163, 0x15b, 0x3,   0x2,
        0x2,   0x2,    0x163,  0x15c,  0x3,    0x2,    0x2,    0x2,    0x163,  0x15d, 0x3,   0x2,   0x2,   0x2,   0x163,
        0x15e, 0x3,    0x2,    0x2,    0x2,    0x163,  0x15f,  0x3,    0x2,    0x2,   0x2,   0x164, 0x17c, 0x3,   0x2,
        0x2,   0x2,    0x165,  0x166,  0xc,    0x6,    0x2,    0x2,    0x166,  0x167, 0x5,   0x36,  0x1c,  0x2,   0x167,
        0x168, 0x5,    0x34,   0x1b,   0x7,    0x168,  0x17b,  0x3,    0x2,    0x2,   0x2,   0x169, 0x16a, 0xc,   0x5,
        0x2,   0x2,    0x16a,  0x16b,  0x5,    0x38,   0x1d,   0x2,    0x16b,  0x16c, 0x5,   0x34,  0x1b,  0x6,   0x16c,
        0x17b, 0x3,    0x2,    0x2,    0x2,    0x16d,  0x16e,  0xc,    0x4,    0x2,   0x2,   0x16e, 0x16f, 0x5,   0x3a,
        0x1e,  0x2,    0x16f,  0x170,  0x5,    0x34,   0x1b,   0x5,    0x170,  0x17b, 0x3,   0x2,   0x2,   0x2,   0x171,
        0x172, 0xc,    0x3,    0x2,    0x2,    0x172,  0x173,  0x5,    0x3c,   0x1f,  0x2,   0x173, 0x174, 0x5,   0x34,
        0x1b,  0x4,    0x174,  0x17b,  0x3,    0x2,    0x2,    0x2,    0x175,  0x176, 0xc,   0x9,   0x2,   0x2,   0x176,
        0x177, 0x7,    0x23,   0x2,    0x2,    0x177,  0x178,  0x5,    0x34,   0x1b,  0x2,   0x178, 0x179, 0x7,   0x24,
        0x2,   0x2,    0x179,  0x17b,  0x3,    0x2,    0x2,    0x2,    0x17a,  0x165, 0x3,   0x2,   0x2,   0x2,   0x17a,
        0x169, 0x3,    0x2,    0x2,    0x2,    0x17a,  0x16d,  0x3,    0x2,    0x2,   0x2,   0x17a, 0x171, 0x3,   0x2,
        0x2,   0x2,    0x17a,  0x175,  0x3,    0x2,    0x2,    0x2,    0x17b,  0x17e, 0x3,   0x2,   0x2,   0x2,   0x17c,
        0x17a, 0x3,    0x2,    0x2,    0x2,    0x17c,  0x17d,  0x3,    0x2,    0x2,   0x2,   0x17d, 0x35,  0x3,   0x2,
        0x2,   0x2,    0x17e,  0x17c,  0x3,    0x2,    0x2,    0x2,    0x17f,  0x183, 0x7,   0x25,  0x2,   0x2,   0x180,
        0x183, 0x7,    0x26,   0x2,    0x2,    0x181,  0x183,  0x7,    0x27,   0x2,   0x2,   0x182, 0x17f, 0x3,   0x2,
        0x2,   0x2,    0x182,  0x180,  0x3,    0x2,    0x2,    0x2,    0x182,  0x181, 0x3,   0x2,   0x2,   0x2,   0x183,
        0x37,  0x3,    0x2,    0x2,    0x2,    0x184,  0x187,  0x7,    0x28,   0x2,   0x2,   0x185, 0x187, 0x7,   0x29,
        0x2,   0x2,    0x186,  0x184,  0x3,    0x2,    0x2,    0x2,    0x186,  0x185, 0x3,   0x2,   0x2,   0x2,   0x187,
        0x39,  0x3,    0x2,    0x2,    0x2,    0x188,  0x18d,  0x7,    0x2a,   0x2,   0x2,   0x189, 0x18d, 0x7,   0x2b,
        0x2,   0x2,    0x18a,  0x18d,  0x7,    0x2c,   0x2,    0x2,    0x18b,  0x18d, 0x7,   0x2d,  0x2,   0x2,   0x18c,
        0x188, 0x3,    0x2,    0x2,    0x2,    0x18c,  0x189,  0x3,    0x2,    0x2,   0x2,   0x18c, 0x18a, 0x3,   0x2,
        0x2,   0x2,    0x18c,  0x18b,  0x3,    0x2,    0x2,    0x2,    0x18d,  0x3b,  0x3,   0x2,   0x2,   0x2,   0x18e,
        0x191, 0x7,    0x2e,   0x2,    0x2,    0x18f,  0x191,  0x7,    0x2f,   0x2,   0x2,   0x190, 0x18e, 0x3,   0x2,
        0x2,   0x2,    0x190,  0x18f,  0x3,    0x2,    0x2,    0x2,    0x191,  0x3d,  0x3,   0x2,   0x2,   0x2,   0x192,
        0x193, 0x5,    0x40,   0x21,   0x2,    0x193,  0x3f,   0x3,    0x2,    0x2,   0x2,   0x194, 0x195, 0x7,   0x50,
        0x2,   0x2,    0x195,  0x196,  0x7,    0x4,    0x2,    0x2,    0x196,  0x197, 0x5,   0x42,  0x22,  0x2,   0x197,
        0x198, 0x7,    0x5,    0x2,    0x2,    0x198,  0x41,   0x3,    0x2,    0x2,   0x2,   0x199, 0x19e, 0x5,   0x34,
        0x1b,  0x2,    0x19a,  0x19b,  0x7,    0x9,    0x2,    0x2,    0x19b,  0x19d, 0x5,   0x34,  0x1b,  0x2,   0x19c,
        0x19a, 0x3,    0x2,    0x2,    0x2,    0x19d,  0x1a0,  0x3,    0x2,    0x2,   0x2,   0x19e, 0x19c, 0x3,   0x2,
        0x2,   0x2,    0x19e,  0x19f,  0x3,    0x2,    0x2,    0x2,    0x19f,  0x1a2, 0x3,   0x2,   0x2,   0x2,   0x1a0,
        0x19e, 0x3,    0x2,    0x2,    0x2,    0x1a1,  0x199,  0x3,    0x2,    0x2,   0x2,   0x1a1, 0x1a2, 0x3,   0x2,
        0x2,   0x2,    0x1a2,  0x43,   0x3,    0x2,    0x2,    0x2,    0x1a3,  0x1a4, 0x7,   0x50,  0x2,   0x2,   0x1a4,
        0x45,  0x3,    0x2,    0x2,    0x2,    0x1a5,  0x1aa,  0x7,    0x30,   0x2,   0x2,   0x1a6, 0x1a7, 0x7,   0x23,
        0x2,   0x2,    0x1a7,  0x1a8,  0x5,    0x34,   0x1b,   0x2,    0x1a8,  0x1a9, 0x7,   0x24,  0x2,   0x2,   0x1a9,
        0x1ab, 0x3,    0x2,    0x2,    0x2,    0x1aa,  0x1a6,  0x3,    0x2,    0x2,   0x2,   0x1aa, 0x1ab, 0x3,   0x2,
        0x2,   0x2,    0x1ab,  0x1ac,  0x3,    0x2,    0x2,    0x2,    0x1ac,  0x1ad, 0x5,   0x48,  0x25,  0x2,   0x1ad,
        0x1ae, 0x5,    0x68,   0x35,   0x2,    0x1ae,  0x47,   0x3,    0x2,    0x2,   0x2,   0x1af, 0x1b2, 0x7,   0x31,
        0x2,   0x2,    0x1b0,  0x1b2,  0x7,    0x32,   0x2,    0x2,    0x1b1,  0x1af, 0x3,   0x2,   0x2,   0x2,   0x1b1,
        0x1b0, 0x3,    0x2,    0x2,    0x2,    0x1b2,  0x49,   0x3,    0x2,    0x2,   0x2,   0x1b3, 0x1b4, 0x7,   0x33,
        0x2,   0x2,    0x1b4,  0x1b5,  0x5,    0x34,   0x1b,   0x2,    0x1b5,  0x4b,  0x3,   0x2,   0x2,   0x2,   0x1b6,
        0x1b7, 0x7,    0x10,   0x2,    0x2,    0x1b7,  0x1bc,  0x5,    0x34,   0x1b,  0x2,   0x1b8, 0x1b9, 0x7,   0x10,
        0x2,   0x2,    0x1b9,  0x1ba,  0x7,    0x11,   0x2,    0x2,    0x1ba,  0x1bc, 0x5,   0x34,  0x1b,  0x2,   0x1bb,
        0x1b6, 0x3,    0x2,    0x2,    0x2,    0x1bb,  0x1b8,  0x3,    0x2,    0x2,   0x2,   0x1bc, 0x4d,  0x3,   0x2,
        0x2,   0x2,    0x1bd,  0x1be,  0x7,    0x34,   0x2,    0x2,    0x1be,  0x1bf, 0x5,   0x68,  0x35,  0x2,   0x1bf,
        0x4f,  0x3,    0x2,    0x2,    0x2,    0x1c0,  0x1c1,  0x7,    0x34,   0x2,   0x2,   0x1c1, 0x1c2, 0x7,   0x4,
        0x2,   0x2,    0x1c2,  0x1c3,  0x5,    0x34,   0x1b,   0x2,    0x1c3,  0x1c4, 0x7,   0x5,   0x2,   0x2,   0x1c4,
        0x51,  0x3,    0x2,    0x2,    0x2,    0x1c5,  0x1cd,  0x5,    0x54,   0x2b,  0x2,   0x1c6, 0x1cd, 0x5,   0x56,
        0x2c,  0x2,    0x1c7,  0x1cd,  0x5,    0x58,   0x2d,   0x2,    0x1c8,  0x1cd, 0x5,   0x60,  0x31,  0x2,   0x1c9,
        0x1cd, 0x5,    0x62,   0x32,   0x2,    0x1ca,  0x1cd,  0x5,    0x64,   0x33,  0x2,   0x1cb, 0x1cd, 0x5,   0x66,
        0x34,  0x2,    0x1cc,  0x1c5,  0x3,    0x2,    0x2,    0x2,    0x1cc,  0x1c6, 0x3,   0x2,   0x2,   0x2,   0x1cc,
        0x1c7, 0x3,    0x2,    0x2,    0x2,    0x1cc,  0x1c8,  0x3,    0x2,    0x2,   0x2,   0x1cc, 0x1c9, 0x3,   0x2,
        0x2,   0x2,    0x1cc,  0x1ca,  0x3,    0x2,    0x2,    0x2,    0x1cc,  0x1cb, 0x3,   0x2,   0x2,   0x2,   0x1cd,
        0x53,  0x3,    0x2,    0x2,    0x2,    0x1ce,  0x1d0,  0x7,    0x50,   0x2,   0x2,   0x1cf, 0x1ce, 0x3,   0x2,
        0x2,   0x2,    0x1cf,  0x1d0,  0x3,    0x2,    0x2,    0x2,    0x1d0,  0x1d1, 0x3,   0x2,   0x2,   0x2,   0x1d1,
        0x1d2, 0x7,    0x4b,   0x2,    0x2,    0x1d2,  0x55,   0x3,    0x2,    0x2,   0x2,   0x1d3, 0x1d4, 0x7,   0x4c,
        0x2,   0x2,    0x1d4,  0x57,   0x3,    0x2,    0x2,    0x2,    0x1d5,  0x1d9, 0x5,   0x5a,  0x2e,  0x2,   0x1d6,
        0x1d9, 0x5,    0x5c,   0x2f,   0x2,    0x1d7,  0x1d9,  0x5,    0x5e,   0x30,  0x2,   0x1d8, 0x1d5, 0x3,   0x2,
        0x2,   0x2,    0x1d8,  0x1d6,  0x3,    0x2,    0x2,    0x2,    0x1d8,  0x1d7, 0x3,   0x2,   0x2,   0x2,   0x1d9,
        0x59,  0x3,    0x2,    0x2,    0x2,    0x1da,  0x1db,  0x7,    0x4d,   0x2,   0x2,   0x1db, 0x1dc, 0x7,   0x3,
        0x2,   0x2,    0x1dc,  0x1dd,  0x7,    0x4d,   0x2,    0x2,    0x1dd,  0x5b,  0x3,   0x2,   0x2,   0x2,   0x1de,
        0x1df, 0x7,    0x42,   0x2,    0x2,    0x1df,  0x1e0,  0x7,    0x3,    0x2,   0x2,   0x1e0, 0x1e1, 0x7,   0x4d,
        0x2,   0x2,    0x1e1,  0x5d,   0x3,    0x2,    0x2,    0x2,    0x1e2,  0x1e3, 0x7,   0x43,  0x2,   0x2,   0x1e3,
        0x1e4, 0x7,    0x3,    0x2,    0x2,    0x1e4,  0x1ec,  0x7,    0x4d,   0x2,   0x2,   0x1e5, 0x1e6, 0x7,   0x44,
        0x2,   0x2,    0x1e6,  0x1e7,  0x7,    0x3,    0x2,    0x2,    0x1e7,  0x1ec, 0x7,   0x4d,  0x2,   0x2,   0x1e8,
        0x1e9, 0x7,    0x45,   0x2,    0x2,    0x1e9,  0x1ea,  0x7,    0x3,    0x2,   0x2,   0x1ea, 0x1ec, 0x7,   0x4d,
        0x2,   0x2,    0x1eb,  0x1e2,  0x3,    0x2,    0x2,    0x2,    0x1eb,  0x1e5, 0x3,   0x2,   0x2,   0x2,   0x1eb,
        0x1e8, 0x3,    0x2,    0x2,    0x2,    0x1ec,  0x5f,   0x3,    0x2,    0x2,   0x2,   0x1ed, 0x1ee, 0x9,   0x2,
        0x2,   0x2,    0x1ee,  0x61,   0x3,    0x2,    0x2,    0x2,    0x1ef,  0x1f2, 0x7,   0x35,  0x2,   0x2,   0x1f0,
        0x1f2, 0x7,    0x36,   0x2,    0x2,    0x1f1,  0x1ef,  0x3,    0x2,    0x2,   0x2,   0x1f1, 0x1f0, 0x3,   0x2,
        0x2,   0x2,    0x1f2,  0x63,   0x3,    0x2,    0x2,    0x2,    0x1f3,  0x1f6, 0x7,   0x4d,  0x2,   0x2,   0x1f4,
        0x1f5, 0x7,    0x3,    0x2,    0x2,    0x1f5,  0x1f7,  0x7,    0x37,   0x2,   0x2,   0x1f6, 0x1f4, 0x3,   0x2,
        0x2,   0x2,    0x1f6,  0x1f7,  0x3,    0x2,    0x2,    0x2,    0x1f7,  0x65,  0x3,   0x2,   0x2,   0x2,   0x1f8,
        0x1fb, 0x7,    0x42,   0x2,    0x2,    0x1f9,  0x1fa,  0x7,    0x3,    0x2,   0x2,   0x1fa, 0x1fc, 0x7,   0x38,
        0x2,   0x2,    0x1fb,  0x1f9,  0x3,    0x2,    0x2,    0x2,    0x1fb,  0x1fc, 0x3,   0x2,   0x2,   0x2,   0x1fc,
        0x67,  0x3,    0x2,    0x2,    0x2,    0x1fd,  0x206,  0x5,    0x6a,   0x36,  0x2,   0x1fe, 0x206, 0x5,   0x6c,
        0x37,  0x2,    0x1ff,  0x206,  0x5,    0x6e,   0x38,   0x2,    0x200,  0x201, 0x7,   0x25,  0x2,   0x2,   0x201,
        0x206, 0x5,    0x68,   0x35,   0x2,    0x202,  0x203,  0x7,    0x39,   0x2,   0x2,   0x203, 0x206, 0x5,   0x68,
        0x35,  0x2,    0x204,  0x206,  0x5,    0x78,   0x3d,   0x2,    0x205,  0x1fd, 0x3,   0x2,   0x2,   0x2,   0x205,
        0x1fe, 0x3,    0x2,    0x2,    0x2,    0x205,  0x1ff,  0x3,    0x2,    0x2,   0x2,   0x205, 0x200, 0x3,   0x2,
        0x2,   0x2,    0x205,  0x202,  0x3,    0x2,    0x2,    0x2,    0x205,  0x204, 0x3,   0x2,   0x2,   0x2,   0x206,
        0x69,  0x3,    0x2,    0x2,    0x2,    0x207,  0x208,  0x7,    0x41,   0x2,   0x2,   0x208, 0x6b,  0x3,   0x2,
        0x2,   0x2,    0x209,  0x20a,  0x7,    0x23,   0x2,    0x2,    0x20a,  0x20b, 0x5,   0x68,  0x35,  0x2,   0x20b,
        0x20c, 0x7,    0x51,   0x2,    0x2,    0x20c,  0x20d,  0x7,    0x4d,   0x2,   0x2,   0x20d, 0x20e, 0x7,   0x24,
        0x2,   0x2,    0x20e,  0x6d,   0x3,    0x2,    0x2,    0x2,    0x20f,  0x214, 0x5,   0x70,  0x39,  0x2,   0x210,
        0x214, 0x5,    0x72,   0x3a,   0x2,    0x211,  0x214,  0x5,    0x74,   0x3b,  0x2,   0x212, 0x214, 0x5,   0x76,
        0x3c,  0x2,    0x213,  0x20f,  0x3,    0x2,    0x2,    0x2,    0x213,  0x210, 0x3,   0x2,   0x2,   0x2,   0x213,
        0x211, 0x3,    0x2,    0x2,    0x2,    0x213,  0x212,  0x3,    0x2,    0x2,   0x2,   0x214, 0x6f,  0x3,   0x2,
        0x2,   0x2,    0x215,  0x216,  0x9,    0x3,    0x2,    0x2,    0x216,  0x71,  0x3,   0x2,   0x2,   0x2,   0x217,
        0x218, 0x9,    0x4,    0x2,    0x2,    0x218,  0x73,   0x3,    0x2,    0x2,   0x2,   0x219, 0x21a, 0x7,   0x3f,
        0x2,   0x2,    0x21a,  0x75,   0x3,    0x2,    0x2,    0x2,    0x21b,  0x21c, 0x7,   0x40,  0x2,   0x2,   0x21c,
        0x77,  0x3,    0x2,    0x2,    0x2,    0x21d,  0x21e,  0x7,    0x50,   0x2,   0x2,   0x21e, 0x79,  0x3,   0x2,
        0x2,   0x2,    0x2f,   0x7d,   0x7f,   0x86,   0x8e,   0x99,   0x9f,   0xab,  0xaf,  0xb6,  0xb9,  0xc1,  0xd1,
        0xd5,  0xdb,   0xeb,   0xf7,   0x10c,  0x11a,  0x11e,  0x125,  0x133,  0x141, 0x14b, 0x154, 0x163, 0x17a, 0x17c,
        0x182, 0x186,  0x18c,  0x190,  0x19e,  0x1a1,  0x1aa,  0x1b1,  0x1bb,  0x1cc, 0x1cf, 0x1d8, 0x1eb, 0x1f1, 0x1f6,
        0x1fb, 0x205,  0x213,
    };

    _serializedATN.insert(_serializedATN.end(),
                          serializedATNSegment0,
                          serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));

    atn::ATNDeserializer deserializer;
    _atn = deserializer.deserialize(_serializedATN);

    size_t count = _atn.getNumberOfDecisions();
    _decisionToDFA.reserve(count);
    for (size_t i = 0; i < count; i++) { _decisionToDFA.emplace_back(_atn.getDecisionState(i), i); }
}

anceParser::Initializer anceParser::_init;
