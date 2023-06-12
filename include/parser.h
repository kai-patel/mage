#ifndef PARSER_H_
#define PARSER_H_
#include <lexer.h>
#include <stdint.h>

typedef enum ASTType {
  AST_Integer,
  AST_Float,
  AST_Bool,
  AST_String,
  AST_Char,
  AST_Variable,
  AST_Function,
  AST_Application,
  AST_If,
  AST_While,
  AST_Assign,
  AST_Plus,
  AST_Minus,
  AST_Multiply,
  AST_Divide,
  AST_LT,
  AST_GT,
  AST_LEQ,
  AST_GEQ,
  AST_OpenBlock,
  AST_CloseBlock,
  AST_Empty
} ASTType;

typedef struct Node {
  ASTType type;
  union {
    uint64_t number;
    char *string;
  };
  struct Node *left;
  struct Node *right;
} Node;

typedef struct ParserStruct Parser;

Parser *parser_new(char *);
Node *parser_parse_tree(Parser *);

#endif
