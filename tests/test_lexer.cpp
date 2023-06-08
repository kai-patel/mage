#include <string.h>
extern "C" {
#include "lexer.h"
#include "mage.h"
}

#include <gtest/gtest.h>

TEST(LexerTests, SingleTokens) {
  const char *input = "+-*/!!====,;{()}";
  Token expected[] = {
      {Token_Plus, NULL},      {Token_Minus, NULL},  {Token_Asterisk, NULL},
      {Token_Slash, NULL},     {Token_Bang, NULL},   {Token_NotEqual, NULL},
      {Token_Equal, NULL},     {Token_Assign, NULL}, {Token_Comma, NULL},
      {Token_Semicolon, NULL}, {Token_LCurly, NULL}, {Token_LParen, NULL},
      {Token_RParen, NULL},    {Token_RCurly, NULL}, {Token_Eof, NULL}};

  const size_t n_expected = 15;

  Token *actual[n_expected] = {NULL};

  Lexer *lexer = lexer_new(input);
  Token *token = (Token *)malloc(sizeof(*token));
  token->type = Token_Illegal;

  size_t n_actual = 0;

  while (token && token->type != Token_Eof) {
    token = lexer_next(lexer);
    actual[n_actual++] = token;
  }

  ASSERT_EQ(n_actual, n_expected);

  for (size_t i = 0; i < n_expected; i++) {
    EXPECT_EQ(expected[i].type, actual[i]->type);
    EXPECT_EQ(expected[i].lexeme, actual[i]->lexeme);
  }

  for (size_t i = 0; i < n_actual; i++) {
    free(actual[i]);
  }

  free(token);
  free(lexer);
}

TEST(LexerTests, IdentifierTokens) {
  const char *input = "The qu_ick brown1 fox ju34_mped over the lazy dog";
  const char *expected[] = {"The",  "qu_ick", "brown1", "fox", "ju34_mped",
                            "over", "the",    "lazy",   "dog", NULL};

  const size_t n_expected = 10;

  Token *actual[n_expected] = {NULL};

  Lexer *lexer = lexer_new(input);
  Token *token = (Token *)malloc(sizeof(*token));
  token->type = Token_Illegal;

  size_t n_actual = 0;

  while (token && token->type != Token_Eof) {
    token = lexer_next(lexer);
    actual[n_actual++] = token;
  }

  ASSERT_EQ(n_actual, n_expected);

  for (size_t i = 0; i < n_expected; i++) {
    EXPECT_EQ(i == n_expected - 1 ? Token_Eof : Token_Ident, actual[i]->type);
    EXPECT_STREQ(expected[i], actual[i]->lexeme);
  }

  for (size_t i = 0; i < n_actual; i++) {
    free(actual[i]);
  }

  free(token);
  free(lexer);
}

TEST(LexerTests, NumberTokens) {
  const char *input = "1 10 2_300 45872 82_4_21";
  const char *expected[] = {"1", "10", "2_300", "45872", "82_4_21", NULL};

  const size_t n_expected = 6;

  Token *actual[n_expected] = {NULL};

  Lexer *lexer = lexer_new(input);
  Token *token = (Token *)malloc(sizeof(*token));
  token->type = Token_Illegal;

  size_t n_actual = 0;

  while (token && token->type != Token_Eof) {
    token = lexer_next(lexer);
    actual[n_actual++] = token;
  }

  ASSERT_EQ(n_actual, n_expected);

  for (size_t i = 0; i < n_expected; i++) {
    EXPECT_EQ(i == n_expected - 1 ? Token_Eof : Token_Int, actual[i]->type);
    EXPECT_STREQ(expected[i], actual[i]->lexeme);
  }

  for (size_t i = 0; i < n_actual; i++) {
    free(actual[i]);
  }

  free(token);
  free(lexer);
}
