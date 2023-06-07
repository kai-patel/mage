#include "mage.h"
#include "lexer.h"
#include <stdint.h>
#include <stdio.h>

extern Lexer *lexer_new(const char *);
extern Token *lexer_next(Lexer *);

