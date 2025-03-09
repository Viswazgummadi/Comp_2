%{
#include <stdlib.h>   // Add this for exit()
#include "ast.h"
#include "parser.tab.h"
void yyerror(const char *s);  // Add prototype
%}

%option noinput nounput
%option noyywrap

DIGIT    [0-9]
ID       [a-zA-Z_][a-zA-Z0-9_]*

%%
{DIGIT}+    {printf("Lexer: Found number %s with val %d\n", yytext, atoi(yytext)); yylval.num = atoi(yytext); return NUMBER; }
{ID}       { printf("Lexer: Found identifier %s\n", yytext); yylval.str = strdup(yytext); return IDENTIFIER; }
"+"        { return PLUS; }
"-"        { return MINUS; }
"*"        { return TIMES; }
"/"        { return DIVIDE; }
"="        { return ASSIGN; }
";"        { return SEMI; }
"("        { return '('; }
")"        { return ')'; }

[ \t\n]    ; /* Ignore whitespace */
.          { yyerror("Invalid character"); }
%%
