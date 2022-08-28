
// Generated from ./src/management/grammar/data.g4 by ANTLR 4.10.1

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

    explicit dataParser(antlr4::TokenStream* input);

    dataParser(antlr4::TokenStream* input, const antlr4::atn::ParserATNSimulatorOptions& options);

    ~dataParser() override;

    std::string getGrammarFileName() const override;

    const antlr4::atn::ATN& getATN() const override;

    const std::vector<std::string>& getRuleNames() const override;

    const antlr4::dfa::Vocabulary& getVocabulary() const override;

    antlr4::atn::SerializedATNView getSerializedATN() const override;

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

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ElementContext* element();

    class DictionaryContext : public antlr4::ParserRuleContext
    {
      public:
        DictionaryContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t             getRuleIndex() const override;
        std::vector<EntryContext*> entry();
        EntryContext*              entry(size_t i);

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

  DictionaryContext* dictionary();

  class EntryContext : public antlr4::ParserRuleContext
  {
    public:
      dataParser::ElementContext* value = nullptr;
      EntryContext(antlr4::ParserRuleContext* parent, size_t invokingState);
      virtual size_t              getRuleIndex() const override;
      antlr4::tree::TerminalNode* KEY();
      ElementContext*             element();

      virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
  };

  EntryContext* entry();

  class ListContext : public antlr4::ParserRuleContext
  {
    public:
      ListContext(antlr4::ParserRuleContext* parent, size_t invokingState);
      virtual size_t               getRuleIndex() const override;
      std::vector<ElementContext*> element();
      ElementContext*              element(size_t i);

      virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
  };

  ListContext* list();

  class StringContext : public antlr4::ParserRuleContext
  {
    public:
      StringContext(antlr4::ParserRuleContext* parent, size_t invokingState);
      virtual size_t              getRuleIndex() const override;
      antlr4::tree::TerminalNode* STRING();

      virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
  };

  StringContext* string();

  class  BooleanContext : public antlr4::ParserRuleContext {
  public:
    BooleanContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    BooleanContext() = default;
    void copyFrom(BooleanContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class TrueContext : public BooleanContext
  {
    public:
      TrueContext(BooleanContext* ctx);

      virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
  };

  class FalseContext : public BooleanContext
  {
    public:
      FalseContext(BooleanContext* ctx);

      virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
  };

  BooleanContext* boolean();

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

