
// Generated from ./src/management/grammar/data.g4 by ANTLR 4.8

#pragma once

#include "antlr4-runtime.h"

class dataParser : public antlr4::Parser
{
  public:
    enum
    {
        T__0         = 1,
        T__1         = 2,
        T__2         = 3,
        T__3         = 4,
        T__4         = 5,
        T__5         = 6,
        T__6         = 7,
        T__7         = 8,
        KEY          = 9,
        STRING       = 10,
        WHITESPACE   = 11,
        LINE_COMMENT = 12
    };

    enum
    {
        RuleElement    = 0,
        RuleDictionary = 1,
        RuleEntry      = 2,
        RuleList       = 3,
        RuleString     = 4,
        RuleBoolean    = 5
    };

    dataParser(antlr4::TokenStream* input);
    ~dataParser();

    virtual std::string                     getGrammarFileName() const override;
    virtual const antlr4::atn::ATN&         getATN() const override { return _atn; };
    virtual const std::vector<std::string>& getTokenNames() const override
    {
        return _tokenNames;
    };// deprecated: use vocabulary instead.
    virtual const std::vector<std::string>& getRuleNames() const override;
    virtual antlr4::dfa::Vocabulary&        getVocabulary() const override;

    class ElementContext;
    class DictionaryContext;
    class EntryContext;
    class ListContext;
    class StringContext;
    class BooleanContext;

    class ElementContext : public antlr4::ParserRuleContext
    {
      public:
        ElementContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t     getRuleIndex() const override;
        DictionaryContext* dictionary();
        ListContext*       list();
        StringContext*     string();
        BooleanContext*    boolean();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ElementContext* element();

    class DictionaryContext : public antlr4::ParserRuleContext
    {
      public:
        DictionaryContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t             getRuleIndex() const override;
        std::vector<EntryContext*> entry();
        EntryContext*              entry(size_t i);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    DictionaryContext* dictionary();

    class EntryContext : public antlr4::ParserRuleContext
    {
      public:
        dataParser::ElementContext* value = nullptr;
        ;
        EntryContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* KEY();
        ElementContext*             element();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    EntryContext* entry();

    class ListContext : public antlr4::ParserRuleContext
    {
      public:
        ListContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t               getRuleIndex() const override;
        std::vector<ElementContext*> element();
        ElementContext*              element(size_t i);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ListContext* list();

    class StringContext : public antlr4::ParserRuleContext
    {
      public:
        StringContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* STRING();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    StringContext* string();

    class BooleanContext : public antlr4::ParserRuleContext
    {
      public:
        BooleanContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        BooleanContext() = default;
        void copyFrom(BooleanContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class TrueContext : public BooleanContext
    {
      public:
        TrueContext(BooleanContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class FalseContext : public BooleanContext
    {
      public:
        FalseContext(BooleanContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    BooleanContext* boolean();

  private:
    static std::vector<antlr4::dfa::DFA>       _decisionToDFA;
    static antlr4::atn::PredictionContextCache _sharedContextCache;
    static std::vector<std::string>            _ruleNames;
    static std::vector<std::string>            _tokenNames;

    static std::vector<std::string> _literalNames;
    static std::vector<std::string> _symbolicNames;
    static antlr4::dfa::Vocabulary  _vocabulary;
    static antlr4::atn::ATN         _atn;
    static std::vector<uint16_t>    _serializedATN;

    struct Initializer {
        Initializer();
    };
    static Initializer _init;
};

