#ifndef LEXER_H_
#define LEXER_H_
typedef enum {
  Token_Eof = 0,
  Token_Illegal,
  Token_Ident,
  Token_Int,
  Token_Assign,
  Token_Plus,
  Token_Minus,
  Token_Bang,
  Token_Asterisk,
  Token_Slash,
  Token_LT,
  Token_GT,
  Token_Equal,
  Token_NotEqual,
  Token_Comma,
  Token_Semicolon,
  Token_LParen,
  Token_RParen,
  Token_LCurly,
  Token_RCurly,
  Token_Function,
  Token_Let,
  Token_True,
  Token_False,
  Token_If,
  Token_Else,
  Token_While,
  Token_Return,
} TokenType;

typedef struct {
  TokenType type;
  char *lexeme;
} Token;

typedef struct LexerStruct Lexer;

Lexer *lexer_new(const char *);
Token *lexer_next(Lexer *);
TokenType lexer_next_type(Lexer *);
#endif
