
#include "wci/intermediate/TypeSpec.h"
using namespace wci::intermediate;


// Generated from Pcl2.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"




class  Pcl2Lexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, PROGRAM = 10, VAR = 11, BEGIN = 12, END = 13, PRINTF = 14, 
    IS = 15, QM = 16, ISNT = 17, KEEP = 18, GOING = 19, DEF = 20, CALL = 21, 
    IDENTIFIER = 22, INTEGER = 23, FLOAT = 24, MUL_OP = 25, DIV_OP = 26, 
    ADD_OP = 27, SUB_OP = 28, EQ_OP = 29, GT_OP = 30, LT_OP = 31, NE_OP = 32, 
    GE_OP = 33, LE_OP = 34, NEWLINE = 35, WS = 36, LINE_COMMENT = 37, COMMENT = 38, 
    QUOTE = 39, STRING = 40
  };

  Pcl2Lexer(antlr4::CharStream *input);
  ~Pcl2Lexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

