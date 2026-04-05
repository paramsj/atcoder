%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+      { yylval = atoi(yytext); return num; }
"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"("         { return '('; }
")"         { return ')'; }
">="        { return GE; }
"<="        { return LE; }
"=="        { return EQ; }
"!="        { return NE; }
">"         { return '>'; }
"<"         { return '<'; }
[ \t]       ; /* skip whitespace */
\n          { return 0; /* end of input */ }
.           { return yytext[0]; }
%%

int yywrap() { return 1; }