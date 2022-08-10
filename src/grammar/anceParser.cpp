
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
        setState(129);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~0x3fULL) == 0)
                && ((1ULL << _la)
                    & ((1ULL << anceParser::T__5) | (1ULL << anceParser::T__10) | (1ULL << anceParser::T__11)))
                       != 0))
        {
            setState(127);
            _errHandler->sync(this);
            switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx))
            {
                case 1:
                {
                    setState(124);
                    variableDeclaration();
                    break;
                }

                case 2:
                {
                    setState(125);
                    function();
                    break;
                }

                case 3:
                {
                    setState(126);
                    typeDefinition();
                    break;
                }

                default:
                    break;
            }
            setState(131);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(132);
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
        setState(134);
        accessModifier();
        setState(136);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::CONST)
        {
            setState(135);
            match(anceParser::CONST);
        }
        setState(138);
        match(anceParser::IDENTIFIER);
        setState(139);
        match(anceParser::T__0);
        setState(140);
        type();
        setState(144);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0)
             && ((1ULL << _la)
                 & ((1ULL << anceParser::T__14) | (1ULL << anceParser::T__15) | (1ULL << anceParser::T__16)))
                    != 0))
        {
            setState(141);
            assigner();
            setState(142);
            literalExpression();
        }
        setState(146);
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
        setState(177);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__10:
            case anceParser::T__11:
            {
                _localctx = _tracker.createInstance<anceParser::FunctionDefinitionContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(148);
                accessModifier();
                setState(149);
                match(anceParser::IDENTIFIER);
                setState(150);
                match(anceParser::T__1);
                setState(151);
                parameters();
                setState(152);
                match(anceParser::T__2);
                setState(155);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == anceParser::T__0)
                {
                    setState(153);
                    match(anceParser::T__0);
                    setState(154);
                    type();
                }
                setState(157);
                match(anceParser::T__3);
                setState(161);
                _errHandler->sync(this);
                _la = _input->LA(1);
                while (
                    (((_la & ~0x3fULL) == 0)
                     && ((1ULL << _la)
                         & ((1ULL << anceParser::T__1) | (1ULL << anceParser::T__3) | (1ULL << anceParser::T__12)
                            | (1ULL << anceParser::T__13) | (1ULL << anceParser::T__17) | (1ULL << anceParser::T__18)
                            | (1ULL << anceParser::T__19) | (1ULL << anceParser::T__20) | (1ULL << anceParser::T__23)
                            | (1ULL << anceParser::T__25) | (1ULL << anceParser::T__31) | (1ULL << anceParser::T__33)
                            | (1ULL << anceParser::T__36) | (1ULL << anceParser::T__47) | (1ULL << anceParser::T__50)
                            | (1ULL << anceParser::T__51) | (1ULL << anceParser::T__53) | (1ULL << anceParser::T__54)
                            | (1ULL << anceParser::T__55) | (1ULL << anceParser::T__56) | (1ULL << anceParser::T__57)
                            | (1ULL << anceParser::T__58) | (1ULL << anceParser::T__59) | (1ULL << anceParser::T__60)
                            | (1ULL << anceParser::T__61) | (1ULL << anceParser::T__62)))
                            != 0)
                    || ((((_la - 64) & ~0x3fULL) == 0)
                        && ((1ULL << (_la - 64))
                            & ((1ULL << (anceParser::T__63 - 64)) | (1ULL << (anceParser::T__64 - 64))
                               | (1ULL << (anceParser::T__65 - 64)) | (1ULL << (anceParser::NATIVE_INTEGER_TYPE - 64))
                               | (1ULL << (anceParser::SIGNED_INTEGER - 64)) | (1ULL << (anceParser::HEX_INTEGER - 64))
                               | (1ULL << (anceParser::BIN_INTEGER - 64)) | (1ULL << (anceParser::OCT_INTEGER - 64))
                               | (1ULL << (anceParser::HALF - 64)) | (1ULL << (anceParser::SINGLE - 64))
                               | (1ULL << (anceParser::DOUBLE - 64)) | (1ULL << (anceParser::QUAD - 64))
                               | (1ULL << (anceParser::STRING - 64)) | (1ULL << (anceParser::BYTE - 64))
                               | (1ULL << (anceParser::INTEGER - 64)) | (1ULL << (anceParser::IDENTIFIER - 64))))
                               != 0))
                {
                    setState(158);
                    code();
                    setState(163);
                    _errHandler->sync(this);
                    _la = _input->LA(1);
                }
                setState(164);
                match(anceParser::T__4);
                break;
            }

            case anceParser::T__5:
            {
                _localctx = _tracker.createInstance<anceParser::ExternFunctionDeclarationContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(166);
                match(anceParser::T__5);
                setState(167);
                match(anceParser::IDENTIFIER);
                setState(168);
                match(anceParser::T__1);
                setState(169);
                parameters();
                setState(170);
                match(anceParser::T__2);
                setState(173);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == anceParser::T__0)
                {
                    setState(171);
                    match(anceParser::T__0);
                    setState(172);
                    type();
                }
                setState(175);
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
        setState(187);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::IDENTIFIER)
        {
            setState(179);
            parameter();
            setState(184);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == anceParser::T__6)
            {
                setState(180);
                match(anceParser::T__6);
                setState(181);
                parameter();
                setState(186);
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
        setState(189);
        match(anceParser::IDENTIFIER);
        setState(190);
        match(anceParser::T__0);
        setState(191);
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

anceParser::DefineAliasContext* anceParser::TypeDefinitionContext::defineAlias()
{
    return getRuleContext<anceParser::DefineAliasContext>(0);
}

anceParser::StructDefinitionContext* anceParser::TypeDefinitionContext::structDefinition()
{
    return getRuleContext<anceParser::StructDefinitionContext>(0);
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
        setState(195);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx))
        {
            case 1:
            {
                enterOuterAlt(_localctx, 1);
                setState(193);
                defineAlias();
                break;
            }

            case 2:
            {
                enterOuterAlt(_localctx, 2);
                setState(194);
                structDefinition();
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

//----------------- DefineAliasContext ------------------------------------------------------------------

anceParser::DefineAliasContext::DefineAliasContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::AccessModifierContext* anceParser::DefineAliasContext::accessModifier()
{
    return getRuleContext<anceParser::AccessModifierContext>(0);
}

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
    enterRule(_localctx, 12, anceParser::RuleDefineAlias);

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
        setState(197);
        accessModifier();
        setState(198);
        match(anceParser::T__7);
        setState(199);
        match(anceParser::IDENTIFIER);
        setState(200);
        match(anceParser::T__8);
        setState(201);
        type();
        setState(202);
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

//----------------- StructDefinitionContext ------------------------------------------------------------------

anceParser::StructDefinitionContext::StructDefinitionContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::AccessModifierContext* anceParser::StructDefinitionContext::accessModifier()
{
    return getRuleContext<anceParser::AccessModifierContext>(0);
}

tree::TerminalNode* anceParser::StructDefinitionContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

std::vector<anceParser::MemberContext*> anceParser::StructDefinitionContext::member()
{
    return getRuleContexts<anceParser::MemberContext>();
}

anceParser::MemberContext* anceParser::StructDefinitionContext::member(size_t i)
{
    return getRuleContext<anceParser::MemberContext>(i);
}

size_t anceParser::StructDefinitionContext::getRuleIndex() const
{
    return anceParser::RuleStructDefinition;
}

antlrcpp::Any anceParser::StructDefinitionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitStructDefinition(this);
    else return visitor->visitChildren(this);
}

anceParser::StructDefinitionContext* anceParser::structDefinition()
{
    StructDefinitionContext* _localctx = _tracker.createInstance<StructDefinitionContext>(_ctx, getState());
    enterRule(_localctx, 14, anceParser::RuleStructDefinition);
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
        setState(204);
        accessModifier();
        setState(205);
        match(anceParser::T__9);
        setState(206);
        match(anceParser::IDENTIFIER);
        setState(207);
        match(anceParser::T__3);
        setState(211);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == anceParser::T__10

               || _la == anceParser::T__11)
        {
            setState(208);
            member();
            setState(213);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(214);
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

//----------------- MemberContext ------------------------------------------------------------------

anceParser::MemberContext::MemberContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::AccessModifierContext* anceParser::MemberContext::accessModifier()
{
    return getRuleContext<anceParser::AccessModifierContext>(0);
}

tree::TerminalNode* anceParser::MemberContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::TypeContext* anceParser::MemberContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::MemberContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

anceParser::AssignerContext* anceParser::MemberContext::assigner()
{
    return getRuleContext<anceParser::AssignerContext>(0);
}

anceParser::LiteralExpressionContext* anceParser::MemberContext::literalExpression()
{
    return getRuleContext<anceParser::LiteralExpressionContext>(0);
}

size_t anceParser::MemberContext::getRuleIndex() const
{
    return anceParser::RuleMember;
}

antlrcpp::Any anceParser::MemberContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitMember(this);
    else return visitor->visitChildren(this);
}

anceParser::MemberContext* anceParser::member()
{
    MemberContext* _localctx = _tracker.createInstance<MemberContext>(_ctx, getState());
    enterRule(_localctx, 16, anceParser::RuleMember);
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
        setState(216);
        accessModifier();
        setState(217);
        match(anceParser::IDENTIFIER);
        setState(218);
        match(anceParser::T__0);
        setState(219);
        type();
        setState(223);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0)
             && ((1ULL << _la)
                 & ((1ULL << anceParser::T__14) | (1ULL << anceParser::T__15) | (1ULL << anceParser::T__16)))
                    != 0))
        {
            setState(220);
            assigner();
            setState(221);
            literalExpression();
        }
        setState(225);
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
    enterRule(_localctx, 18, anceParser::RuleAccessModifier);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(229);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__10:
            {
                _localctx = _tracker.createInstance<anceParser::PublicContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(227);
                match(anceParser::T__10);
                break;
            }

            case anceParser::T__11:
            {
                _localctx = _tracker.createInstance<anceParser::PrivateContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(228);
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
    enterRule(_localctx, 20, anceParser::RuleCode);

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
        switch (_input->LA(1))
        {
            case anceParser::T__1:
            case anceParser::T__12:
            case anceParser::T__13:
            case anceParser::T__17:
            case anceParser::T__18:
            case anceParser::T__19:
            case anceParser::T__20:
            case anceParser::T__23:
            case anceParser::T__25:
            case anceParser::T__31:
            case anceParser::T__33:
            case anceParser::T__36:
            case anceParser::T__47:
            case anceParser::T__50:
            case anceParser::T__51:
            case anceParser::T__53:
            case anceParser::T__54:
            case anceParser::T__55:
            case anceParser::T__56:
            case anceParser::T__57:
            case anceParser::T__58:
            case anceParser::T__59:
            case anceParser::T__60:
            case anceParser::T__61:
            case anceParser::T__62:
            case anceParser::T__63:
            case anceParser::T__64:
            case anceParser::T__65:
            case anceParser::NATIVE_INTEGER_TYPE:
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
                setState(231);
                statement();
                break;
            }

            case anceParser::T__3:
            {
                enterOuterAlt(_localctx, 2);
                setState(232);
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
    enterRule(_localctx, 22, anceParser::RuleBlock);
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
        setState(235);
        match(anceParser::T__3);
        setState(239);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~0x3fULL) == 0)
                && ((1ULL << _la)
                    & ((1ULL << anceParser::T__1) | (1ULL << anceParser::T__3) | (1ULL << anceParser::T__12)
                       | (1ULL << anceParser::T__13) | (1ULL << anceParser::T__17) | (1ULL << anceParser::T__18)
                       | (1ULL << anceParser::T__19) | (1ULL << anceParser::T__20) | (1ULL << anceParser::T__23)
                       | (1ULL << anceParser::T__25) | (1ULL << anceParser::T__31) | (1ULL << anceParser::T__33)
                       | (1ULL << anceParser::T__36) | (1ULL << anceParser::T__47) | (1ULL << anceParser::T__50)
                       | (1ULL << anceParser::T__51) | (1ULL << anceParser::T__53) | (1ULL << anceParser::T__54)
                       | (1ULL << anceParser::T__55) | (1ULL << anceParser::T__56) | (1ULL << anceParser::T__57)
                       | (1ULL << anceParser::T__58) | (1ULL << anceParser::T__59) | (1ULL << anceParser::T__60)
                       | (1ULL << anceParser::T__61) | (1ULL << anceParser::T__62)))
                       != 0)
               || ((((_la - 64) & ~0x3fULL) == 0)
                   && ((1ULL << (_la - 64))
                       & ((1ULL << (anceParser::T__63 - 64)) | (1ULL << (anceParser::T__64 - 64))
                          | (1ULL << (anceParser::T__65 - 64)) | (1ULL << (anceParser::NATIVE_INTEGER_TYPE - 64))
                          | (1ULL << (anceParser::SIGNED_INTEGER - 64)) | (1ULL << (anceParser::HEX_INTEGER - 64))
                          | (1ULL << (anceParser::BIN_INTEGER - 64)) | (1ULL << (anceParser::OCT_INTEGER - 64))
                          | (1ULL << (anceParser::HALF - 64)) | (1ULL << (anceParser::SINGLE - 64))
                          | (1ULL << (anceParser::DOUBLE - 64)) | (1ULL << (anceParser::QUAD - 64))
                          | (1ULL << (anceParser::STRING - 64)) | (1ULL << (anceParser::BYTE - 64))
                          | (1ULL << (anceParser::INTEGER - 64)) | (1ULL << (anceParser::IDENTIFIER - 64))))
                          != 0))
        {
            setState(236);
            code();
            setState(241);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(242);
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
    enterRule(_localctx, 24, anceParser::RuleStatement);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(255);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx))
        {
            case 1:
            {
                enterOuterAlt(_localctx, 1);
                setState(244);
                expressionStatement();
                break;
            }

            case 2:
            {
                enterOuterAlt(_localctx, 2);
                setState(245);
                localVariableDefinition();
                break;
            }

            case 3:
            {
                enterOuterAlt(_localctx, 3);
                setState(246);
                localReferenceDefinition();
                break;
            }

            case 4:
            {
                enterOuterAlt(_localctx, 4);
                setState(247);
                dropStatement();
                break;
            }

            case 5:
            {
                enterOuterAlt(_localctx, 5);
                setState(248);
                assignment();
                break;
            }

            case 6:
            {
                enterOuterAlt(_localctx, 6);
                setState(249);
                deleteStatement();
                break;
            }

            case 7:
            {
                enterOuterAlt(_localctx, 7);
                setState(250);
                returnStatement();
                break;
            }

            case 8:
            {
                enterOuterAlt(_localctx, 8);
                setState(251);
                assertStatement();
                break;
            }

            case 9:
            {
                enterOuterAlt(_localctx, 9);
                setState(252);
                ifStatement();
                break;
            }

            case 10:
            {
                enterOuterAlt(_localctx, 10);
                setState(253);
                whileStatement();
                break;
            }

            case 11:
            {
                enterOuterAlt(_localctx, 11);
                setState(254);
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
    enterRule(_localctx, 26, anceParser::RuleExpressionStatement);

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
        setState(257);
        independentExpression();
        setState(258);
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
    enterRule(_localctx, 28, anceParser::RuleLocalVariableDefinition);
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
        setState(260);
        match(anceParser::T__12);
        setState(261);
        match(anceParser::IDENTIFIER);
        setState(262);
        match(anceParser::T__0);
        setState(263);
        type();
        setState(267);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0)
             && ((1ULL << _la)
                 & ((1ULL << anceParser::T__14) | (1ULL << anceParser::T__15) | (1ULL << anceParser::T__16)))
                    != 0))
        {
            setState(264);
            assigner();
            setState(265);
            expression(0);
        }
        setState(269);
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

tree::TerminalNode* anceParser::LocalReferenceDefinitionContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::TypeContext* anceParser::LocalReferenceDefinitionContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::BindRefContext* anceParser::LocalReferenceDefinitionContext::bindRef()
{
    return getRuleContext<anceParser::BindRefContext>(0);
}

tree::TerminalNode* anceParser::LocalReferenceDefinitionContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

size_t anceParser::LocalReferenceDefinitionContext::getRuleIndex() const
{
    return anceParser::RuleLocalReferenceDefinition;
}

antlrcpp::Any anceParser::LocalReferenceDefinitionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitLocalReferenceDefinition(this);
    else return visitor->visitChildren(this);
}

anceParser::LocalReferenceDefinitionContext* anceParser::localReferenceDefinition()
{
    LocalReferenceDefinitionContext* _localctx =
        _tracker.createInstance<LocalReferenceDefinitionContext>(_ctx, getState());
    enterRule(_localctx, 30, anceParser::RuleLocalReferenceDefinition);

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
        setState(271);
        match(anceParser::T__12);
        setState(272);
        match(anceParser::IDENTIFIER);
        setState(273);
        match(anceParser::T__0);
        setState(274);
        type();
        setState(275);
        bindRef();
        setState(276);
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
    enterRule(_localctx, 32, anceParser::RuleDropStatement);

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
        setState(278);
        match(anceParser::T__13);
        setState(279);
        match(anceParser::IDENTIFIER);
        setState(280);
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
    enterRule(_localctx, 34, anceParser::RuleAssignment);

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
        antlrcpp::downCast<AssignmentContext*>(_localctx)->assignable = expression(0);
        setState(283);
        assigner();
        setState(284);
        antlrcpp::downCast<AssignmentContext*>(_localctx)->assigned = expression(0);
        setState(285);
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
    enterRule(_localctx, 36, anceParser::RuleAssigner);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(290);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__14:
            {
                _localctx = _tracker.createInstance<anceParser::CopyAssignmentContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(287);
                match(anceParser::T__14);
                break;
            }

            case anceParser::T__15:
            {
                _localctx = _tracker.createInstance<anceParser::MoveAssignmentContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(288);
                match(anceParser::T__15);
                break;
            }

            case anceParser::T__16:
            {
                _localctx = _tracker.createInstance<anceParser::FinalCopyAssignmentContext>(_localctx);
                enterOuterAlt(_localctx, 3);
                setState(289);
                match(anceParser::T__16);
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
    enterRule(_localctx, 38, anceParser::RuleDeleteStatement);
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
        setState(292);
        match(anceParser::T__17);
        setState(294);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::BUFFER)
        {
            setState(293);
            match(anceParser::BUFFER);
        }
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
    enterRule(_localctx, 40, anceParser::RuleReturnStatement);
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
        setState(299);
        match(anceParser::T__18);
        setState(301);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0)
             && ((1ULL << _la)
                 & ((1ULL << anceParser::T__1) | (1ULL << anceParser::T__20) | (1ULL << anceParser::T__25)
                    | (1ULL << anceParser::T__31) | (1ULL << anceParser::T__33) | (1ULL << anceParser::T__36)
                    | (1ULL << anceParser::T__47) | (1ULL << anceParser::T__50) | (1ULL << anceParser::T__51)
                    | (1ULL << anceParser::T__53) | (1ULL << anceParser::T__54) | (1ULL << anceParser::T__55)
                    | (1ULL << anceParser::T__56) | (1ULL << anceParser::T__57) | (1ULL << anceParser::T__58)
                    | (1ULL << anceParser::T__59) | (1ULL << anceParser::T__60) | (1ULL << anceParser::T__61)
                    | (1ULL << anceParser::T__62)))
                    != 0)
            || ((((_la - 64) & ~0x3fULL) == 0)
                && ((1ULL << (_la - 64))
                    & ((1ULL << (anceParser::T__63 - 64)) | (1ULL << (anceParser::T__64 - 64))
                       | (1ULL << (anceParser::T__65 - 64)) | (1ULL << (anceParser::NATIVE_INTEGER_TYPE - 64))
                       | (1ULL << (anceParser::SIGNED_INTEGER - 64)) | (1ULL << (anceParser::HEX_INTEGER - 64))
                       | (1ULL << (anceParser::BIN_INTEGER - 64)) | (1ULL << (anceParser::OCT_INTEGER - 64))
                       | (1ULL << (anceParser::HALF - 64)) | (1ULL << (anceParser::SINGLE - 64))
                       | (1ULL << (anceParser::DOUBLE - 64)) | (1ULL << (anceParser::QUAD - 64))
                       | (1ULL << (anceParser::STRING - 64)) | (1ULL << (anceParser::BYTE - 64))
                       | (1ULL << (anceParser::INTEGER - 64)) | (1ULL << (anceParser::IDENTIFIER - 64))))
                       != 0))
        {
            setState(300);
            expression(0);
        }
        setState(303);
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
    enterRule(_localctx, 42, anceParser::RuleAssertStatement);

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
        setState(305);
        match(anceParser::T__19);
        setState(306);
        expression(0);
        setState(307);
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
    enterRule(_localctx, 44, anceParser::RuleIfStatement);

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
        setState(309);
        match(anceParser::T__20);
        setState(310);
        expression(0);
        setState(311);
        match(anceParser::T__21);
        setState(312);
        antlrcpp::downCast<IfStatementContext*>(_localctx)->ifBlock = code();
        setState(315);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx))
        {
            case 1:
            {
                setState(313);
                match(anceParser::T__22);
                setState(314);
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
    enterRule(_localctx, 46, anceParser::RuleWhileStatement);

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
        setState(317);
        match(anceParser::T__23);
        setState(318);
        expression(0);
        setState(319);
        match(anceParser::T__24);
        setState(320);
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
    enterRule(_localctx, 48, anceParser::RuleMatchStatement);
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
        setState(322);
        match(anceParser::T__25);
        setState(323);
        expression(0);
        setState(324);
        match(anceParser::T__26);
        setState(325);
        match(anceParser::T__3);
        setState(329);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (((((_la - 30) & ~0x3fULL) == 0)
                && ((1ULL << (_la - 30))
                    & ((1ULL << (anceParser::T__29 - 30)) | (1ULL << (anceParser::T__54 - 30))
                       | (1ULL << (anceParser::T__55 - 30)) | (1ULL << (anceParser::SIGNED_INTEGER - 30))
                       | (1ULL << (anceParser::HEX_INTEGER - 30)) | (1ULL << (anceParser::BIN_INTEGER - 30))
                       | (1ULL << (anceParser::OCT_INTEGER - 30)) | (1ULL << (anceParser::HALF - 30))
                       | (1ULL << (anceParser::SINGLE - 30)) | (1ULL << (anceParser::DOUBLE - 30))
                       | (1ULL << (anceParser::QUAD - 30)) | (1ULL << (anceParser::STRING - 30))
                       | (1ULL << (anceParser::BYTE - 30)) | (1ULL << (anceParser::INTEGER - 30))
                       | (1ULL << (anceParser::IDENTIFIER - 30))))
                       != 0))
        {
            setState(326);
            matchCase();
            setState(331);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(332);
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
    enterRule(_localctx, 50, anceParser::RuleMatchCase);
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
        setState(348);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__54:
            case anceParser::T__55:
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
                setState(334);
                literalExpression();
                setState(339);
                _errHandler->sync(this);
                _la = _input->LA(1);
                while (_la == anceParser::T__27)
                {
                    setState(335);
                    match(anceParser::T__27);
                    setState(336);
                    literalExpression();
                    setState(341);
                    _errHandler->sync(this);
                    _la = _input->LA(1);
                }
                setState(342);
                match(anceParser::T__28);
                setState(343);
                code();
                break;
            }

            case anceParser::T__29:
            {
                _localctx = _tracker.createInstance<anceParser::DefaultCaseContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(345);
                match(anceParser::T__29);
                setState(346);
                match(anceParser::T__28);
                setState(347);
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

//----------------- IfExpressionContext ------------------------------------------------------------------

std::vector<anceParser::ExpressionContext*> anceParser::IfExpressionContext::expression()
{
    return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::IfExpressionContext::expression(size_t i)
{
    return getRuleContext<anceParser::ExpressionContext>(i);
}

anceParser::IfExpressionContext::IfExpressionContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::IfExpressionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitIfExpression(this);
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
//----------------- NotOperationContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::NotOperationContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::NotOperationContext::NotOperationContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::NotOperationContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitNotOperation(this);
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
//----------------- LogicalOrContext ------------------------------------------------------------------

std::vector<anceParser::ExpressionContext*> anceParser::LogicalOrContext::expression()
{
    return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::LogicalOrContext::expression(size_t i)
{
    return getRuleContext<anceParser::ExpressionContext>(i);
}

anceParser::LogicalOrContext::LogicalOrContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::LogicalOrContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitLogicalOr(this);
    else return visitor->visitChildren(this);
}
//----------------- MatchContext ------------------------------------------------------------------

anceParser::MatchExpressionContext* anceParser::MatchContext::matchExpression()
{
    return getRuleContext<anceParser::MatchExpressionContext>(0);
}

anceParser::MatchContext::MatchContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::MatchContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitMatch(this);
    else return visitor->visitChildren(this);
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
//----------------- MemberAccessContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::MemberAccessContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::ExpressionContext* anceParser::MemberAccessContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::MemberAccessContext::MemberAccessContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::MemberAccessContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitMemberAccess(this);
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
//----------------- LogicalAndContext ------------------------------------------------------------------

std::vector<anceParser::ExpressionContext*> anceParser::LogicalAndContext::expression()
{
    return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::LogicalAndContext::expression(size_t i)
{
    return getRuleContext<anceParser::ExpressionContext>(i);
}

anceParser::LogicalAndContext::LogicalAndContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::LogicalAndContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitLogicalAnd(this);
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
//----------------- IndirectionContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::IndirectionContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::IndirectionContext::IndirectionContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::IndirectionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitIndirection(this);
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
    size_t startState = 52;
    enterRecursionRule(_localctx, 52, anceParser::RuleExpression, precedence);

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
        setState(373);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx))
        {
            case 1:
            {
                _localctx       = _tracker.createInstance<VariableContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;

                setState(351);
                variableAccess();
                break;
            }

            case 2:
            {
                _localctx       = _tracker.createInstance<AllocContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(352);
                allocation();
                break;
            }

            case 3:
            {
                _localctx       = _tracker.createInstance<LiteralContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(353);
                literalExpression();
                break;
            }

            case 4:
            {
                _localctx       = _tracker.createInstance<AdressOfContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(354);
                addressof();
                break;
            }

            case 5:
            {
                _localctx       = _tracker.createInstance<RefContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(355);
                bindRef();
                break;
            }

            case 6:
            {
                _localctx       = _tracker.createInstance<SizeOfContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(356);
                sizeofType();
                break;
            }

            case 7:
            {
                _localctx       = _tracker.createInstance<SizeOfContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(357);
                sizeofExpression();
                break;
            }

            case 8:
            {
                _localctx       = _tracker.createInstance<IndependentContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(358);
                independentExpression();
                break;
            }

            case 9:
            {
                _localctx       = _tracker.createInstance<ParenthesisContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(359);
                match(anceParser::T__1);
                setState(360);
                expression(0);
                setState(361);
                match(anceParser::T__2);
                break;
            }

            case 10:
            {
                _localctx       = _tracker.createInstance<NotOperationContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(363);
                match(anceParser::T__33);
                setState(364);
                expression(9);
                break;
            }

            case 11:
            {
                _localctx       = _tracker.createInstance<IfExpressionContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(365);
                match(anceParser::T__20);
                setState(366);
                antlrcpp::downCast<IfExpressionContext*>(_localctx)->condition = expression(0);
                setState(367);
                match(anceParser::T__21);
                setState(368);
                antlrcpp::downCast<IfExpressionContext*>(_localctx)->thenBlock = expression(0);
                setState(369);
                match(anceParser::T__22);
                setState(370);
                antlrcpp::downCast<IfExpressionContext*>(_localctx)->elseBlock = expression(2);
                break;
            }

            case 12:
            {
                _localctx       = _tracker.createInstance<MatchContext>(_localctx);
                _ctx            = _localctx;
                previousContext = _localctx;
                setState(372);
                matchExpression();
                break;
            }

            default:
                break;
        }
        _ctx->stop = _input->LT(-1);
        setState(408);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER)
        {
            if (alt == 1)
            {
                if (!_parseListeners.empty()) triggerExitRuleEvent();
                previousContext = _localctx;
                setState(406);
                _errHandler->sync(this);
                switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx))
                {
                    case 1:
                    {
                        auto newContext = _tracker.createInstance<BinaryOperationContext>(
                            _tracker.createInstance<ExpressionContext>(parentContext, parentState));
                        _localctx        = newContext;
                        newContext->left = previousContext;
                        pushNewRecursionContext(newContext, startState, RuleExpression);
                        setState(375);

                        if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
                        setState(376);
                        binaryOperatorMultiplicative();
                        setState(377);
                        antlrcpp::downCast<BinaryOperationContext*>(_localctx)->right = expression(9);
                        break;
                    }

                    case 2:
                    {
                        auto newContext = _tracker.createInstance<BinaryOperationContext>(
                            _tracker.createInstance<ExpressionContext>(parentContext, parentState));
                        _localctx        = newContext;
                        newContext->left = previousContext;
                        pushNewRecursionContext(newContext, startState, RuleExpression);
                        setState(379);

                        if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
                        setState(380);
                        binaryOperatorAdditive();
                        setState(381);
                        antlrcpp::downCast<BinaryOperationContext*>(_localctx)->right = expression(8);
                        break;
                    }

                    case 3:
                    {
                        auto newContext = _tracker.createInstance<BinaryOperationContext>(
                            _tracker.createInstance<ExpressionContext>(parentContext, parentState));
                        _localctx        = newContext;
                        newContext->left = previousContext;
                        pushNewRecursionContext(newContext, startState, RuleExpression);
                        setState(383);

                        if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
                        setState(384);
                        binaryOperatorRelational();
                        setState(385);
                        antlrcpp::downCast<BinaryOperationContext*>(_localctx)->right = expression(7);
                        break;
                    }

                    case 4:
                    {
                        auto newContext = _tracker.createInstance<BinaryOperationContext>(
                            _tracker.createInstance<ExpressionContext>(parentContext, parentState));
                        _localctx        = newContext;
                        newContext->left = previousContext;
                        pushNewRecursionContext(newContext, startState, RuleExpression);
                        setState(387);

                        if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
                        setState(388);
                        binaryOperatorEquality();
                        setState(389);
                        antlrcpp::downCast<BinaryOperationContext*>(_localctx)->right = expression(6);
                        break;
                    }

                    case 5:
                    {
                        auto newContext = _tracker.createInstance<LogicalAndContext>(
                            _tracker.createInstance<ExpressionContext>(parentContext, parentState));
                        _localctx        = newContext;
                        newContext->left = previousContext;
                        pushNewRecursionContext(newContext, startState, RuleExpression);
                        setState(391);

                        if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
                        setState(392);
                        match(anceParser::T__34);
                        setState(393);
                        antlrcpp::downCast<LogicalAndContext*>(_localctx)->right = expression(5);
                        break;
                    }

                    case 6:
                    {
                        auto newContext = _tracker.createInstance<LogicalOrContext>(
                            _tracker.createInstance<ExpressionContext>(parentContext, parentState));
                        _localctx        = newContext;
                        newContext->left = previousContext;
                        pushNewRecursionContext(newContext, startState, RuleExpression);
                        setState(394);

                        if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
                        setState(395);
                        match(anceParser::T__35);
                        setState(396);
                        antlrcpp::downCast<LogicalOrContext*>(_localctx)->right = expression(4);
                        break;
                    }

                    case 7:
                    {
                        auto newContext = _tracker.createInstance<IndirectionContext>(
                            _tracker.createInstance<ExpressionContext>(parentContext, parentState));
                        _localctx         = newContext;
                        newContext->value = previousContext;
                        pushNewRecursionContext(newContext, startState, RuleExpression);
                        setState(397);

                        if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
                        setState(398);
                        match(anceParser::T__30);
                        break;
                    }

                    case 8:
                    {
                        auto newContext = _tracker.createInstance<SubscriptContext>(
                            _tracker.createInstance<ExpressionContext>(parentContext, parentState));
                        _localctx           = newContext;
                        newContext->indexed = previousContext;
                        pushNewRecursionContext(newContext, startState, RuleExpression);
                        setState(399);

                        if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
                        setState(400);
                        match(anceParser::T__31);
                        setState(401);
                        antlrcpp::downCast<SubscriptContext*>(_localctx)->index = expression(0);
                        setState(402);
                        match(anceParser::T__32);
                        break;
                    }

                    case 9:
                    {
                        auto newContext = _tracker.createInstance<MemberAccessContext>(
                            _tracker.createInstance<ExpressionContext>(parentContext, parentState));
                        _localctx            = newContext;
                        newContext->accessed = previousContext;
                        pushNewRecursionContext(newContext, startState, RuleExpression);
                        setState(404);

                        if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
                        setState(405);
                        match(anceParser::IDENTIFIER);
                        break;
                    }

                    default:
                        break;
                }
            }
            setState(410);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
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
    enterRule(_localctx, 54, anceParser::RuleBinaryOperatorMultiplicative);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(414);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__36:
            {
                _localctx = _tracker.createInstance<anceParser::MultiplicationContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(411);
                match(anceParser::T__36);
                break;
            }

            case anceParser::T__37:
            {
                _localctx = _tracker.createInstance<anceParser::DivisionContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(412);
                match(anceParser::T__37);
                break;
            }

            case anceParser::T__38:
            {
                _localctx = _tracker.createInstance<anceParser::RemainderContext>(_localctx);
                enterOuterAlt(_localctx, 3);
                setState(413);
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
    enterRule(_localctx, 56, anceParser::RuleBinaryOperatorAdditive);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(418);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__39:
            {
                _localctx = _tracker.createInstance<anceParser::AdditionContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(416);
                match(anceParser::T__39);
                break;
            }

            case anceParser::T__40:
            {
                _localctx = _tracker.createInstance<anceParser::SubtractionContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(417);
                match(anceParser::T__40);
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
    enterRule(_localctx, 58, anceParser::RuleBinaryOperatorRelational);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(424);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__41:
            {
                _localctx = _tracker.createInstance<anceParser::LessThanContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(420);
                match(anceParser::T__41);
                break;
            }

            case anceParser::T__42:
            {
                _localctx = _tracker.createInstance<anceParser::LessThanOrEqualContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(421);
                match(anceParser::T__42);
                break;
            }

            case anceParser::T__43:
            {
                _localctx = _tracker.createInstance<anceParser::GreaterThanContext>(_localctx);
                enterOuterAlt(_localctx, 3);
                setState(422);
                match(anceParser::T__43);
                break;
            }

            case anceParser::T__44:
            {
                _localctx = _tracker.createInstance<anceParser::GreaterThanOrEqualContext>(_localctx);
                enterOuterAlt(_localctx, 4);
                setState(423);
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
    enterRule(_localctx, 60, anceParser::RuleBinaryOperatorEquality);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(428);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__45:
            {
                _localctx = _tracker.createInstance<anceParser::EqualContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(426);
                match(anceParser::T__45);
                break;
            }

            case anceParser::T__46:
            {
                _localctx = _tracker.createInstance<anceParser::NotEqualContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(427);
                match(anceParser::T__46);
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
    enterRule(_localctx, 62, anceParser::RuleIndependentExpression);

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
        setState(430);
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

anceParser::TypeContext* anceParser::FunctionCallContext::type()
{
    return getRuleContext<anceParser::TypeContext>(0);
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
    enterRule(_localctx, 64, anceParser::RuleFunctionCall);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(442);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx))
        {
            case 1:
            {
                enterOuterAlt(_localctx, 1);
                setState(432);
                match(anceParser::IDENTIFIER);
                setState(433);
                match(anceParser::T__1);
                setState(434);
                arguments();
                setState(435);
                match(anceParser::T__2);
                break;
            }

            case 2:
            {
                enterOuterAlt(_localctx, 2);
                setState(437);
                type();
                setState(438);
                match(anceParser::T__1);
                setState(439);
                arguments();
                setState(440);
                match(anceParser::T__2);
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
    enterRule(_localctx, 66, anceParser::RuleArguments);
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
        setState(452);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0)
             && ((1ULL << _la)
                 & ((1ULL << anceParser::T__1) | (1ULL << anceParser::T__20) | (1ULL << anceParser::T__25)
                    | (1ULL << anceParser::T__31) | (1ULL << anceParser::T__33) | (1ULL << anceParser::T__36)
                    | (1ULL << anceParser::T__47) | (1ULL << anceParser::T__50) | (1ULL << anceParser::T__51)
                    | (1ULL << anceParser::T__53) | (1ULL << anceParser::T__54) | (1ULL << anceParser::T__55)
                    | (1ULL << anceParser::T__56) | (1ULL << anceParser::T__57) | (1ULL << anceParser::T__58)
                    | (1ULL << anceParser::T__59) | (1ULL << anceParser::T__60) | (1ULL << anceParser::T__61)
                    | (1ULL << anceParser::T__62)))
                    != 0)
            || ((((_la - 64) & ~0x3fULL) == 0)
                && ((1ULL << (_la - 64))
                    & ((1ULL << (anceParser::T__63 - 64)) | (1ULL << (anceParser::T__64 - 64))
                       | (1ULL << (anceParser::T__65 - 64)) | (1ULL << (anceParser::NATIVE_INTEGER_TYPE - 64))
                       | (1ULL << (anceParser::SIGNED_INTEGER - 64)) | (1ULL << (anceParser::HEX_INTEGER - 64))
                       | (1ULL << (anceParser::BIN_INTEGER - 64)) | (1ULL << (anceParser::OCT_INTEGER - 64))
                       | (1ULL << (anceParser::HALF - 64)) | (1ULL << (anceParser::SINGLE - 64))
                       | (1ULL << (anceParser::DOUBLE - 64)) | (1ULL << (anceParser::QUAD - 64))
                       | (1ULL << (anceParser::STRING - 64)) | (1ULL << (anceParser::BYTE - 64))
                       | (1ULL << (anceParser::INTEGER - 64)) | (1ULL << (anceParser::IDENTIFIER - 64))))
                       != 0))
        {
            setState(444);
            expression(0);
            setState(449);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == anceParser::T__6)
            {
                setState(445);
                match(anceParser::T__6);
                setState(446);
                expression(0);
                setState(451);
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
    enterRule(_localctx, 68, anceParser::RuleVariableAccess);

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
        setState(454);
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
    enterRule(_localctx, 70, anceParser::RuleAllocation);
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
        setState(456);
        match(anceParser::T__47);
        setState(461);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::T__31)
        {
            setState(457);
            match(anceParser::T__31);
            setState(458);
            expression(0);
            setState(459);
            match(anceParser::T__32);
        }
        setState(463);
        allocator();
        setState(464);
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
    enterRule(_localctx, 72, anceParser::RuleAllocator);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(468);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__48:
            {
                _localctx = _tracker.createInstance<anceParser::DynamicContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(466);
                match(anceParser::T__48);
                break;
            }

            case anceParser::T__49:
            {
                _localctx = _tracker.createInstance<anceParser::AutomaticContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(467);
                match(anceParser::T__49);
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
    enterRule(_localctx, 74, anceParser::RuleAddressof);

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
        setState(470);
        match(anceParser::T__50);
        setState(471);
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
    enterRule(_localctx, 76, anceParser::RuleBindRef);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(478);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx))
        {
            case 1:
            {
                _localctx = _tracker.createInstance<anceParser::BindReferenceContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(473);
                match(anceParser::T__51);
                setState(474);
                expression(0);
                break;
            }

            case 2:
            {
                _localctx = _tracker.createInstance<anceParser::BindReferenceToAddressContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(475);
                match(anceParser::T__51);
                setState(476);
                match(anceParser::T__52);
                setState(477);
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
    enterRule(_localctx, 78, anceParser::RuleSizeofType);

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
        setState(480);
        match(anceParser::T__53);
        setState(481);
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
    enterRule(_localctx, 80, anceParser::RuleSizeofExpression);

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
        setState(483);
        match(anceParser::T__53);
        setState(484);
        match(anceParser::T__1);
        setState(485);
        expression(0);
        setState(486);
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

//----------------- MatchExpressionContext ------------------------------------------------------------------

anceParser::MatchExpressionContext::MatchExpressionContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

anceParser::ExpressionContext* anceParser::MatchExpressionContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

std::vector<anceParser::MatchExpressionCaseContext*> anceParser::MatchExpressionContext::matchExpressionCase()
{
    return getRuleContexts<anceParser::MatchExpressionCaseContext>();
}

anceParser::MatchExpressionCaseContext* anceParser::MatchExpressionContext::matchExpressionCase(size_t i)
{
    return getRuleContext<anceParser::MatchExpressionCaseContext>(i);
}

size_t anceParser::MatchExpressionContext::getRuleIndex() const
{
    return anceParser::RuleMatchExpression;
}

antlrcpp::Any anceParser::MatchExpressionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitMatchExpression(this);
    else return visitor->visitChildren(this);
}

anceParser::MatchExpressionContext* anceParser::matchExpression()
{
    MatchExpressionContext* _localctx = _tracker.createInstance<MatchExpressionContext>(_ctx, getState());
    enterRule(_localctx, 82, anceParser::RuleMatchExpression);
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
        setState(488);
        match(anceParser::T__25);
        setState(489);
        antlrcpp::downCast<MatchExpressionContext*>(_localctx)->condition = expression(0);
        setState(490);
        match(anceParser::T__26);
        setState(491);
        match(anceParser::T__3);
        setState(500);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 30) & ~0x3fULL) == 0)
             && ((1ULL << (_la - 30))
                 & ((1ULL << (anceParser::T__29 - 30)) | (1ULL << (anceParser::T__54 - 30))
                    | (1ULL << (anceParser::T__55 - 30)) | (1ULL << (anceParser::SIGNED_INTEGER - 30))
                    | (1ULL << (anceParser::HEX_INTEGER - 30)) | (1ULL << (anceParser::BIN_INTEGER - 30))
                    | (1ULL << (anceParser::OCT_INTEGER - 30)) | (1ULL << (anceParser::HALF - 30))
                    | (1ULL << (anceParser::SINGLE - 30)) | (1ULL << (anceParser::DOUBLE - 30))
                    | (1ULL << (anceParser::QUAD - 30)) | (1ULL << (anceParser::STRING - 30))
                    | (1ULL << (anceParser::BYTE - 30)) | (1ULL << (anceParser::INTEGER - 30))
                    | (1ULL << (anceParser::IDENTIFIER - 30))))
                    != 0))
        {
            setState(492);
            matchExpressionCase();
            setState(497);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == anceParser::T__6)
            {
                setState(493);
                match(anceParser::T__6);
                setState(494);
                matchExpressionCase();
                setState(499);
                _errHandler->sync(this);
                _la = _input->LA(1);
            }
        }
        setState(502);
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

//----------------- MatchExpressionCaseContext ------------------------------------------------------------------

anceParser::MatchExpressionCaseContext::MatchExpressionCaseContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

size_t anceParser::MatchExpressionCaseContext::getRuleIndex() const
{
    return anceParser::RuleMatchExpressionCase;
}

void anceParser::MatchExpressionCaseContext::copyFrom(MatchExpressionCaseContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- LiteralExpressionCaseContext ------------------------------------------------------------------

std::vector<anceParser::LiteralExpressionContext*> anceParser::LiteralExpressionCaseContext::literalExpression()
{
    return getRuleContexts<anceParser::LiteralExpressionContext>();
}

anceParser::LiteralExpressionContext* anceParser::LiteralExpressionCaseContext::literalExpression(size_t i)
{
    return getRuleContext<anceParser::LiteralExpressionContext>(i);
}

anceParser::ExpressionContext* anceParser::LiteralExpressionCaseContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::LiteralExpressionCaseContext::LiteralExpressionCaseContext(MatchExpressionCaseContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::LiteralExpressionCaseContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitLiteralExpressionCase(this);
    else return visitor->visitChildren(this);
}
//----------------- DefaultExpressionCaseContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::DefaultExpressionCaseContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::DefaultExpressionCaseContext::DefaultExpressionCaseContext(MatchExpressionCaseContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any anceParser::DefaultExpressionCaseContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
        return parserVisitor->visitDefaultExpressionCase(this);
    else return visitor->visitChildren(this);
}
anceParser::MatchExpressionCaseContext* anceParser::matchExpressionCase()
{
    MatchExpressionCaseContext* _localctx = _tracker.createInstance<MatchExpressionCaseContext>(_ctx, getState());
    enterRule(_localctx, 84, anceParser::RuleMatchExpressionCase);
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
        setState(518);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__54:
            case anceParser::T__55:
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
                _localctx = _tracker.createInstance<anceParser::LiteralExpressionCaseContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(504);
                literalExpression();
                setState(509);
                _errHandler->sync(this);
                _la = _input->LA(1);
                while (_la == anceParser::T__27)
                {
                    setState(505);
                    match(anceParser::T__27);
                    setState(506);
                    literalExpression();
                    setState(511);
                    _errHandler->sync(this);
                    _la = _input->LA(1);
                }
                setState(512);
                match(anceParser::T__28);
                setState(513);
                expression(0);
                break;
            }

            case anceParser::T__29:
            {
                _localctx = _tracker.createInstance<anceParser::DefaultExpressionCaseContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(515);
                match(anceParser::T__29);
                setState(516);
                match(anceParser::T__28);
                setState(517);
                expression(0);
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
    enterRule(_localctx, 86, anceParser::RuleLiteralExpression);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(527);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx))
        {
            case 1:
            {
                enterOuterAlt(_localctx, 1);
                setState(520);
                stringLiteral();
                break;
            }

            case 2:
            {
                enterOuterAlt(_localctx, 2);
                setState(521);
                byteLiteral();
                break;
            }

            case 3:
            {
                enterOuterAlt(_localctx, 3);
                setState(522);
                integerLiteral();
                break;
            }

            case 4:
            {
                enterOuterAlt(_localctx, 4);
                setState(523);
                floatingPointLiteral();
                break;
            }

            case 5:
            {
                enterOuterAlt(_localctx, 5);
                setState(524);
                booleanLiteral();
                break;
            }

            case 6:
            {
                enterOuterAlt(_localctx, 6);
                setState(525);
                sizeLiteral();
                break;
            }

            case 7:
            {
                enterOuterAlt(_localctx, 7);
                setState(526);
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
    enterRule(_localctx, 88, anceParser::RuleStringLiteral);
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
        setState(530);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::IDENTIFIER)
        {
            setState(529);
            antlrcpp::downCast<StringLiteralContext*>(_localctx)->prefix = match(anceParser::IDENTIFIER);
        }
        setState(532);
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
    enterRule(_localctx, 90, anceParser::RuleByteLiteral);

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
        setState(534);
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

anceParser::NormalIntegerContext* anceParser::IntegerLiteralContext::normalInteger()
{
    return getRuleContext<anceParser::NormalIntegerContext>(0);
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
    enterRule(_localctx, 92, anceParser::RuleIntegerLiteral);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(538);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::SIGNED_INTEGER:
            case anceParser::INTEGER:
            {
                enterOuterAlt(_localctx, 1);
                setState(536);
                normalInteger();
                break;
            }

            case anceParser::HEX_INTEGER:
            case anceParser::BIN_INTEGER:
            case anceParser::OCT_INTEGER:
            {
                enterOuterAlt(_localctx, 2);
                setState(537);
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

//----------------- NormalIntegerContext ------------------------------------------------------------------

anceParser::NormalIntegerContext::NormalIntegerContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{}

std::vector<tree::TerminalNode*> anceParser::NormalIntegerContext::INTEGER()
{
    return getTokens(anceParser::INTEGER);
}

tree::TerminalNode* anceParser::NormalIntegerContext::INTEGER(size_t i)
{
    return getToken(anceParser::INTEGER, i);
}

tree::TerminalNode* anceParser::NormalIntegerContext::SIGNED_INTEGER()
{
    return getToken(anceParser::SIGNED_INTEGER, 0);
}

size_t anceParser::NormalIntegerContext::getRuleIndex() const
{
    return anceParser::RuleNormalInteger;
}

antlrcpp::Any anceParser::NormalIntegerContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitNormalInteger(this);
    else return visitor->visitChildren(this);
}

anceParser::NormalIntegerContext* anceParser::normalInteger()
{
    NormalIntegerContext* _localctx = _tracker.createInstance<NormalIntegerContext>(_ctx, getState());
    enterRule(_localctx, 94, anceParser::RuleNormalInteger);

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
        setState(542);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::INTEGER:
            {
                setState(540);
                antlrcpp::downCast<NormalIntegerContext*>(_localctx)->uvalue = match(anceParser::INTEGER);
                break;
            }

            case anceParser::SIGNED_INTEGER:
            {
                setState(541);
                antlrcpp::downCast<NormalIntegerContext*>(_localctx)->svalue = match(anceParser::SIGNED_INTEGER);
                break;
            }

            default:
                throw NoViableAltException(this);
        }
        setState(546);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx))
        {
            case 1:
            {
                setState(544);
                match(anceParser::T__0);
                setState(545);
                antlrcpp::downCast<NormalIntegerContext*>(_localctx)->width = match(anceParser::INTEGER);
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
    enterRule(_localctx, 96, anceParser::RuleSpecialInteger);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(557);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::HEX_INTEGER:
            {
                enterOuterAlt(_localctx, 1);
                setState(548);
                match(anceParser::HEX_INTEGER);
                setState(549);
                match(anceParser::T__0);
                setState(550);
                antlrcpp::downCast<SpecialIntegerContext*>(_localctx)->width = match(anceParser::INTEGER);
                break;
            }

            case anceParser::BIN_INTEGER:
            {
                enterOuterAlt(_localctx, 2);
                setState(551);
                match(anceParser::BIN_INTEGER);
                setState(552);
                match(anceParser::T__0);
                setState(553);
                antlrcpp::downCast<SpecialIntegerContext*>(_localctx)->width = match(anceParser::INTEGER);
                break;
            }

            case anceParser::OCT_INTEGER:
            {
                enterOuterAlt(_localctx, 3);
                setState(554);
                match(anceParser::OCT_INTEGER);
                setState(555);
                match(anceParser::T__0);
                setState(556);
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
    enterRule(_localctx, 98, anceParser::RuleFloatingPointLiteral);
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
        setState(559);
        _la = _input->LA(1);
        if (!(((((_la - 72) & ~0x3fULL) == 0)
               && ((1ULL << (_la - 72))
                   & ((1ULL << (anceParser::HALF - 72)) | (1ULL << (anceParser::SINGLE - 72))
                      | (1ULL << (anceParser::DOUBLE - 72)) | (1ULL << (anceParser::QUAD - 72))))
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
    enterRule(_localctx, 100, anceParser::RuleBooleanLiteral);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(563);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__54:
            {
                _localctx = _tracker.createInstance<anceParser::TrueContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(561);
                match(anceParser::T__54);
                break;
            }

            case anceParser::T__55:
            {
                _localctx = _tracker.createInstance<anceParser::FalseContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(562);
                match(anceParser::T__55);
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
    enterRule(_localctx, 102, anceParser::RuleSizeLiteral);

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
        setState(565);
        match(anceParser::INTEGER);
        setState(566);
        match(anceParser::T__0);
        setState(567);
        match(anceParser::T__56);
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
    enterRule(_localctx, 104, anceParser::RuleDiffLiteral);

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
        setState(569);
        match(anceParser::SIGNED_INTEGER);
        setState(570);
        match(anceParser::T__0);
        setState(571);
        match(anceParser::T__57);
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
    enterRule(_localctx, 106, anceParser::RuleType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(581);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::NATIVE_INTEGER_TYPE:
            {
                _localctx = _tracker.createInstance<anceParser::IntegerContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(573);
                integerType();
                break;
            }

            case anceParser::T__31:
            {
                _localctx = _tracker.createInstance<anceParser::ArrayContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(574);
                arrayType();
                break;
            }

            case anceParser::T__56:
            case anceParser::T__57:
            case anceParser::T__59:
            case anceParser::T__60:
            case anceParser::T__61:
            case anceParser::T__62:
            case anceParser::T__63:
            case anceParser::T__64:
            case anceParser::T__65:
            {
                _localctx = _tracker.createInstance<anceParser::KeywordContext>(_localctx);
                enterOuterAlt(_localctx, 3);
                setState(575);
                keywordType();
                break;
            }

            case anceParser::T__36:
            {
                _localctx = _tracker.createInstance<anceParser::PointerContext>(_localctx);
                enterOuterAlt(_localctx, 4);
                setState(576);
                match(anceParser::T__36);
                setState(577);
                type();
                break;
            }

            case anceParser::T__58:
            {
                _localctx = _tracker.createInstance<anceParser::ReferenceContext>(_localctx);
                enterOuterAlt(_localctx, 5);
                setState(578);
                match(anceParser::T__58);
                setState(579);
                type();
                break;
            }

            case anceParser::IDENTIFIER:
            {
                _localctx = _tracker.createInstance<anceParser::CustomContext>(_localctx);
                enterOuterAlt(_localctx, 6);
                setState(580);
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
    enterRule(_localctx, 108, anceParser::RuleIntegerType);

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
        setState(583);
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
    enterRule(_localctx, 110, anceParser::RuleArrayType);

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
        setState(585);
        match(anceParser::T__31);
        setState(586);
        type();
        setState(587);
        match(anceParser::SEMICOLON);
        setState(588);
        match(anceParser::INTEGER);
        setState(589);
        match(anceParser::T__32);
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
    enterRule(_localctx, 112, anceParser::RuleKeywordType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(595);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__59:
            case anceParser::T__60:
            case anceParser::T__61:
            case anceParser::T__62:
            {
                enterOuterAlt(_localctx, 1);
                setState(591);
                floatingPointType();
                break;
            }

            case anceParser::T__56:
            case anceParser::T__57:
            case anceParser::T__63:
            {
                enterOuterAlt(_localctx, 2);
                setState(592);
                targetDependentType();
                break;
            }

            case anceParser::T__64:
            {
                enterOuterAlt(_localctx, 3);
                setState(593);
                booleanType();
                break;
            }

            case anceParser::T__65:
            {
                enterOuterAlt(_localctx, 4);
                setState(594);
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
    enterRule(_localctx, 114, anceParser::RuleFloatingPointType);
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
        setState(597);
        _la = _input->LA(1);
        if (!((((_la & ~0x3fULL) == 0)
               && ((1ULL << _la)
                   & ((1ULL << anceParser::T__59) | (1ULL << anceParser::T__60) | (1ULL << anceParser::T__61)
                      | (1ULL << anceParser::T__62)))
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
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitTargetDependentType(this);
    else return visitor->visitChildren(this);
}

anceParser::TargetDependentTypeContext* anceParser::targetDependentType()
{
    TargetDependentTypeContext* _localctx = _tracker.createInstance<TargetDependentTypeContext>(_ctx, getState());
    enterRule(_localctx, 116, anceParser::RuleTargetDependentType);
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
        setState(599);
        _la = _input->LA(1);
        if (!(((((_la - 57) & ~0x3fULL) == 0)
               && ((1ULL << (_la - 57))
                   & ((1ULL << (anceParser::T__56 - 57)) | (1ULL << (anceParser::T__57 - 57))
                      | (1ULL << (anceParser::T__63 - 57))))
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
    enterRule(_localctx, 118, anceParser::RuleBooleanType);

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
        setState(601);
        match(anceParser::T__64);
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
    enterRule(_localctx, 120, anceParser::RuleVoidType);

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
        setState(603);
        match(anceParser::T__65);
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
    enterRule(_localctx, 122, anceParser::RuleCustomType);

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
        setState(605);
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
        case 26:
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
            return precpred(_ctx, 8);
        case 1:
            return precpred(_ctx, 7);
        case 2:
            return precpred(_ctx, 6);
        case 3:
            return precpred(_ctx, 5);
        case 4:
            return precpred(_ctx, 4);
        case 5:
            return precpred(_ctx, 3);
        case 6:
            return precpred(_ctx, 18);
        case 7:
            return precpred(_ctx, 17);
        case 8:
            return precpred(_ctx, 16);

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
                                                   "defineAlias",
                                                   "structDefinition",
                                                   "member",
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
                                                   "matchExpression",
                                                   "matchExpressionCase",
                                                   "literalExpression",
                                                   "stringLiteral",
                                                   "byteLiteral",
                                                   "integerLiteral",
                                                   "normalInteger",
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
                                                      "'alias'",
                                                      "'struct'",
                                                      "'public'",
                                                      "'private'",
                                                      "'let'",
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
                                                      "'.'",
                                                      "'['",
                                                      "']'",
                                                      "'not'",
                                                      "'and'",
                                                      "'or'",
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
                                                      "'ref'",
                                                      "'to'",
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
        else { _tokenNames.push_back(name); }
    }

    static const uint16_t serializedATNSegment0[] = {
        0x3,   0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 0x3,   0x58,  0x262, 0x4,   0x2,   0x9,
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
        0x4,   0x3b,   0x9,    0x3b,   0x4,    0x3c,   0x9,    0x3c,   0x4,    0x3d,  0x9,   0x3d,  0x4,   0x3e,  0x9,
        0x3e,  0x4,    0x3f,   0x9,    0x3f,   0x3,    0x2,    0x3,    0x2,    0x3,   0x2,   0x7,   0x2,   0x82,  0xa,
        0x2,   0xc,    0x2,    0xe,    0x2,    0x85,   0xb,    0x2,    0x3,    0x2,   0x3,   0x2,   0x3,   0x3,   0x3,
        0x3,   0x5,    0x3,    0x8b,   0xa,    0x3,    0x3,    0x3,    0x3,    0x3,   0x3,   0x3,   0x3,   0x3,   0x3,
        0x3,   0x3,    0x3,    0x5,    0x3,    0x93,   0xa,    0x3,    0x3,    0x3,   0x3,   0x3,   0x3,   0x4,   0x3,
        0x4,   0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x3,   0x4,   0x5,   0x4,   0x9e,  0xa,
        0x4,   0x3,    0x4,    0x3,    0x4,    0x7,    0x4,    0xa2,   0xa,    0x4,   0xc,   0x4,   0xe,   0x4,   0xa5,
        0xb,   0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,   0x3,   0x4,   0x3,   0x4,   0x3,
        0x4,   0x3,    0x4,    0x3,    0x4,    0x5,    0x4,    0xb0,   0xa,    0x4,   0x3,   0x4,   0x3,   0x4,   0x5,
        0x4,   0xb4,   0xa,    0x4,    0x3,    0x5,    0x3,    0x5,    0x3,    0x5,   0x7,   0x5,   0xb9,  0xa,   0x5,
        0xc,   0x5,    0xe,    0x5,    0xbc,   0xb,    0x5,    0x5,    0x5,    0xbe,  0xa,   0x5,   0x3,   0x6,   0x3,
        0x6,   0x3,    0x6,    0x3,    0x6,    0x3,    0x7,    0x3,    0x7,    0x5,   0x7,   0xc6,  0xa,   0x7,   0x3,
        0x8,   0x3,    0x8,    0x3,    0x8,    0x3,    0x8,    0x3,    0x8,    0x3,   0x8,   0x3,   0x8,   0x3,   0x9,
        0x3,   0x9,    0x3,    0x9,    0x3,    0x9,    0x3,    0x9,    0x7,    0x9,   0xd4,  0xa,   0x9,   0xc,   0x9,
        0xe,   0x9,    0xd7,   0xb,    0x9,    0x3,    0x9,    0x3,    0x9,    0x3,   0xa,   0x3,   0xa,   0x3,   0xa,
        0x3,   0xa,    0x3,    0xa,    0x3,    0xa,    0x3,    0xa,    0x5,    0xa,   0xe2,  0xa,   0xa,   0x3,   0xa,
        0x3,   0xa,    0x3,    0xb,    0x3,    0xb,    0x5,    0xb,    0xe8,   0xa,   0xb,   0x3,   0xc,   0x3,   0xc,
        0x5,   0xc,    0xec,   0xa,    0xc,    0x3,    0xd,    0x3,    0xd,    0x7,   0xd,   0xf0,  0xa,   0xd,   0xc,
        0xd,   0xe,    0xd,    0xf3,   0xb,    0xd,    0x3,    0xd,    0x3,    0xd,   0x3,   0xe,   0x3,   0xe,   0x3,
        0xe,   0x3,    0xe,    0x3,    0xe,    0x3,    0xe,    0x3,    0xe,    0x3,   0xe,   0x3,   0xe,   0x3,   0xe,
        0x3,   0xe,    0x5,    0xe,    0x102,  0xa,    0xe,    0x3,    0xf,    0x3,   0xf,   0x3,   0xf,   0x3,   0x10,
        0x3,   0x10,   0x3,    0x10,   0x3,    0x10,   0x3,    0x10,   0x3,    0x10,  0x3,   0x10,  0x5,   0x10,  0x10e,
        0xa,   0x10,   0x3,    0x10,   0x3,    0x10,   0x3,    0x11,   0x3,    0x11,  0x3,   0x11,  0x3,   0x11,  0x3,
        0x11,  0x3,    0x11,   0x3,    0x11,   0x3,    0x12,   0x3,    0x12,   0x3,   0x12,  0x3,   0x12,  0x3,   0x13,
        0x3,   0x13,   0x3,    0x13,   0x3,    0x13,   0x3,    0x13,   0x3,    0x14,  0x3,   0x14,  0x3,   0x14,  0x5,
        0x14,  0x125,  0xa,    0x14,   0x3,    0x15,   0x3,    0x15,   0x5,    0x15,  0x129, 0xa,   0x15,  0x3,   0x15,
        0x3,   0x15,   0x3,    0x15,   0x3,    0x16,   0x3,    0x16,   0x5,    0x16,  0x130, 0xa,   0x16,  0x3,   0x16,
        0x3,   0x16,   0x3,    0x17,   0x3,    0x17,   0x3,    0x17,   0x3,    0x17,  0x3,   0x18,  0x3,   0x18,  0x3,
        0x18,  0x3,    0x18,   0x3,    0x18,   0x3,    0x18,   0x5,    0x18,   0x13e, 0xa,   0x18,  0x3,   0x19,  0x3,
        0x19,  0x3,    0x19,   0x3,    0x19,   0x3,    0x19,   0x3,    0x1a,   0x3,   0x1a,  0x3,   0x1a,  0x3,   0x1a,
        0x3,   0x1a,   0x7,    0x1a,   0x14a,  0xa,    0x1a,   0xc,    0x1a,   0xe,   0x1a,  0x14d, 0xb,   0x1a,  0x3,
        0x1a,  0x3,    0x1a,   0x3,    0x1b,   0x3,    0x1b,   0x3,    0x1b,   0x7,   0x1b,  0x154, 0xa,   0x1b,  0xc,
        0x1b,  0xe,    0x1b,   0x157,  0xb,    0x1b,   0x3,    0x1b,   0x3,    0x1b,  0x3,   0x1b,  0x3,   0x1b,  0x3,
        0x1b,  0x3,    0x1b,   0x5,    0x1b,   0x15f,  0xa,    0x1b,   0x3,    0x1c,  0x3,   0x1c,  0x3,   0x1c,  0x3,
        0x1c,  0x3,    0x1c,   0x3,    0x1c,   0x3,    0x1c,   0x3,    0x1c,   0x3,   0x1c,  0x3,   0x1c,  0x3,   0x1c,
        0x3,   0x1c,   0x3,    0x1c,   0x3,    0x1c,   0x3,    0x1c,   0x3,    0x1c,  0x3,   0x1c,  0x3,   0x1c,  0x3,
        0x1c,  0x3,    0x1c,   0x3,    0x1c,   0x3,    0x1c,   0x3,    0x1c,   0x5,   0x1c,  0x178, 0xa,   0x1c,  0x3,
        0x1c,  0x3,    0x1c,   0x3,    0x1c,   0x3,    0x1c,   0x3,    0x1c,   0x3,   0x1c,  0x3,   0x1c,  0x3,   0x1c,
        0x3,   0x1c,   0x3,    0x1c,   0x3,    0x1c,   0x3,    0x1c,   0x3,    0x1c,  0x3,   0x1c,  0x3,   0x1c,  0x3,
        0x1c,  0x3,    0x1c,   0x3,    0x1c,   0x3,    0x1c,   0x3,    0x1c,   0x3,   0x1c,  0x3,   0x1c,  0x3,   0x1c,
        0x3,   0x1c,   0x3,    0x1c,   0x3,    0x1c,   0x3,    0x1c,   0x3,    0x1c,  0x3,   0x1c,  0x3,   0x1c,  0x3,
        0x1c,  0x7,    0x1c,   0x199,  0xa,    0x1c,   0xc,    0x1c,   0xe,    0x1c,  0x19c, 0xb,   0x1c,  0x3,   0x1d,
        0x3,   0x1d,   0x3,    0x1d,   0x5,    0x1d,   0x1a1,  0xa,    0x1d,   0x3,   0x1e,  0x3,   0x1e,  0x5,   0x1e,
        0x1a5, 0xa,    0x1e,   0x3,    0x1f,   0x3,    0x1f,   0x3,    0x1f,   0x3,   0x1f,  0x5,   0x1f,  0x1ab, 0xa,
        0x1f,  0x3,    0x20,   0x3,    0x20,   0x5,    0x20,   0x1af,  0xa,    0x20,  0x3,   0x21,  0x3,   0x21,  0x3,
        0x22,  0x3,    0x22,   0x3,    0x22,   0x3,    0x22,   0x3,    0x22,   0x3,   0x22,  0x3,   0x22,  0x3,   0x22,
        0x3,   0x22,   0x3,    0x22,   0x5,    0x22,   0x1bd,  0xa,    0x22,   0x3,   0x23,  0x3,   0x23,  0x3,   0x23,
        0x7,   0x23,   0x1c2,  0xa,    0x23,   0xc,    0x23,   0xe,    0x23,   0x1c5, 0xb,   0x23,  0x5,   0x23,  0x1c7,
        0xa,   0x23,   0x3,    0x24,   0x3,    0x24,   0x3,    0x25,   0x3,    0x25,  0x3,   0x25,  0x3,   0x25,  0x3,
        0x25,  0x5,    0x25,   0x1d0,  0xa,    0x25,   0x3,    0x25,   0x3,    0x25,  0x3,   0x25,  0x3,   0x26,  0x3,
        0x26,  0x5,    0x26,   0x1d7,  0xa,    0x26,   0x3,    0x27,   0x3,    0x27,  0x3,   0x27,  0x3,   0x28,  0x3,
        0x28,  0x3,    0x28,   0x3,    0x28,   0x3,    0x28,   0x5,    0x28,   0x1e1, 0xa,   0x28,  0x3,   0x29,  0x3,
        0x29,  0x3,    0x29,   0x3,    0x2a,   0x3,    0x2a,   0x3,    0x2a,   0x3,   0x2a,  0x3,   0x2a,  0x3,   0x2b,
        0x3,   0x2b,   0x3,    0x2b,   0x3,    0x2b,   0x3,    0x2b,   0x3,    0x2b,  0x3,   0x2b,  0x7,   0x2b,  0x1f2,
        0xa,   0x2b,   0xc,    0x2b,   0xe,    0x2b,   0x1f5,  0xb,    0x2b,   0x5,   0x2b,  0x1f7, 0xa,   0x2b,  0x3,
        0x2b,  0x3,    0x2b,   0x3,    0x2c,   0x3,    0x2c,   0x3,    0x2c,   0x7,   0x2c,  0x1fe, 0xa,   0x2c,  0xc,
        0x2c,  0xe,    0x2c,   0x201,  0xb,    0x2c,   0x3,    0x2c,   0x3,    0x2c,  0x3,   0x2c,  0x3,   0x2c,  0x3,
        0x2c,  0x3,    0x2c,   0x5,    0x2c,   0x209,  0xa,    0x2c,   0x3,    0x2d,  0x3,   0x2d,  0x3,   0x2d,  0x3,
        0x2d,  0x3,    0x2d,   0x3,    0x2d,   0x3,    0x2d,   0x5,    0x2d,   0x212, 0xa,   0x2d,  0x3,   0x2e,  0x5,
        0x2e,  0x215,  0xa,    0x2e,   0x3,    0x2e,   0x3,    0x2e,   0x3,    0x2f,  0x3,   0x2f,  0x3,   0x30,  0x3,
        0x30,  0x5,    0x30,   0x21d,  0xa,    0x30,   0x3,    0x31,   0x3,    0x31,  0x5,   0x31,  0x221, 0xa,   0x31,
        0x3,   0x31,   0x3,    0x31,   0x5,    0x31,   0x225,  0xa,    0x31,   0x3,   0x32,  0x3,   0x32,  0x3,   0x32,
        0x3,   0x32,   0x3,    0x32,   0x3,    0x32,   0x3,    0x32,   0x3,    0x32,  0x3,   0x32,  0x5,   0x32,  0x230,
        0xa,   0x32,   0x3,    0x33,   0x3,    0x33,   0x3,    0x34,   0x3,    0x34,  0x5,   0x34,  0x236, 0xa,   0x34,
        0x3,   0x35,   0x3,    0x35,   0x3,    0x35,   0x3,    0x35,   0x3,    0x36,  0x3,   0x36,  0x3,   0x36,  0x3,
        0x36,  0x3,    0x37,   0x3,    0x37,   0x3,    0x37,   0x3,    0x37,   0x3,   0x37,  0x3,   0x37,  0x3,   0x37,
        0x3,   0x37,   0x5,    0x37,   0x248,  0xa,    0x37,   0x3,    0x38,   0x3,   0x38,  0x3,   0x39,  0x3,   0x39,
        0x3,   0x39,   0x3,    0x39,   0x3,    0x39,   0x3,    0x39,   0x3,    0x3a,  0x3,   0x3a,  0x3,   0x3a,  0x3,
        0x3a,  0x5,    0x3a,   0x256,  0xa,    0x3a,   0x3,    0x3b,   0x3,    0x3b,  0x3,   0x3c,  0x3,   0x3c,  0x3,
        0x3d,  0x3,    0x3d,   0x3,    0x3e,   0x3,    0x3e,   0x3,    0x3f,   0x3,   0x3f,  0x3,   0x3f,  0x2,   0x3,
        0x36,  0x40,   0x2,    0x4,    0x6,    0x8,    0xa,    0xc,    0xe,    0x10,  0x12,  0x14,  0x16,  0x18,  0x1a,
        0x1c,  0x1e,   0x20,   0x22,   0x24,   0x26,   0x28,   0x2a,   0x2c,   0x2e,  0x30,  0x32,  0x34,  0x36,  0x38,
        0x3a,  0x3c,   0x3e,   0x40,   0x42,   0x44,   0x46,   0x48,   0x4a,   0x4c,  0x4e,  0x50,  0x52,  0x54,  0x56,
        0x58,  0x5a,   0x5c,   0x5e,   0x60,   0x62,   0x64,   0x66,   0x68,   0x6a,  0x6c,  0x6e,  0x70,  0x72,  0x74,
        0x76,  0x78,   0x7a,   0x7c,   0x2,    0x5,    0x3,    0x2,    0x4a,   0x4d,  0x3,   0x2,   0x3e,  0x41,  0x4,
        0x2,   0x3b,   0x3c,   0x42,   0x42,   0x2,    0x281,  0x2,    0x83,   0x3,   0x2,   0x2,   0x2,   0x4,   0x88,
        0x3,   0x2,    0x2,    0x2,    0x6,    0xb3,   0x3,    0x2,    0x2,    0x2,   0x8,   0xbd,  0x3,   0x2,   0x2,
        0x2,   0xa,    0xbf,   0x3,    0x2,    0x2,    0x2,    0xc,    0xc5,   0x3,   0x2,   0x2,   0x2,   0xe,   0xc7,
        0x3,   0x2,    0x2,    0x2,    0x10,   0xce,   0x3,    0x2,    0x2,    0x2,   0x12,  0xda,  0x3,   0x2,   0x2,
        0x2,   0x14,   0xe7,   0x3,    0x2,    0x2,    0x2,    0x16,   0xeb,   0x3,   0x2,   0x2,   0x2,   0x18,  0xed,
        0x3,   0x2,    0x2,    0x2,    0x1a,   0x101,  0x3,    0x2,    0x2,    0x2,   0x1c,  0x103, 0x3,   0x2,   0x2,
        0x2,   0x1e,   0x106,  0x3,    0x2,    0x2,    0x2,    0x20,   0x111,  0x3,   0x2,   0x2,   0x2,   0x22,  0x118,
        0x3,   0x2,    0x2,    0x2,    0x24,   0x11c,  0x3,    0x2,    0x2,    0x2,   0x26,  0x124, 0x3,   0x2,   0x2,
        0x2,   0x28,   0x126,  0x3,    0x2,    0x2,    0x2,    0x2a,   0x12d,  0x3,   0x2,   0x2,   0x2,   0x2c,  0x133,
        0x3,   0x2,    0x2,    0x2,    0x2e,   0x137,  0x3,    0x2,    0x2,    0x2,   0x30,  0x13f, 0x3,   0x2,   0x2,
        0x2,   0x32,   0x144,  0x3,    0x2,    0x2,    0x2,    0x34,   0x15e,  0x3,   0x2,   0x2,   0x2,   0x36,  0x177,
        0x3,   0x2,    0x2,    0x2,    0x38,   0x1a0,  0x3,    0x2,    0x2,    0x2,   0x3a,  0x1a4, 0x3,   0x2,   0x2,
        0x2,   0x3c,   0x1aa,  0x3,    0x2,    0x2,    0x2,    0x3e,   0x1ae,  0x3,   0x2,   0x2,   0x2,   0x40,  0x1b0,
        0x3,   0x2,    0x2,    0x2,    0x42,   0x1bc,  0x3,    0x2,    0x2,    0x2,   0x44,  0x1c6, 0x3,   0x2,   0x2,
        0x2,   0x46,   0x1c8,  0x3,    0x2,    0x2,    0x2,    0x48,   0x1ca,  0x3,   0x2,   0x2,   0x2,   0x4a,  0x1d6,
        0x3,   0x2,    0x2,    0x2,    0x4c,   0x1d8,  0x3,    0x2,    0x2,    0x2,   0x4e,  0x1e0, 0x3,   0x2,   0x2,
        0x2,   0x50,   0x1e2,  0x3,    0x2,    0x2,    0x2,    0x52,   0x1e5,  0x3,   0x2,   0x2,   0x2,   0x54,  0x1ea,
        0x3,   0x2,    0x2,    0x2,    0x56,   0x208,  0x3,    0x2,    0x2,    0x2,   0x58,  0x211, 0x3,   0x2,   0x2,
        0x2,   0x5a,   0x214,  0x3,    0x2,    0x2,    0x2,    0x5c,   0x218,  0x3,   0x2,   0x2,   0x2,   0x5e,  0x21c,
        0x3,   0x2,    0x2,    0x2,    0x60,   0x220,  0x3,    0x2,    0x2,    0x2,   0x62,  0x22f, 0x3,   0x2,   0x2,
        0x2,   0x64,   0x231,  0x3,    0x2,    0x2,    0x2,    0x66,   0x235,  0x3,   0x2,   0x2,   0x2,   0x68,  0x237,
        0x3,   0x2,    0x2,    0x2,    0x6a,   0x23b,  0x3,    0x2,    0x2,    0x2,   0x6c,  0x247, 0x3,   0x2,   0x2,
        0x2,   0x6e,   0x249,  0x3,    0x2,    0x2,    0x2,    0x70,   0x24b,  0x3,   0x2,   0x2,   0x2,   0x72,  0x255,
        0x3,   0x2,    0x2,    0x2,    0x74,   0x257,  0x3,    0x2,    0x2,    0x2,   0x76,  0x259, 0x3,   0x2,   0x2,
        0x2,   0x78,   0x25b,  0x3,    0x2,    0x2,    0x2,    0x7a,   0x25d,  0x3,   0x2,   0x2,   0x2,   0x7c,  0x25f,
        0x3,   0x2,    0x2,    0x2,    0x7e,   0x82,   0x5,    0x4,    0x3,    0x2,   0x7f,  0x82,  0x5,   0x6,   0x4,
        0x2,   0x80,   0x82,   0x5,    0xc,    0x7,    0x2,    0x81,   0x7e,   0x3,   0x2,   0x2,   0x2,   0x81,  0x7f,
        0x3,   0x2,    0x2,    0x2,    0x81,   0x80,   0x3,    0x2,    0x2,    0x2,   0x82,  0x85,  0x3,   0x2,   0x2,
        0x2,   0x83,   0x81,   0x3,    0x2,    0x2,    0x2,    0x83,   0x84,   0x3,   0x2,   0x2,   0x2,   0x84,  0x86,
        0x3,   0x2,    0x2,    0x2,    0x85,   0x83,   0x3,    0x2,    0x2,    0x2,   0x86,  0x87,  0x7,   0x2,   0x2,
        0x3,   0x87,   0x3,    0x3,    0x2,    0x2,    0x2,    0x88,   0x8a,   0x5,   0x14,  0xb,   0x2,   0x89,  0x8b,
        0x7,   0x53,   0x2,    0x2,    0x8a,   0x89,   0x3,    0x2,    0x2,    0x2,   0x8a,  0x8b,  0x3,   0x2,   0x2,
        0x2,   0x8b,   0x8c,   0x3,    0x2,    0x2,    0x2,    0x8c,   0x8d,   0x7,   0x54,  0x2,   0x2,   0x8d,  0x8e,
        0x7,   0x3,    0x2,    0x2,    0x8e,   0x92,   0x5,    0x6c,   0x37,   0x2,   0x8f,  0x90,  0x5,   0x26,  0x14,
        0x2,   0x90,   0x91,   0x5,    0x58,   0x2d,   0x2,    0x91,   0x93,   0x3,   0x2,   0x2,   0x2,   0x92,  0x8f,
        0x3,   0x2,    0x2,    0x2,    0x92,   0x93,   0x3,    0x2,    0x2,    0x2,   0x93,  0x94,  0x3,   0x2,   0x2,
        0x2,   0x94,   0x95,   0x7,    0x55,   0x2,    0x2,    0x95,   0x5,    0x3,   0x2,   0x2,   0x2,   0x96,  0x97,
        0x5,   0x14,   0xb,    0x2,    0x97,   0x98,   0x7,    0x54,   0x2,    0x2,   0x98,  0x99,  0x7,   0x4,   0x2,
        0x2,   0x99,   0x9a,   0x5,    0x8,    0x5,    0x2,    0x9a,   0x9d,   0x7,   0x5,   0x2,   0x2,   0x9b,  0x9c,
        0x7,   0x3,    0x2,    0x2,    0x9c,   0x9e,   0x5,    0x6c,   0x37,   0x2,   0x9d,  0x9b,  0x3,   0x2,   0x2,
        0x2,   0x9d,   0x9e,   0x3,    0x2,    0x2,    0x2,    0x9e,   0x9f,   0x3,   0x2,   0x2,   0x2,   0x9f,  0xa3,
        0x7,   0x6,    0x2,    0x2,    0xa0,   0xa2,   0x5,    0x16,   0xc,    0x2,   0xa1,  0xa0,  0x3,   0x2,   0x2,
        0x2,   0xa2,   0xa5,   0x3,    0x2,    0x2,    0x2,    0xa3,   0xa1,   0x3,   0x2,   0x2,   0x2,   0xa3,  0xa4,
        0x3,   0x2,    0x2,    0x2,    0xa4,   0xa6,   0x3,    0x2,    0x2,    0x2,   0xa5,  0xa3,  0x3,   0x2,   0x2,
        0x2,   0xa6,   0xa7,   0x7,    0x7,    0x2,    0x2,    0xa7,   0xb4,   0x3,   0x2,   0x2,   0x2,   0xa8,  0xa9,
        0x7,   0x8,    0x2,    0x2,    0xa9,   0xaa,   0x7,    0x54,   0x2,    0x2,   0xaa,  0xab,  0x7,   0x4,   0x2,
        0x2,   0xab,   0xac,   0x5,    0x8,    0x5,    0x2,    0xac,   0xaf,   0x7,   0x5,   0x2,   0x2,   0xad,  0xae,
        0x7,   0x3,    0x2,    0x2,    0xae,   0xb0,   0x5,    0x6c,   0x37,   0x2,   0xaf,  0xad,  0x3,   0x2,   0x2,
        0x2,   0xaf,   0xb0,   0x3,    0x2,    0x2,    0x2,    0xb0,   0xb1,   0x3,   0x2,   0x2,   0x2,   0xb1,  0xb2,
        0x7,   0x55,   0x2,    0x2,    0xb2,   0xb4,   0x3,    0x2,    0x2,    0x2,   0xb3,  0x96,  0x3,   0x2,   0x2,
        0x2,   0xb3,   0xa8,   0x3,    0x2,    0x2,    0x2,    0xb4,   0x7,    0x3,   0x2,   0x2,   0x2,   0xb5,  0xba,
        0x5,   0xa,    0x6,    0x2,    0xb6,   0xb7,   0x7,    0x9,    0x2,    0x2,   0xb7,  0xb9,  0x5,   0xa,   0x6,
        0x2,   0xb8,   0xb6,   0x3,    0x2,    0x2,    0x2,    0xb9,   0xbc,   0x3,   0x2,   0x2,   0x2,   0xba,  0xb8,
        0x3,   0x2,    0x2,    0x2,    0xba,   0xbb,   0x3,    0x2,    0x2,    0x2,   0xbb,  0xbe,  0x3,   0x2,   0x2,
        0x2,   0xbc,   0xba,   0x3,    0x2,    0x2,    0x2,    0xbd,   0xb5,   0x3,   0x2,   0x2,   0x2,   0xbd,  0xbe,
        0x3,   0x2,    0x2,    0x2,    0xbe,   0x9,    0x3,    0x2,    0x2,    0x2,   0xbf,  0xc0,  0x7,   0x54,  0x2,
        0x2,   0xc0,   0xc1,   0x7,    0x3,    0x2,    0x2,    0xc1,   0xc2,   0x5,   0x6c,  0x37,  0x2,   0xc2,  0xb,
        0x3,   0x2,    0x2,    0x2,    0xc3,   0xc6,   0x5,    0xe,    0x8,    0x2,   0xc4,  0xc6,  0x5,   0x10,  0x9,
        0x2,   0xc5,   0xc3,   0x3,    0x2,    0x2,    0x2,    0xc5,   0xc4,   0x3,   0x2,   0x2,   0x2,   0xc6,  0xd,
        0x3,   0x2,    0x2,    0x2,    0xc7,   0xc8,   0x5,    0x14,   0xb,    0x2,   0xc8,  0xc9,  0x7,   0xa,   0x2,
        0x2,   0xc9,   0xca,   0x7,    0x54,   0x2,    0x2,    0xca,   0xcb,   0x7,   0xb,   0x2,   0x2,   0xcb,  0xcc,
        0x5,   0x6c,   0x37,   0x2,    0xcc,   0xcd,   0x7,    0x55,   0x2,    0x2,   0xcd,  0xf,   0x3,   0x2,   0x2,
        0x2,   0xce,   0xcf,   0x5,    0x14,   0xb,    0x2,    0xcf,   0xd0,   0x7,   0xc,   0x2,   0x2,   0xd0,  0xd1,
        0x7,   0x54,   0x2,    0x2,    0xd1,   0xd5,   0x7,    0x6,    0x2,    0x2,   0xd2,  0xd4,  0x5,   0x12,  0xa,
        0x2,   0xd3,   0xd2,   0x3,    0x2,    0x2,    0x2,    0xd4,   0xd7,   0x3,   0x2,   0x2,   0x2,   0xd5,  0xd3,
        0x3,   0x2,    0x2,    0x2,    0xd5,   0xd6,   0x3,    0x2,    0x2,    0x2,   0xd6,  0xd8,  0x3,   0x2,   0x2,
        0x2,   0xd7,   0xd5,   0x3,    0x2,    0x2,    0x2,    0xd8,   0xd9,   0x7,   0x7,   0x2,   0x2,   0xd9,  0x11,
        0x3,   0x2,    0x2,    0x2,    0xda,   0xdb,   0x5,    0x14,   0xb,    0x2,   0xdb,  0xdc,  0x7,   0x54,  0x2,
        0x2,   0xdc,   0xdd,   0x7,    0x3,    0x2,    0x2,    0xdd,   0xe1,   0x5,   0x6c,  0x37,  0x2,   0xde,  0xdf,
        0x5,   0x26,   0x14,   0x2,    0xdf,   0xe0,   0x5,    0x58,   0x2d,   0x2,   0xe0,  0xe2,  0x3,   0x2,   0x2,
        0x2,   0xe1,   0xde,   0x3,    0x2,    0x2,    0x2,    0xe1,   0xe2,   0x3,   0x2,   0x2,   0x2,   0xe2,  0xe3,
        0x3,   0x2,    0x2,    0x2,    0xe3,   0xe4,   0x7,    0x55,   0x2,    0x2,   0xe4,  0x13,  0x3,   0x2,   0x2,
        0x2,   0xe5,   0xe8,   0x7,    0xd,    0x2,    0x2,    0xe6,   0xe8,   0x7,   0xe,   0x2,   0x2,   0xe7,  0xe5,
        0x3,   0x2,    0x2,    0x2,    0xe7,   0xe6,   0x3,    0x2,    0x2,    0x2,   0xe8,  0x15,  0x3,   0x2,   0x2,
        0x2,   0xe9,   0xec,   0x5,    0x1a,   0xe,    0x2,    0xea,   0xec,   0x5,   0x18,  0xd,   0x2,   0xeb,  0xe9,
        0x3,   0x2,    0x2,    0x2,    0xeb,   0xea,   0x3,    0x2,    0x2,    0x2,   0xec,  0x17,  0x3,   0x2,   0x2,
        0x2,   0xed,   0xf1,   0x7,    0x6,    0x2,    0x2,    0xee,   0xf0,   0x5,   0x16,  0xc,   0x2,   0xef,  0xee,
        0x3,   0x2,    0x2,    0x2,    0xf0,   0xf3,   0x3,    0x2,    0x2,    0x2,   0xf1,  0xef,  0x3,   0x2,   0x2,
        0x2,   0xf1,   0xf2,   0x3,    0x2,    0x2,    0x2,    0xf2,   0xf4,   0x3,   0x2,   0x2,   0x2,   0xf3,  0xf1,
        0x3,   0x2,    0x2,    0x2,    0xf4,   0xf5,   0x7,    0x7,    0x2,    0x2,   0xf5,  0x19,  0x3,   0x2,   0x2,
        0x2,   0xf6,   0x102,  0x5,    0x1c,   0xf,    0x2,    0xf7,   0x102,  0x5,   0x1e,  0x10,  0x2,   0xf8,  0x102,
        0x5,   0x20,   0x11,   0x2,    0xf9,   0x102,  0x5,    0x22,   0x12,   0x2,   0xfa,  0x102, 0x5,   0x24,  0x13,
        0x2,   0xfb,   0x102,  0x5,    0x28,   0x15,   0x2,    0xfc,   0x102,  0x5,   0x2a,  0x16,  0x2,   0xfd,  0x102,
        0x5,   0x2c,   0x17,   0x2,    0xfe,   0x102,  0x5,    0x2e,   0x18,   0x2,   0xff,  0x102, 0x5,   0x30,  0x19,
        0x2,   0x100,  0x102,  0x5,    0x32,   0x1a,   0x2,    0x101,  0xf6,   0x3,   0x2,   0x2,   0x2,   0x101, 0xf7,
        0x3,   0x2,    0x2,    0x2,    0x101,  0xf8,   0x3,    0x2,    0x2,    0x2,   0x101, 0xf9,  0x3,   0x2,   0x2,
        0x2,   0x101,  0xfa,   0x3,    0x2,    0x2,    0x2,    0x101,  0xfb,   0x3,   0x2,   0x2,   0x2,   0x101, 0xfc,
        0x3,   0x2,    0x2,    0x2,    0x101,  0xfd,   0x3,    0x2,    0x2,    0x2,   0x101, 0xfe,  0x3,   0x2,   0x2,
        0x2,   0x101,  0xff,   0x3,    0x2,    0x2,    0x2,    0x101,  0x100,  0x3,   0x2,   0x2,   0x2,   0x102, 0x1b,
        0x3,   0x2,    0x2,    0x2,    0x103,  0x104,  0x5,    0x40,   0x21,   0x2,   0x104, 0x105, 0x7,   0x55,  0x2,
        0x2,   0x105,  0x1d,   0x3,    0x2,    0x2,    0x2,    0x106,  0x107,  0x7,   0xf,   0x2,   0x2,   0x107, 0x108,
        0x7,   0x54,   0x2,    0x2,    0x108,  0x109,  0x7,    0x3,    0x2,    0x2,   0x109, 0x10d, 0x5,   0x6c,  0x37,
        0x2,   0x10a,  0x10b,  0x5,    0x26,   0x14,   0x2,    0x10b,  0x10c,  0x5,   0x36,  0x1c,  0x2,   0x10c, 0x10e,
        0x3,   0x2,    0x2,    0x2,    0x10d,  0x10a,  0x3,    0x2,    0x2,    0x2,   0x10d, 0x10e, 0x3,   0x2,   0x2,
        0x2,   0x10e,  0x10f,  0x3,    0x2,    0x2,    0x2,    0x10f,  0x110,  0x7,   0x55,  0x2,   0x2,   0x110, 0x1f,
        0x3,   0x2,    0x2,    0x2,    0x111,  0x112,  0x7,    0xf,    0x2,    0x2,   0x112, 0x113, 0x7,   0x54,  0x2,
        0x2,   0x113,  0x114,  0x7,    0x3,    0x2,    0x2,    0x114,  0x115,  0x5,   0x6c,  0x37,  0x2,   0x115, 0x116,
        0x5,   0x4e,   0x28,   0x2,    0x116,  0x117,  0x7,    0x55,   0x2,    0x2,   0x117, 0x21,  0x3,   0x2,   0x2,
        0x2,   0x118,  0x119,  0x7,    0x10,   0x2,    0x2,    0x119,  0x11a,  0x7,   0x54,  0x2,   0x2,   0x11a, 0x11b,
        0x7,   0x55,   0x2,    0x2,    0x11b,  0x23,   0x3,    0x2,    0x2,    0x2,   0x11c, 0x11d, 0x5,   0x36,  0x1c,
        0x2,   0x11d,  0x11e,  0x5,    0x26,   0x14,   0x2,    0x11e,  0x11f,  0x5,   0x36,  0x1c,  0x2,   0x11f, 0x120,
        0x7,   0x55,   0x2,    0x2,    0x120,  0x25,   0x3,    0x2,    0x2,    0x2,   0x121, 0x125, 0x7,   0x11,  0x2,
        0x2,   0x122,  0x125,  0x7,    0x12,   0x2,    0x2,    0x123,  0x125,  0x7,   0x13,  0x2,   0x2,   0x124, 0x121,
        0x3,   0x2,    0x2,    0x2,    0x124,  0x122,  0x3,    0x2,    0x2,    0x2,   0x124, 0x123, 0x3,   0x2,   0x2,
        0x2,   0x125,  0x27,   0x3,    0x2,    0x2,    0x2,    0x126,  0x128,  0x7,   0x14,  0x2,   0x2,   0x127, 0x129,
        0x7,   0x52,   0x2,    0x2,    0x128,  0x127,  0x3,    0x2,    0x2,    0x2,   0x128, 0x129, 0x3,   0x2,   0x2,
        0x2,   0x129,  0x12a,  0x3,    0x2,    0x2,    0x2,    0x12a,  0x12b,  0x5,   0x36,  0x1c,  0x2,   0x12b, 0x12c,
        0x7,   0x55,   0x2,    0x2,    0x12c,  0x29,   0x3,    0x2,    0x2,    0x2,   0x12d, 0x12f, 0x7,   0x15,  0x2,
        0x2,   0x12e,  0x130,  0x5,    0x36,   0x1c,   0x2,    0x12f,  0x12e,  0x3,   0x2,   0x2,   0x2,   0x12f, 0x130,
        0x3,   0x2,    0x2,    0x2,    0x130,  0x131,  0x3,    0x2,    0x2,    0x2,   0x131, 0x132, 0x7,   0x55,  0x2,
        0x2,   0x132,  0x2b,   0x3,    0x2,    0x2,    0x2,    0x133,  0x134,  0x7,   0x16,  0x2,   0x2,   0x134, 0x135,
        0x5,   0x36,   0x1c,   0x2,    0x135,  0x136,  0x7,    0x55,   0x2,    0x2,   0x136, 0x2d,  0x3,   0x2,   0x2,
        0x2,   0x137,  0x138,  0x7,    0x17,   0x2,    0x2,    0x138,  0x139,  0x5,   0x36,  0x1c,  0x2,   0x139, 0x13a,
        0x7,   0x18,   0x2,    0x2,    0x13a,  0x13d,  0x5,    0x16,   0xc,    0x2,   0x13b, 0x13c, 0x7,   0x19,  0x2,
        0x2,   0x13c,  0x13e,  0x5,    0x16,   0xc,    0x2,    0x13d,  0x13b,  0x3,   0x2,   0x2,   0x2,   0x13d, 0x13e,
        0x3,   0x2,    0x2,    0x2,    0x13e,  0x2f,   0x3,    0x2,    0x2,    0x2,   0x13f, 0x140, 0x7,   0x1a,  0x2,
        0x2,   0x140,  0x141,  0x5,    0x36,   0x1c,   0x2,    0x141,  0x142,  0x7,   0x1b,  0x2,   0x2,   0x142, 0x143,
        0x5,   0x16,   0xc,    0x2,    0x143,  0x31,   0x3,    0x2,    0x2,    0x2,   0x144, 0x145, 0x7,   0x1c,  0x2,
        0x2,   0x145,  0x146,  0x5,    0x36,   0x1c,   0x2,    0x146,  0x147,  0x7,   0x1d,  0x2,   0x2,   0x147, 0x14b,
        0x7,   0x6,    0x2,    0x2,    0x148,  0x14a,  0x5,    0x34,   0x1b,   0x2,   0x149, 0x148, 0x3,   0x2,   0x2,
        0x2,   0x14a,  0x14d,  0x3,    0x2,    0x2,    0x2,    0x14b,  0x149,  0x3,   0x2,   0x2,   0x2,   0x14b, 0x14c,
        0x3,   0x2,    0x2,    0x2,    0x14c,  0x14e,  0x3,    0x2,    0x2,    0x2,   0x14d, 0x14b, 0x3,   0x2,   0x2,
        0x2,   0x14e,  0x14f,  0x7,    0x7,    0x2,    0x2,    0x14f,  0x33,   0x3,   0x2,   0x2,   0x2,   0x150, 0x155,
        0x5,   0x58,   0x2d,   0x2,    0x151,  0x152,  0x7,    0x1e,   0x2,    0x2,   0x152, 0x154, 0x5,   0x58,  0x2d,
        0x2,   0x153,  0x151,  0x3,    0x2,    0x2,    0x2,    0x154,  0x157,  0x3,   0x2,   0x2,   0x2,   0x155, 0x153,
        0x3,   0x2,    0x2,    0x2,    0x155,  0x156,  0x3,    0x2,    0x2,    0x2,   0x156, 0x158, 0x3,   0x2,   0x2,
        0x2,   0x157,  0x155,  0x3,    0x2,    0x2,    0x2,    0x158,  0x159,  0x7,   0x1f,  0x2,   0x2,   0x159, 0x15a,
        0x5,   0x16,   0xc,    0x2,    0x15a,  0x15f,  0x3,    0x2,    0x2,    0x2,   0x15b, 0x15c, 0x7,   0x20,  0x2,
        0x2,   0x15c,  0x15d,  0x7,    0x1f,   0x2,    0x2,    0x15d,  0x15f,  0x5,   0x16,  0xc,   0x2,   0x15e, 0x150,
        0x3,   0x2,    0x2,    0x2,    0x15e,  0x15b,  0x3,    0x2,    0x2,    0x2,   0x15f, 0x35,  0x3,   0x2,   0x2,
        0x2,   0x160,  0x161,  0x8,    0x1c,   0x1,    0x2,    0x161,  0x178,  0x5,   0x46,  0x24,  0x2,   0x162, 0x178,
        0x5,   0x48,   0x25,   0x2,    0x163,  0x178,  0x5,    0x58,   0x2d,   0x2,   0x164, 0x178, 0x5,   0x4c,  0x27,
        0x2,   0x165,  0x178,  0x5,    0x4e,   0x28,   0x2,    0x166,  0x178,  0x5,   0x50,  0x29,  0x2,   0x167, 0x178,
        0x5,   0x52,   0x2a,   0x2,    0x168,  0x178,  0x5,    0x40,   0x21,   0x2,   0x169, 0x16a, 0x7,   0x4,   0x2,
        0x2,   0x16a,  0x16b,  0x5,    0x36,   0x1c,   0x2,    0x16b,  0x16c,  0x7,   0x5,   0x2,   0x2,   0x16c, 0x178,
        0x3,   0x2,    0x2,    0x2,    0x16d,  0x16e,  0x7,    0x24,   0x2,    0x2,   0x16e, 0x178, 0x5,   0x36,  0x1c,
        0xb,   0x16f,  0x170,  0x7,    0x17,   0x2,    0x2,    0x170,  0x171,  0x5,   0x36,  0x1c,  0x2,   0x171, 0x172,
        0x7,   0x18,   0x2,    0x2,    0x172,  0x173,  0x5,    0x36,   0x1c,   0x2,   0x173, 0x174, 0x7,   0x19,  0x2,
        0x2,   0x174,  0x175,  0x5,    0x36,   0x1c,   0x4,    0x175,  0x178,  0x3,   0x2,   0x2,   0x2,   0x176, 0x178,
        0x5,   0x54,   0x2b,   0x2,    0x177,  0x160,  0x3,    0x2,    0x2,    0x2,   0x177, 0x162, 0x3,   0x2,   0x2,
        0x2,   0x177,  0x163,  0x3,    0x2,    0x2,    0x2,    0x177,  0x164,  0x3,   0x2,   0x2,   0x2,   0x177, 0x165,
        0x3,   0x2,    0x2,    0x2,    0x177,  0x166,  0x3,    0x2,    0x2,    0x2,   0x177, 0x167, 0x3,   0x2,   0x2,
        0x2,   0x177,  0x168,  0x3,    0x2,    0x2,    0x2,    0x177,  0x169,  0x3,   0x2,   0x2,   0x2,   0x177, 0x16d,
        0x3,   0x2,    0x2,    0x2,    0x177,  0x16f,  0x3,    0x2,    0x2,    0x2,   0x177, 0x176, 0x3,   0x2,   0x2,
        0x2,   0x178,  0x19a,  0x3,    0x2,    0x2,    0x2,    0x179,  0x17a,  0xc,   0xa,   0x2,   0x2,   0x17a, 0x17b,
        0x5,   0x38,   0x1d,   0x2,    0x17b,  0x17c,  0x5,    0x36,   0x1c,   0xb,   0x17c, 0x199, 0x3,   0x2,   0x2,
        0x2,   0x17d,  0x17e,  0xc,    0x9,    0x2,    0x2,    0x17e,  0x17f,  0x5,   0x3a,  0x1e,  0x2,   0x17f, 0x180,
        0x5,   0x36,   0x1c,   0xa,    0x180,  0x199,  0x3,    0x2,    0x2,    0x2,   0x181, 0x182, 0xc,   0x8,   0x2,
        0x2,   0x182,  0x183,  0x5,    0x3c,   0x1f,   0x2,    0x183,  0x184,  0x5,   0x36,  0x1c,  0x9,   0x184, 0x199,
        0x3,   0x2,    0x2,    0x2,    0x185,  0x186,  0xc,    0x7,    0x2,    0x2,   0x186, 0x187, 0x5,   0x3e,  0x20,
        0x2,   0x187,  0x188,  0x5,    0x36,   0x1c,   0x8,    0x188,  0x199,  0x3,   0x2,   0x2,   0x2,   0x189, 0x18a,
        0xc,   0x6,    0x2,    0x2,    0x18a,  0x18b,  0x7,    0x25,   0x2,    0x2,   0x18b, 0x199, 0x5,   0x36,  0x1c,
        0x7,   0x18c,  0x18d,  0xc,    0x5,    0x2,    0x2,    0x18d,  0x18e,  0x7,   0x26,  0x2,   0x2,   0x18e, 0x199,
        0x5,   0x36,   0x1c,   0x6,    0x18f,  0x190,  0xc,    0x14,   0x2,    0x2,   0x190, 0x199, 0x7,   0x21,  0x2,
        0x2,   0x191,  0x192,  0xc,    0x13,   0x2,    0x2,    0x192,  0x193,  0x7,   0x22,  0x2,   0x2,   0x193, 0x194,
        0x5,   0x36,   0x1c,   0x2,    0x194,  0x195,  0x7,    0x23,   0x2,    0x2,   0x195, 0x199, 0x3,   0x2,   0x2,
        0x2,   0x196,  0x197,  0xc,    0x12,   0x2,    0x2,    0x197,  0x199,  0x7,   0x54,  0x2,   0x2,   0x198, 0x179,
        0x3,   0x2,    0x2,    0x2,    0x198,  0x17d,  0x3,    0x2,    0x2,    0x2,   0x198, 0x181, 0x3,   0x2,   0x2,
        0x2,   0x198,  0x185,  0x3,    0x2,    0x2,    0x2,    0x198,  0x189,  0x3,   0x2,   0x2,   0x2,   0x198, 0x18c,
        0x3,   0x2,    0x2,    0x2,    0x198,  0x18f,  0x3,    0x2,    0x2,    0x2,   0x198, 0x191, 0x3,   0x2,   0x2,
        0x2,   0x198,  0x196,  0x3,    0x2,    0x2,    0x2,    0x199,  0x19c,  0x3,   0x2,   0x2,   0x2,   0x19a, 0x198,
        0x3,   0x2,    0x2,    0x2,    0x19a,  0x19b,  0x3,    0x2,    0x2,    0x2,   0x19b, 0x37,  0x3,   0x2,   0x2,
        0x2,   0x19c,  0x19a,  0x3,    0x2,    0x2,    0x2,    0x19d,  0x1a1,  0x7,   0x27,  0x2,   0x2,   0x19e, 0x1a1,
        0x7,   0x28,   0x2,    0x2,    0x19f,  0x1a1,  0x7,    0x29,   0x2,    0x2,   0x1a0, 0x19d, 0x3,   0x2,   0x2,
        0x2,   0x1a0,  0x19e,  0x3,    0x2,    0x2,    0x2,    0x1a0,  0x19f,  0x3,   0x2,   0x2,   0x2,   0x1a1, 0x39,
        0x3,   0x2,    0x2,    0x2,    0x1a2,  0x1a5,  0x7,    0x2a,   0x2,    0x2,   0x1a3, 0x1a5, 0x7,   0x2b,  0x2,
        0x2,   0x1a4,  0x1a2,  0x3,    0x2,    0x2,    0x2,    0x1a4,  0x1a3,  0x3,   0x2,   0x2,   0x2,   0x1a5, 0x3b,
        0x3,   0x2,    0x2,    0x2,    0x1a6,  0x1ab,  0x7,    0x2c,   0x2,    0x2,   0x1a7, 0x1ab, 0x7,   0x2d,  0x2,
        0x2,   0x1a8,  0x1ab,  0x7,    0x2e,   0x2,    0x2,    0x1a9,  0x1ab,  0x7,   0x2f,  0x2,   0x2,   0x1aa, 0x1a6,
        0x3,   0x2,    0x2,    0x2,    0x1aa,  0x1a7,  0x3,    0x2,    0x2,    0x2,   0x1aa, 0x1a8, 0x3,   0x2,   0x2,
        0x2,   0x1aa,  0x1a9,  0x3,    0x2,    0x2,    0x2,    0x1ab,  0x3d,   0x3,   0x2,   0x2,   0x2,   0x1ac, 0x1af,
        0x7,   0x30,   0x2,    0x2,    0x1ad,  0x1af,  0x7,    0x31,   0x2,    0x2,   0x1ae, 0x1ac, 0x3,   0x2,   0x2,
        0x2,   0x1ae,  0x1ad,  0x3,    0x2,    0x2,    0x2,    0x1af,  0x3f,   0x3,   0x2,   0x2,   0x2,   0x1b0, 0x1b1,
        0x5,   0x42,   0x22,   0x2,    0x1b1,  0x41,   0x3,    0x2,    0x2,    0x2,   0x1b2, 0x1b3, 0x7,   0x54,  0x2,
        0x2,   0x1b3,  0x1b4,  0x7,    0x4,    0x2,    0x2,    0x1b4,  0x1b5,  0x5,   0x44,  0x23,  0x2,   0x1b5, 0x1b6,
        0x7,   0x5,    0x2,    0x2,    0x1b6,  0x1bd,  0x3,    0x2,    0x2,    0x2,   0x1b7, 0x1b8, 0x5,   0x6c,  0x37,
        0x2,   0x1b8,  0x1b9,  0x7,    0x4,    0x2,    0x2,    0x1b9,  0x1ba,  0x5,   0x44,  0x23,  0x2,   0x1ba, 0x1bb,
        0x7,   0x5,    0x2,    0x2,    0x1bb,  0x1bd,  0x3,    0x2,    0x2,    0x2,   0x1bc, 0x1b2, 0x3,   0x2,   0x2,
        0x2,   0x1bc,  0x1b7,  0x3,    0x2,    0x2,    0x2,    0x1bd,  0x43,   0x3,   0x2,   0x2,   0x2,   0x1be, 0x1c3,
        0x5,   0x36,   0x1c,   0x2,    0x1bf,  0x1c0,  0x7,    0x9,    0x2,    0x2,   0x1c0, 0x1c2, 0x5,   0x36,  0x1c,
        0x2,   0x1c1,  0x1bf,  0x3,    0x2,    0x2,    0x2,    0x1c2,  0x1c5,  0x3,   0x2,   0x2,   0x2,   0x1c3, 0x1c1,
        0x3,   0x2,    0x2,    0x2,    0x1c3,  0x1c4,  0x3,    0x2,    0x2,    0x2,   0x1c4, 0x1c7, 0x3,   0x2,   0x2,
        0x2,   0x1c5,  0x1c3,  0x3,    0x2,    0x2,    0x2,    0x1c6,  0x1be,  0x3,   0x2,   0x2,   0x2,   0x1c6, 0x1c7,
        0x3,   0x2,    0x2,    0x2,    0x1c7,  0x45,   0x3,    0x2,    0x2,    0x2,   0x1c8, 0x1c9, 0x7,   0x54,  0x2,
        0x2,   0x1c9,  0x47,   0x3,    0x2,    0x2,    0x2,    0x1ca,  0x1cf,  0x7,   0x32,  0x2,   0x2,   0x1cb, 0x1cc,
        0x7,   0x22,   0x2,    0x2,    0x1cc,  0x1cd,  0x5,    0x36,   0x1c,   0x2,   0x1cd, 0x1ce, 0x7,   0x23,  0x2,
        0x2,   0x1ce,  0x1d0,  0x3,    0x2,    0x2,    0x2,    0x1cf,  0x1cb,  0x3,   0x2,   0x2,   0x2,   0x1cf, 0x1d0,
        0x3,   0x2,    0x2,    0x2,    0x1d0,  0x1d1,  0x3,    0x2,    0x2,    0x2,   0x1d1, 0x1d2, 0x5,   0x4a,  0x26,
        0x2,   0x1d2,  0x1d3,  0x5,    0x6c,   0x37,   0x2,    0x1d3,  0x49,   0x3,   0x2,   0x2,   0x2,   0x1d4, 0x1d7,
        0x7,   0x33,   0x2,    0x2,    0x1d5,  0x1d7,  0x7,    0x34,   0x2,    0x2,   0x1d6, 0x1d4, 0x3,   0x2,   0x2,
        0x2,   0x1d6,  0x1d5,  0x3,    0x2,    0x2,    0x2,    0x1d7,  0x4b,   0x3,   0x2,   0x2,   0x2,   0x1d8, 0x1d9,
        0x7,   0x35,   0x2,    0x2,    0x1d9,  0x1da,  0x5,    0x36,   0x1c,   0x2,   0x1da, 0x4d,  0x3,   0x2,   0x2,
        0x2,   0x1db,  0x1dc,  0x7,    0x36,   0x2,    0x2,    0x1dc,  0x1e1,  0x5,   0x36,  0x1c,  0x2,   0x1dd, 0x1de,
        0x7,   0x36,   0x2,    0x2,    0x1de,  0x1df,  0x7,    0x37,   0x2,    0x2,   0x1df, 0x1e1, 0x5,   0x36,  0x1c,
        0x2,   0x1e0,  0x1db,  0x3,    0x2,    0x2,    0x2,    0x1e0,  0x1dd,  0x3,   0x2,   0x2,   0x2,   0x1e1, 0x4f,
        0x3,   0x2,    0x2,    0x2,    0x1e2,  0x1e3,  0x7,    0x38,   0x2,    0x2,   0x1e3, 0x1e4, 0x5,   0x6c,  0x37,
        0x2,   0x1e4,  0x51,   0x3,    0x2,    0x2,    0x2,    0x1e5,  0x1e6,  0x7,   0x38,  0x2,   0x2,   0x1e6, 0x1e7,
        0x7,   0x4,    0x2,    0x2,    0x1e7,  0x1e8,  0x5,    0x36,   0x1c,   0x2,   0x1e8, 0x1e9, 0x7,   0x5,   0x2,
        0x2,   0x1e9,  0x53,   0x3,    0x2,    0x2,    0x2,    0x1ea,  0x1eb,  0x7,   0x1c,  0x2,   0x2,   0x1eb, 0x1ec,
        0x5,   0x36,   0x1c,   0x2,    0x1ec,  0x1ed,  0x7,    0x1d,   0x2,    0x2,   0x1ed, 0x1f6, 0x7,   0x6,   0x2,
        0x2,   0x1ee,  0x1f3,  0x5,    0x56,   0x2c,   0x2,    0x1ef,  0x1f0,  0x7,   0x9,   0x2,   0x2,   0x1f0, 0x1f2,
        0x5,   0x56,   0x2c,   0x2,    0x1f1,  0x1ef,  0x3,    0x2,    0x2,    0x2,   0x1f2, 0x1f5, 0x3,   0x2,   0x2,
        0x2,   0x1f3,  0x1f1,  0x3,    0x2,    0x2,    0x2,    0x1f3,  0x1f4,  0x3,   0x2,   0x2,   0x2,   0x1f4, 0x1f7,
        0x3,   0x2,    0x2,    0x2,    0x1f5,  0x1f3,  0x3,    0x2,    0x2,    0x2,   0x1f6, 0x1ee, 0x3,   0x2,   0x2,
        0x2,   0x1f6,  0x1f7,  0x3,    0x2,    0x2,    0x2,    0x1f7,  0x1f8,  0x3,   0x2,   0x2,   0x2,   0x1f8, 0x1f9,
        0x7,   0x7,    0x2,    0x2,    0x1f9,  0x55,   0x3,    0x2,    0x2,    0x2,   0x1fa, 0x1ff, 0x5,   0x58,  0x2d,
        0x2,   0x1fb,  0x1fc,  0x7,    0x1e,   0x2,    0x2,    0x1fc,  0x1fe,  0x5,   0x58,  0x2d,  0x2,   0x1fd, 0x1fb,
        0x3,   0x2,    0x2,    0x2,    0x1fe,  0x201,  0x3,    0x2,    0x2,    0x2,   0x1ff, 0x1fd, 0x3,   0x2,   0x2,
        0x2,   0x1ff,  0x200,  0x3,    0x2,    0x2,    0x2,    0x200,  0x202,  0x3,   0x2,   0x2,   0x2,   0x201, 0x1ff,
        0x3,   0x2,    0x2,    0x2,    0x202,  0x203,  0x7,    0x1f,   0x2,    0x2,   0x203, 0x204, 0x5,   0x36,  0x1c,
        0x2,   0x204,  0x209,  0x3,    0x2,    0x2,    0x2,    0x205,  0x206,  0x7,   0x20,  0x2,   0x2,   0x206, 0x207,
        0x7,   0x1f,   0x2,    0x2,    0x207,  0x209,  0x5,    0x36,   0x1c,   0x2,   0x208, 0x1fa, 0x3,   0x2,   0x2,
        0x2,   0x208,  0x205,  0x3,    0x2,    0x2,    0x2,    0x209,  0x57,   0x3,   0x2,   0x2,   0x2,   0x20a, 0x212,
        0x5,   0x5a,   0x2e,   0x2,    0x20b,  0x212,  0x5,    0x5c,   0x2f,   0x2,   0x20c, 0x212, 0x5,   0x5e,  0x30,
        0x2,   0x20d,  0x212,  0x5,    0x64,   0x33,   0x2,    0x20e,  0x212,  0x5,   0x66,  0x34,  0x2,   0x20f, 0x212,
        0x5,   0x68,   0x35,   0x2,    0x210,  0x212,  0x5,    0x6a,   0x36,   0x2,   0x211, 0x20a, 0x3,   0x2,   0x2,
        0x2,   0x211,  0x20b,  0x3,    0x2,    0x2,    0x2,    0x211,  0x20c,  0x3,   0x2,   0x2,   0x2,   0x211, 0x20d,
        0x3,   0x2,    0x2,    0x2,    0x211,  0x20e,  0x3,    0x2,    0x2,    0x2,   0x211, 0x20f, 0x3,   0x2,   0x2,
        0x2,   0x211,  0x210,  0x3,    0x2,    0x2,    0x2,    0x212,  0x59,   0x3,   0x2,   0x2,   0x2,   0x213, 0x215,
        0x7,   0x54,   0x2,    0x2,    0x214,  0x213,  0x3,    0x2,    0x2,    0x2,   0x214, 0x215, 0x3,   0x2,   0x2,
        0x2,   0x215,  0x216,  0x3,    0x2,    0x2,    0x2,    0x216,  0x217,  0x7,   0x4f,  0x2,   0x2,   0x217, 0x5b,
        0x3,   0x2,    0x2,    0x2,    0x218,  0x219,  0x7,    0x50,   0x2,    0x2,   0x219, 0x5d,  0x3,   0x2,   0x2,
        0x2,   0x21a,  0x21d,  0x5,    0x60,   0x31,   0x2,    0x21b,  0x21d,  0x5,   0x62,  0x32,  0x2,   0x21c, 0x21a,
        0x3,   0x2,    0x2,    0x2,    0x21c,  0x21b,  0x3,    0x2,    0x2,    0x2,   0x21d, 0x5f,  0x3,   0x2,   0x2,
        0x2,   0x21e,  0x221,  0x7,    0x51,   0x2,    0x2,    0x21f,  0x221,  0x7,   0x46,  0x2,   0x2,   0x220, 0x21e,
        0x3,   0x2,    0x2,    0x2,    0x220,  0x21f,  0x3,    0x2,    0x2,    0x2,   0x221, 0x224, 0x3,   0x2,   0x2,
        0x2,   0x222,  0x223,  0x7,    0x3,    0x2,    0x2,    0x223,  0x225,  0x7,   0x51,  0x2,   0x2,   0x224, 0x222,
        0x3,   0x2,    0x2,    0x2,    0x224,  0x225,  0x3,    0x2,    0x2,    0x2,   0x225, 0x61,  0x3,   0x2,   0x2,
        0x2,   0x226,  0x227,  0x7,    0x47,   0x2,    0x2,    0x227,  0x228,  0x7,   0x3,   0x2,   0x2,   0x228, 0x230,
        0x7,   0x51,   0x2,    0x2,    0x229,  0x22a,  0x7,    0x48,   0x2,    0x2,   0x22a, 0x22b, 0x7,   0x3,   0x2,
        0x2,   0x22b,  0x230,  0x7,    0x51,   0x2,    0x2,    0x22c,  0x22d,  0x7,   0x49,  0x2,   0x2,   0x22d, 0x22e,
        0x7,   0x3,    0x2,    0x2,    0x22e,  0x230,  0x7,    0x51,   0x2,    0x2,   0x22f, 0x226, 0x3,   0x2,   0x2,
        0x2,   0x22f,  0x229,  0x3,    0x2,    0x2,    0x2,    0x22f,  0x22c,  0x3,   0x2,   0x2,   0x2,   0x230, 0x63,
        0x3,   0x2,    0x2,    0x2,    0x231,  0x232,  0x9,    0x2,    0x2,    0x2,   0x232, 0x65,  0x3,   0x2,   0x2,
        0x2,   0x233,  0x236,  0x7,    0x39,   0x2,    0x2,    0x234,  0x236,  0x7,   0x3a,  0x2,   0x2,   0x235, 0x233,
        0x3,   0x2,    0x2,    0x2,    0x235,  0x234,  0x3,    0x2,    0x2,    0x2,   0x236, 0x67,  0x3,   0x2,   0x2,
        0x2,   0x237,  0x238,  0x7,    0x51,   0x2,    0x2,    0x238,  0x239,  0x7,   0x3,   0x2,   0x2,   0x239, 0x23a,
        0x7,   0x3b,   0x2,    0x2,    0x23a,  0x69,   0x3,    0x2,    0x2,    0x2,   0x23b, 0x23c, 0x7,   0x46,  0x2,
        0x2,   0x23c,  0x23d,  0x7,    0x3,    0x2,    0x2,    0x23d,  0x23e,  0x7,   0x3c,  0x2,   0x2,   0x23e, 0x6b,
        0x3,   0x2,    0x2,    0x2,    0x23f,  0x248,  0x5,    0x6e,   0x38,   0x2,   0x240, 0x248, 0x5,   0x70,  0x39,
        0x2,   0x241,  0x248,  0x5,    0x72,   0x3a,   0x2,    0x242,  0x243,  0x7,   0x27,  0x2,   0x2,   0x243, 0x248,
        0x5,   0x6c,   0x37,   0x2,    0x244,  0x245,  0x7,    0x3d,   0x2,    0x2,   0x245, 0x248, 0x5,   0x6c,  0x37,
        0x2,   0x246,  0x248,  0x5,    0x7c,   0x3f,   0x2,    0x247,  0x23f,  0x3,   0x2,   0x2,   0x2,   0x247, 0x240,
        0x3,   0x2,    0x2,    0x2,    0x247,  0x241,  0x3,    0x2,    0x2,    0x2,   0x247, 0x242, 0x3,   0x2,   0x2,
        0x2,   0x247,  0x244,  0x3,    0x2,    0x2,    0x2,    0x247,  0x246,  0x3,   0x2,   0x2,   0x2,   0x248, 0x6d,
        0x3,   0x2,    0x2,    0x2,    0x249,  0x24a,  0x7,    0x45,   0x2,    0x2,   0x24a, 0x6f,  0x3,   0x2,   0x2,
        0x2,   0x24b,  0x24c,  0x7,    0x22,   0x2,    0x2,    0x24c,  0x24d,  0x5,   0x6c,  0x37,  0x2,   0x24d, 0x24e,
        0x7,   0x55,   0x2,    0x2,    0x24e,  0x24f,  0x7,    0x51,   0x2,    0x2,   0x24f, 0x250, 0x7,   0x23,  0x2,
        0x2,   0x250,  0x71,   0x3,    0x2,    0x2,    0x2,    0x251,  0x256,  0x5,   0x74,  0x3b,  0x2,   0x252, 0x256,
        0x5,   0x76,   0x3c,   0x2,    0x253,  0x256,  0x5,    0x78,   0x3d,   0x2,   0x254, 0x256, 0x5,   0x7a,  0x3e,
        0x2,   0x255,  0x251,  0x3,    0x2,    0x2,    0x2,    0x255,  0x252,  0x3,   0x2,   0x2,   0x2,   0x255, 0x253,
        0x3,   0x2,    0x2,    0x2,    0x255,  0x254,  0x3,    0x2,    0x2,    0x2,   0x256, 0x73,  0x3,   0x2,   0x2,
        0x2,   0x257,  0x258,  0x9,    0x3,    0x2,    0x2,    0x258,  0x75,   0x3,   0x2,   0x2,   0x2,   0x259, 0x25a,
        0x9,   0x4,    0x2,    0x2,    0x25a,  0x77,   0x3,    0x2,    0x2,    0x2,   0x25b, 0x25c, 0x7,   0x43,  0x2,
        0x2,   0x25c,  0x79,   0x3,    0x2,    0x2,    0x2,    0x25d,  0x25e,  0x7,   0x44,  0x2,   0x2,   0x25e, 0x7b,
        0x3,   0x2,    0x2,    0x2,    0x25f,  0x260,  0x7,    0x54,   0x2,    0x2,   0x260, 0x7d,  0x3,   0x2,   0x2,
        0x2,   0x35,   0x81,   0x83,   0x8a,   0x92,   0x9d,   0xa3,   0xaf,   0xb3,  0xba,  0xbd,  0xc5,  0xd5,  0xe1,
        0xe7,  0xeb,   0xf1,   0x101,  0x10d,  0x124,  0x128,  0x12f,  0x13d,  0x14b, 0x155, 0x15e, 0x177, 0x198, 0x19a,
        0x1a0, 0x1a4,  0x1aa,  0x1ae,  0x1bc,  0x1c3,  0x1c6,  0x1cf,  0x1d6,  0x1e0, 0x1f3, 0x1f6, 0x1ff, 0x208, 0x211,
        0x214, 0x21c,  0x220,  0x224,  0x22f,  0x235,  0x247,  0x255,
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
