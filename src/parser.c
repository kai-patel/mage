#include "lexer.h"
#include <parser.h>
#include <stdio.h>
#include <stdlib.h>

struct ParserStruct {
  Lexer *lexer;
  Node *root;
};

Node *node_new(ASTType type) {
  Node *node = malloc(sizeof(*node));
  if (node == NULL) {
    perror("Could not create new node");
    exit(1);
  }

  node->type = type;
  return node;
}

Parser *parser_new(char *input) {
  Parser *parser = malloc(sizeof(*parser));
  if (parser == NULL) {
    perror("Could not create parser");
    exit(1);
  }

  parser->lexer = lexer_new(input);
  parser->root = node_new(AST_Empty);

  return parser;
}

void add_node(Parser *parser, Node *node) {
  Node *curr = parser->root;
  while (curr && curr->left) {
    curr = curr->left;
  }

  curr->left = node;
}

Node *parser_parse_tree(Parser *parser) {

  for (Token *token = lexer_next(parser->lexer); token->type != Token_Eof;
       token = lexer_next(parser->lexer)) {
    switch (token->type) {
    case Token_Illegal: {
      fprintf(stderr, "Illegal token found %s", token->lexeme);
      exit(1);
    } break;
    case Token_Eof: {
      fprintf(stderr, "Unexpected EOF %s", token->lexeme);
      exit(1);
    } break;
    case Token_Ident: {
    } break;
    case Token_Int: {
    } break;
    case Token_Assign: {
    } break;
    case Token_Plus: {
    } break;
    case Token_Minus: {
    } break;
    case Token_Bang: {
    } break;
    case Token_Asterisk: {
    } break;
    case Token_Slash: {
    } break;
    case Token_LT: {
    } break;
    case Token_GT: {
    } break;
    case Token_Equal: {
    } break;
    case Token_NotEqual: {
    } break;
    case Token_Comma: {
    } break;
    case Token_Semicolon: {
    } break;
    case Token_LParen: {
    } break;
    case Token_RParen: {
    } break;
    case Token_LCurly: {
    } break;
    case Token_RCurly: {
    } break;
    case Token_Function: {
    } break;
    case Token_Let: {
    } break;
    case Token_True: {
    } break;
    case Token_False: {
    } break;
    case Token_If: {
    } break;
    case Token_Else: {
    } break;
    case Token_While: {
    } break;
    case Token_Return: {
    } break;
    }
  }

  return parser->root;
}
