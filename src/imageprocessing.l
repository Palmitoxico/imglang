%{
#include <stdlib.h>
#include <string.h>
#include "imageprocessing.h"
void yyerror(char *);

#include "y.tab.h"
%}



%%

\[	{
	return ABRE_COL;
	}

\]	{
	return FECHA_COL;
	}

[0-9]+(.[0-9]+)? {
		yylval.numval = strtof(yytext, NULL);
        dbgmsg("Achei um numero: %f\n", yylval.numval);
		return NUMERO;
		}

[a-z]  {
        yylval.ival = yytext[0] - 'a';
        return VAR;
       }

[/] { return DIVIDIR; }

\* { return MULTIPLICAR; }

\" { return ASPA; }

[a-zA-Z0-9\.]+  {
        for (int i = 0; i < yyleng; i++ )
          yylval.strval[i] = yytext[i];

        yylval.strval[yyleng] = '\0';
        dbgmsg("Achei nome: %s\n", yylval.strval);
        return STRING;
       }

[=]     {
          return IGUAL;
        }

\n   {
         return EOL;
       }

[ \t]+ ;

.     {dbgmsg("**%s**\n", yytext);
yyerror("Token nao reconhecido!\n");}

%%

int  yywrap() {
  return 1;
}
