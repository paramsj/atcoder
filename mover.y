%{
#include <stdio.h>
#include <stdlib.h>

int x = 0, y = 0;
void yyerror(char *s);
int yylex();
%}

%token START NORTH SOUTH EAST WEST

%%

// The 'input' rule finishes when you hit Enter
input: line '\n' { printf("\nReached Final Position: ( %d, %d )\n", x, y); exit(0); }
     ;

line: S
    ;

S: S D { 
    /* This block runs after EVERY move */
    printf("Move -> Current Position: ( %d, %d )\n", x, y); 
   }
 | START { 
    x = 0; y = 0; 
    printf("Start -> Current Position: ( 0, 0 )\n"); 
   }
 ;

D: NORTH { y++; }
 | SOUTH { y--; }
 | EAST  { x++; }
 | WEST  { x--; }
 ;

%%

void yyerror(char *s) {
    fprintf(stderr, "Invalid string\n");
}

int main() {
    printf("Enter the sequence: \n");
    yyparse();
    return 0;
}