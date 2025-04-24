#include <stdio.h>

#ifndef LEX_H
#define LEX_H

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define COLON 12
#define SEMICOLON 13
#define DEC_OP 14
#define INC_OP 15
#define POW_OP 16

#define ASSIGN_OP 17
#define LESSER_OP 18
#define GREATER_OP 19
#define EQUAL_OP 20
#define NEQUAL_OP 21
#define LEQUAL_OP 22
#define GEQUAL_OP 23

#define ADD_OP 24
#define SUB_OP 25
#define MULT_OP 26
#define DIV_OP 27
#define LEFT_PAREN 28
#define RIGHT_PAREN 29

#define KEY_READ 30
#define KEY_PRINT 31
#define KEY_IF 32
#define KEY_ELSE 33
#define KEY_BEGIN 34
#define KEY_END 35


// Global variables to be used in both lex.c and parser.c
extern int nextToken;
extern int lineNumber;
extern char lexeme[100];


/* Function prototype for lex.c */
int lex();
void initLexer(FILE *input);
const char* tokenString(int token);

#endif
