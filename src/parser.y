%{
#include <stdio.h>    // Add this
#include <stdlib.h>   // Add this
#include "ast.h"
#include "symbol.h"


#define YYDEBUG 1

extern int yylex();
extern int yylineno;
extern ASTNode *root;
extern char *yytext;
extern FILE *yyin;

void yyerror(const char *s);


%}

%define parse.error verbose


%union {
    int num;
    char *str;
    struct ASTNode *node;
}

//%type <node> program stmt expr term factor  // Add program/stmt
%token <num> NUMBER
%token <str> IDENTIFIER
%token PLUS MINUS TIMES DIVIDE ASSIGN SEMI


%type <node> program stmt expr term factor  // Add program/stmt


%%

program:
    stmt { root = $1; }  // Now properly typed
    ;

stmt:
    IDENTIFIER ASSIGN expr SEMI 
    { 
        printf("Parser: Processing assignment for '%s'\n", $1);
        $$ = createAssignNode($1, $3); 
    }
    ;
    
expr:
    term                { $$ = $1; }
    | expr PLUS term    { $$ = createOpNode(OP_ADD, $1, $3); }
    | expr MINUS term   { $$ = createOpNode(OP_SUB, $1, $3); }
    | error             { 
          yyerror("Invalid expression"); 
          yyerrok; 
          $$ = NULL; 
      }
    ;

term:
    factor              { $$ = $1;}
    | term TIMES factor { $$ = createOpNode(OP_MUL, $1, $3);  }
    | term DIVIDE factor { $$ = createOpNode(OP_DIV, $1, $3);}
    | error             { 
          yyerror("Invalid term"); 
          yyerrok; 
          $$ = NULL; 
      }
    ;

factor:
    NUMBER       { $$ = createNumNode($1); if (!$$) YYERROR;}
    | IDENTIFIER { $$ = createVarNode($1); if (!$$) YYERROR;}
    | '(' expr ')' { $$ = $2; if (!$$) YYERROR;}
    ;


%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
    fprintf(stderr, "Last token: %s\n", yytext);
    exit(1);
}
