#include <stdio.h>
#include <ctype.h>

#include "lex.h"

/* Global Variable */
int nextToken;
int lineNumber = 1;
char lexeme[100];

/* Local Variables */
static int charClass; 
static char nextChar;
static int lexLen;
static FILE *in_fp;

/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();

const char* tokenString(int token) 
{
    switch (token) 
    {
        case 10: return "INT_LIT";
        case 11: return "IDENT";
        case 12: return "COLON";
        case 13: return "SEMICOLON";
        case 14: return "DEC_OP";
        case 15: return "INC_OP";
        case 16: return "POW_OP";

        case 17: return "ASSIGN_OP";
        case 18: return "LESSER_OP";
        case 19: return "GREATER_OP";
        case 20: return "EQUAL_OP";
        case 21: return "NEQUAL_OP";
        case 22: return "LEQUAL_OP";
        case 23: return "GEQUAL_OP";

        case 24: return "ADD_OP";
        case 25: return "SUB_OP";
        case 26: return "MULT_OP";
        case 27: return "DIV_OP";
        case 28: return "LEFT_PAREN";
        case 29: return "RIGHT_PAREN";

        case 30: return "KEY_READ";
        case 31: return "KEY_PRINT";
        case 32: return "KEY_IF";
        case 33: return "KEY_ELSE";
        case 34: return "KEY_BEGIN";
        case 35: return "KEY_END";

        case 99: return "UNKNOWN";
         
        default: return "UNKNOWN";
    }
}

// Function to Initialize global variables and to start getting characters from file
void initLexer(FILE *input) {
    in_fp = input;
    lineNumber = 1;
    lexLen = 0;
    nextToken = 0;
    charClass = UNKNOWN;
    getChar();
}


/* Function to handle characters and token assignment to the respective lexemes */
static int lookup(char ch) 
{
    switch (ch) 
    {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            getChar();
            if (nextChar == '+')
            {
                addChar();
                nextToken = INC_OP;
            }
            else
            {
                ungetc(nextChar, in_fp);
	            nextToken = ADD_OP;
            }
            break;
        case '-':
            addChar();
            getChar();
            if (nextChar == '-')
            {
                addChar();
                nextToken = DEC_OP;
            }
            else
            {
	           ungetc(nextChar, in_fp);	    
               nextToken = SUB_OP;
            }
            break;
        case '*':
            addChar();
            getChar();
            if (nextChar == '*')
            {
                addChar();
                nextToken = POW_OP;
            }
            else
            {
	            ungetc(nextChar, in_fp);
                nextToken = MULT_OP;
            }   
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case ';':
            addChar();
            nextToken = SEMICOLON;
            break;
        case ':':
            addChar();
            getChar();
            if (nextChar == '=')
            {
                addChar();
                nextToken = ASSIGN_OP;
            }
            else
            {
	           ungetc(nextChar, in_fp);	    
               nextToken = COLON;
            }
            break;
        case '<':
            addChar();
            getChar();
            if (nextChar == '>')
            {
                addChar();
                nextToken = NEQUAL_OP;
            }
            else if (nextChar == '=')
            {
                addChar();
                nextToken = LEQUAL_OP;
            }
            else
            {
	            ungetc(nextChar, in_fp);
                nextToken = LESSER_OP;
            }
            break;
        case '>':
            addChar();
            getChar();
            if (nextChar == '=')
            {
                addChar();
                nextToken = GEQUAL_OP;
            }
            else
            {
                ungetc(nextChar, in_fp);
                nextToken = GREATER_OP;
            }
            break;
        case '=':
            addChar();
            nextToken = EQUAL_OP;
            break;
        default:
            addChar();
            nextToken = UNKNOWN;
            break;
    }
    return nextToken;
}

/* Function definition to add a character to the lexeme */
static void addChar() 
{
    if (lexLen <= 98) 
    {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } 
    else 
    {
        printf("Error - lexeme is too long \n");
    }
}

/* Function definition to get next character from source code */
static void getChar() 
{
    if ((nextChar = getc(in_fp)) != EOF) 
    {
        if (nextChar == '\n') 
        {
            charClass = UNKNOWN;  
        }
        if (isalpha(nextChar)) 
        {
            charClass = LETTER;
        }
        else if (isdigit(nextChar)) 
        {
            charClass = DIGIT;
        } 
        else 
        {
            charClass = UNKNOWN;
        }
    } 
    else 
    {
        charClass = EOF;
    }
}



/* Function to skip whitespace characters and increment line number for new line */
static void getNonBlank() 
{
    while (isspace(nextChar)) 
    {
        if (nextChar == '\n') 
        {
            lineNumber++;  
        }
        getChar();
    }
}

/* The main lexical analysis and printing output function */
int lex() 
{
    lexLen = 0;
    getNonBlank();

    switch (charClass) 
    {
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) 
            {
                addChar();
                getChar();
            }            
            if(lexeme[0] =='r'&&lexeme[1] =='e'&&lexeme[2] =='a'&&lexeme[3]=='d'&&lexeme[4] ==0)
            {
            nextToken = KEY_READ;
            }
            else if(lexeme[0] =='p'&&lexeme[1] =='r'&&lexeme[2] =='i'&&lexeme[3] =='n'&&lexeme[4]=='t'&&lexeme[5]==0)
            {
            nextToken = KEY_PRINT;
            }
            else if(lexeme[0] =='i'&&lexeme[1] =='f'&&lexeme[2] ==0)
            {
            nextToken = KEY_IF;
            }
            else if(lexeme[0] =='e'&&lexeme[1] =='l'&&lexeme[2] =='s'&&lexeme[3] =='e'&&lexeme[4]==0)
            {
            nextToken = KEY_ELSE;
            }
            else if(lexeme[0] =='b'&&lexeme[1] =='e'&&lexeme[2] =='g'&&lexeme[3] =='i'&&lexeme[4]=='n'&&lexeme[5]==0)
            {
            nextToken = KEY_BEGIN;
            }
            else if(lexeme[0] =='e'&&lexeme[1] =='n'&&lexeme[2] =='d'&&lexeme[3] ==0)
            {
            nextToken = KEY_END;
            }
            else
            {
                nextToken = IDENT; 
            }
            break;

        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) 
            {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;

        case EOF:
            nextToken = EOF;
            lexeme[0] = '\0';
            break;
    }
    return nextToken;
} 
