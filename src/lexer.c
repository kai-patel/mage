#include <assert.h>
#include <ctype.h>
#include <lexer.h>
#include <stdbool.h>
#include <stdlib.h>

struct LexerStruct {
  const char *input;
  char ch;
  size_t position;
};

Lexer *lexer_new(const char *input) {
  Lexer *lexer = malloc(sizeof(*lexer));

  if (!lexer) {
    perror("Failed to create lexer");
    exit(1);
  }

  lexer->input = input;
  lexer->ch = 0;
  lexer->position = 0;

  return lexer;
}

static void step(Lexer *lexer) { lexer->ch = lexer->input[lexer->position++]; }

static char peek(Lexer *lexer) { return lexer->input[lexer->position]; }

static Token *make_token(TokenType t, char *lexeme) {
  Token *token = malloc(sizeof(*token));

  if (!token) {
    perror("Failed to create token");
    exit(1);
  }

  token->type = t;
  token->lexeme = lexeme;

  return token;
}

Token *lexer_next(Lexer *lexer) {
  step(lexer);
  Token *token = NULL;

  char c = lexer->ch;

  // Single character tokens
  switch (c) {
  case '=':
    if (peek(lexer) == '=') {
      step(lexer);
      token = make_token(Token_Equal, NULL);
    } else {
      token = make_token(Token_Assign, NULL);
    }
    break;
  case '+':
    token = make_token(Token_Plus, NULL);
    break;
  case '-':
    token = make_token(Token_Minus, NULL);
    break;
  case '!':
    if (peek(lexer) == '=') {
      step(lexer);
      token = make_token(Token_NotEqual, NULL);
    } else {
      token = make_token(Token_Bang, NULL);
    }
    break;
  case '*':
    token = make_token(Token_Asterisk, NULL);
    break;
  case '/':
    token = make_token(Token_Slash, NULL);
    break;
  case '<':
    token = make_token(Token_LT, NULL);
    break;
  case '>':
    token = make_token(Token_GT, NULL);
    break;
  case ',':
    token = make_token(Token_Comma, NULL);
    break;
  case ';':
    token = make_token(Token_Semicolon, NULL);
    break;
  case '(':
    token = make_token(Token_LParen, NULL);
    break;
  case ')':
    token = make_token(Token_RParen, NULL);
    break;
  case '{':
    token = make_token(Token_LCurly, NULL);
    break;
  case '}':
    token = make_token(Token_RCurly, NULL);
    break;
  case '\0':
    token = make_token(Token_Eof, NULL);
    break;
  }

  if (token == NULL) {
    token = make_token(Token_Illegal, NULL);
  }

  return token;
}
