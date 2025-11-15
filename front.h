#ifndef FRONT_H
#define FRONT_H

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define INC_OP 27
#define DEC_OP 28
#define EQUAL_OP 29
#define MOD_OP 30
#define SEMICOLON 31
#define COLON 32
#define NEQUAL_OP 33
#define LEQUAL_OP 34
#define LESSER_OP 35
#define GEQUAL_OP 36
#define GREATER_OP 37
#define KEY_READ 50
#define KEY_WRITE 51
#define KEY_IF 52
#define KEY_FI 53
#define KEY_ELSE 54
#define KEY_THEN 55


extern char lexeme[100];


int lex();

#endif
