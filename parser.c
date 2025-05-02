#include <stdlib.h>
#include "parser.h"
#include "lex.h"

// Starting the parser P ::= S
void program()
{
    statement();
    if (nextToken != EOF) 
    {
        error();
    }
} 

// Parser for BNF rule: S ::= V := E | O | read(V) | print(E) | if C: begin S end | if C: begin S else: S end | S ; S
void statement() 
{
    if (nextToken == IDENT) 
    {
        lex(); 
        if (nextToken == ASSIGN_OP) 
        {
            lex(); 
            expr();
        } 
        else 
        {
            error();
        }
    }  
    else if (nextToken == INC_OP || nextToken == DEC_OP) 
    {
        lex(); 
        if (nextToken == IDENT) 
        {
            lex(); 
        } 
        else 
        {
            error();
        }
    } 
    else if (nextToken == KEY_READ) 
    { 
        lex(); 
        if (nextToken == LEFT_PAREN)
        {
            lex(); 
            if (nextToken == IDENT)
            {
                lex(); 
                if (nextToken == RIGHT_PAREN)
                {
                    lex(); 
                }
                else 
                {
                    error(); 
                }
            }
            else 
            {
                error(); 
            }
        }
        else 
        {
            error(); 
        }
    } 
    else if (nextToken == KEY_PRINT) 
    { 
        lex(); 
        if (nextToken == LEFT_PAREN)
        {
            lex(); 
            expr();
            if (nextToken == RIGHT_PAREN)
            {
                lex(); 
            }
            else
            {
                error(); 
            }
        }
        else
        {
            error(); 
        }
    }
    else if (nextToken == KEY_IF) 
    { 
        lex(); 
        condition();
        if (nextToken == COLON)
        {
            lex();
            if (nextToken == KEY_BEGIN) 
            {
                lex(); 
                statement();
                if (nextToken == KEY_END) 
                {
                    lex(); 
                }   
                else if (nextToken == KEY_ELSE)
                {
                    lex(); 
                    if (nextToken == COLON)
                    {
                        lex(); 
                        statement();
                        if (nextToken == KEY_END) 
                        {
                            lex(); 
                        } 
                        else
                        {
                            error(); 
                        }
                    }
                    else
                    {
                        error(); 
                    }
                }
                else 
                {
                    error(); 
                }
            } 
            else 
            {
                error();
            }
        } 
        else 
        {
            error(); 
        }
    } 
    else 
    {
        error(); 
    }
    if (nextToken == SEMICOLON) 
    { 
        lex(); 
        statement();
    }
}

// Parser for BNF rule: C ::= E < E | E > E | E = E | E <> E | E <= E | E >= E
void condition()
{
    expr();
    if (nextToken == LESSER_OP || nextToken == GREATER_OP || nextToken == EQUAL_OP || nextToken == NEQUAL_OP || nextToken == LEQUAL_OP || nextToken == GEQUAL_OP)
    {
        lex();
        expr();
    }
    else
    {
        error();
    }
}

// Parser for BNF rule: E ::= T | E + T | E - T
void expr() 
{
    term();
    while (nextToken == ADD_OP || nextToken == SUB_OP) 
    {
        lex();
        term();
    }
}

// Parser for BNF rule: T ::= F | T * F | T / F | T ** F 
void term() 
{
    factor();
    while (nextToken == MULT_OP || nextToken == DIV_OP || nextToken == POW_OP) {
            lex();
            factor();
    }
} 

// Parser for BNF rule: F ::= (E) | N | V
void factor() 
{
        if (nextToken == LEFT_PAREN) 
        {
            lex(); 
            expr();
            if (nextToken == RIGHT_PAREN) 
            {
                lex(); 
            } 
            else 
            { 
                error();
            }
        } 
        else if (nextToken == IDENT) 
        {
            lex();
        }
        else if (nextToken == INT_LIT) 
        {
            lex();
         }
        else 
        {
        error();
        }
}

// Printing out error encountered during parsing
void error() 
{
    printf("Error encounter on line %d: The next lexeme was %s and the next token was %s\n", lineNumber, lexeme, tokenString(nextToken));
    exit(1);
}

// Main Function to drive the parser and display different error messages
int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        fprintf(stderr, "Error: No input file found.\n");
        return 2;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) 
    {
        fprintf(stderr, "Error: File does not exist or cannot be opened.\n");
        return 3;
    }
    
    initLexer(inputFile);
    lex(); 
    program(); 
    if (nextToken != EOF) 
    {
        error(); 
    }
    printf("Syntax Validated\n");
    fclose(inputFile);
    return 0;
}
