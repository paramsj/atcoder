%{
#include "y.tab.h"
%}

%%
"START"     { return START; }
"n"         { return NORTH; }
"s"         { return SOUTH; }
"e"         { return EAST;  }
"w"         { return WEST;  }
[ \t]       ; /* Skip spaces */
\n          { return '\n'; }
.           { return yytext[0]; }
%%

int yywrap() { return 1; }