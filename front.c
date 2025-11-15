/* front.c - a lexical analyzer system for simple arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "front.h"
#include "parser.h"

/* Global Variable */
int nextToken;
char lexeme [100];

/* Local Variables */
static int charClass;
static char nextChar;
static int lexLen;
static FILE *in_fp;

/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();
void printNextToken();

/******************************************************/
/* main driver */
int main(int argc, char* argv[])
{
    if (argc != 2){
      printf("Too many arguments\n");
      printf("Usage: %s <input_file>\n", argv[0]);
      return 2;
    }
    /* Open the input data file and process its contents */
    if ((in_fp = fopen(argv[1], "r")) == NULL) {
        printf("ERROR - cannot open %s \n", argv[1]);
        printf("No file or directory\n");
        return 3;
    } else {
        printf("DCooke Analyzer\n");
        getChar();
        //while (nextToken != EOF) {
            lex();
            program();
        //}
    }
    printf("Syntax Validated\n");
    fclose(in_fp);
    return 0;
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the
 * token */
static int lookup(char ch) { //Self note; this function defines what our next token is
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+': //Note: ++ is INC_OP
            addChar();
            nextChar = getc(in_fp);
            if (nextChar == '+'){
                addChar();
                nextToken = INC_OP;
            }
            else {
                ungetc(nextChar, in_fp);
                nextToken = ADD_OP;
            }
            break;
        case '-': //Note: -- is DEC_OP
            addChar();
            nextChar = getc(in_fp);
            if (nextChar == '-'){
                addChar();
                nextToken = DEC_OP;
            }
            else {
              ungetc(nextChar, in_fp);
              nextToken = SUB_OP;
            }
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case '=':
            addChar();
            nextToken = EQUAL_OP;
            break;
        case '%':
            addChar();
            nextToken = MOD_OP;
            break;
        case ';':
            addChar();
            nextToken = SEMICOLON;
            break;
        case ':':
            addChar();
            nextChar = getc(in_fp);
            if (nextChar == '='){
              addChar();
              nextToken = ASSIGN_OP;
            }
            else{
              ungetc(nextChar, in_fp);
              nextToken = COLON;
            }
            break;
        case '<':
            addChar();
            nextChar = getc(in_fp);
            if (nextChar == '>'){
              addChar();
              nextToken = NEQUAL_OP;
            } else if(nextChar == '='){
                addChar();
                nextToken = LEQUAL_OP;
            } else {
                ungetc(nextChar, in_fp);
                nextToken = LESSER_OP;
              }
            break;
        case '>':
            addChar();
            nextChar = getc(in_fp);
            if (nextChar == '='){
              addChar();
              nextToken = GEQUAL_OP;
            } else {
              ungetc(nextChar, in_fp);
              nextToken = GREATER_OP;
            }
            break;
        default:
            addChar();
            nextToken = UNKNOWN;
            break;
    }
    return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
static void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its
 * character class */
static void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace
 * character */
static void getNonBlank() {
    while (isspace(nextChar)) getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() { //Needs to incorporate read write etcc lexemes.
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        /* Parse identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            //Check if lexeme is a reserved keyword
            if (strcmp(lexeme, "read") == 0)
                nextToken = KEY_READ;
            else if (strcmp(lexeme, "write") == 0)
                nextToken = KEY_WRITE;
            else if (strcmp(lexeme, "if") == 0)
                nextToken = KEY_IF;
            else if (strcmp(lexeme, "fi") == 0)
                nextToken = KEY_FI;
            else if (strcmp(lexeme, "else") == 0)
                nextToken = KEY_ELSE;
            else if (strcmp(lexeme, "then") == 0)
                nextToken = KEY_THEN;
            else
                nextToken = IDENT;
            break;

        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        /* Parentheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;

        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    } /* End of switch */

    //printNextToken();
        /* End of switch */

    return nextToken;
} /* End of function lex */

void printNextToken(){

  if (nextToken != EOF){
      //printf("%s\t", lexeme);
      switch(nextToken){
          case INT_LIT:
              printf("INT_LIT");
              break;
          case IDENT:
              printf("IDENT");
              break;
          case ASSIGN_OP:
              printf("ASSIGN_OP");
              break;
          case ADD_OP:
              printf("ADD_OP");
              break;
          case SUB_OP:
              printf("SUB_OP");
              break;
          case MULT_OP:
              printf("MULT_OP");
              break;
          case DIV_OP:
              printf("DIV_OP");
              break;
          case LEFT_PAREN:
              printf("LEFT_PAREN");
              break;
          case RIGHT_PAREN:
              printf("RIGHT_PAREN");
              break;
          case INC_OP:
              printf("INC_OP");
              break;
          case DEC_OP:
              printf("DEC_OP");
              break;
          case EQUAL_OP:
              printf("EQUAL_OP");
              break;
          case MOD_OP:
              printf("MOD_OP");
              break;
          case SEMICOLON:
              printf("SEMICOLON");
              break;
          case COLON:
              printf("COLON");
              break;
          case NEQUAL_OP:
              printf("NEQUAL_OP");
              break;
          case LEQUAL_OP:
              printf("LEQUAL_OP");
              break;
          case LESSER_OP:
              printf("LESSER_OP");
              break;
          case GEQUAL_OP:
              printf("GEQUAL_OP");
              break;
          case GREATER_OP:
              printf("GREATER_OP");
              break;
          case KEY_READ:
              printf("KEY_READ");
              break;
          case KEY_WRITE:
              printf("KEY_WRITE");
              break;
          case KEY_IF:
              printf("KEY_IF");
              break;
          case KEY_FI:
              printf("KEY_FI");
              break;
          case KEY_ELSE:
              printf("KEY_ELSE");
              break;
          case KEY_THEN:
              printf("KEY_THEN");
              break;
          case EOF:
              printf("EOF");
              break;
          default:
              printf("UNKNOWN");
              break;
          }
        }
}

/*
P ::= S
S ::= V:=E | read(V) | write(E) | if C: then S U fi | S;S  IDENT := INT_LIT
U ::= else S | e  e = epsilon
C ::= (C) | E < E | E > E | E = E | E <> E | E <= E | E >= E
E ::= T | E + T | E - T
T ::= F | T * F | T / F | T % F
F ::= (E) | O | N | V
O ::= ++V | --V
V ::= a | b | … | y | z | aV | bV | … | yV | zV  IDENT
N ::= 0 | 1 | … | 8 | 9 | 0N | 1N | … | 8N | 9N  INT_LIT
*/












//placeholder
