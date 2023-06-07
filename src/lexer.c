#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <lexer.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static void ignore_whitespace(Lexer *lexer) {
  while (isblank(lexer->ch)) {
    step(lexer);
  }
  return;
}

static size_t read_identifier_length(Lexer *lexer) {
  size_t start_pos = lexer->position;

  while (isalnum(lexer->ch) || lexer->ch == '_') {
    step(lexer);
  }

  return lexer->position - start_pos;
}

static TokenType identifier_to_type(const char *identifier) {
  if (strcmp(identifier, "defn") == 0) {
    return Token_Function;
  }
  if (strcmp(identifier, "let") == 0) {
    return Token_Let;
  }
  if (strcmp(identifier, "true") == 0) {
    return Token_True;
  }
  if (strcmp(identifier, "false") == 0) {
    return Token_False;
  }
  if (strcmp(identifier, "if") == 0) {
    return Token_If;
  }
  if (strcmp(identifier, "else") == 0) {
    return Token_Else;
  }
  if (strcmp(identifier, "while") == 0) {
    return Token_While;
  }
  if (strcmp(identifier, "return") == 0) {
    return Token_Return;
  }

  return Token_Ident;
}

static char *identifier_to_lexeme(const char *identifier, TokenType t) {
  if (t == Token_Ident) {
    return (char *)identifier;
  }
  return NULL;
}

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
  if (lexer->position > 0 && lexer->ch == '\0') {
    return make_token(Token_Eof, NULL);
  }

  step(lexer);
  Token *token = NULL;

  ignore_whitespace(lexer);
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

  // String Tokens
  if (isalpha(c) || c == '_') {
    size_t len = read_identifier_length(lexer);
    char *identifier = malloc(sizeof(*identifier) * len + 1);
    const char *start_of_ident = &lexer->input[lexer->position - len - 1];

    if (identifier == NULL) {
      perror("Could not create identifier");
      exit(1);
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    char *result = strncpy(identifier, start_of_ident, len);
#pragma clang diagnostic pop

    if (result != 0) {
      perror("Could not copy identifier string");
      exit(1);
    }

    TokenType id_type = identifier_to_type(identifier);
    char *id_lexeme = identifier_to_lexeme(identifier, id_type);

    token = make_token(id_type, id_lexeme);

    return token;
  }

  if (token == NULL) {
    token = make_token(Token_Illegal, NULL);
  }

  return token;
}
