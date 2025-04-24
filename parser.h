#ifndef PARSER_H
#define PARSER_H

#include "lex.h"

/* Function declarations for parser.c program */
void program();
void statement();
void condition();
void expr();
void term();
void factor();
void error();


#endif
