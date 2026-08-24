%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *s);
int yylex();
%}

%token num
%token GE LE EQ NE
%left '>' '<' GE LE EQ NE
%left '+' '-'
%left '*' '/'

%%
S : E { printf("Result: %d\n", $1); }
  ;

E : E '+' T     { $$ = $1 + $3; }
  | E '-' T     { $$ = $1 - $3; }
  | E '>' E     { $$ = $1 > $3; }
  | E '<' E     { $$ = $1 < $3; }
  | E GE E      { $$ = $1 >= $3; }
  | E LE E      { $$ = $1 <= $3; }
  | E EQ E      { $$ = $1 == $3; }
  | E NE E      { $$ = $1 != $3; }
  | T           { $$ = $1; }
  ;

T : T '*' F     { $$ = $1 * $3; }
  | T '/' F     { $$ = $1 / $3; }
  | F           { $$ = $1; }
  ;

F : '(' E ')'   { $$ = $2; }
  | num         { $$ = $1; }
  ;

%%
void yyerror(const char *s) { fprintf(stderr, "Error: %s\n", s); }
int main() { return yyparse(); }