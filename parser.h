#ifndef PARSER_H
#define PARSER_H

void program();
void term();
void statement();
void comparison();
void assignment();
void readStatement();
void writeStatement();
void ifStatement();
void expression();
void factor();

extern int nextToken;
#endif
