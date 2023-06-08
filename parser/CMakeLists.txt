find_package(bison REQUIRED)

bison_target(BisonParser "parser.y" "../src/parser.c"
             DEFINES_FILE "../include/parser.h")
