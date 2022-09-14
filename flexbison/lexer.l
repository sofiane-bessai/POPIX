%{

#include "../include/Parser.hpp"
#include "../include/expression/LogicalExpression.hpp"

void yyerror (char const *s);

%}

%option noyywrap
%option nounput
%option noinput
%option yylineno

space       [ \t]+
newline     [\r\n]+

identifier  [a-zA-Z][a-zA-Z0-9_]*

%%

{space}                             { /*ignoré par le lexer*/ }
{newline}                           {  }

"While"|"while"                     { return WHILE; }
"if"                                { return IF; }
"else"                              { return ELSE; }
"require_accuracy"|"require_nsb"    { return REQUIRE_ACCURACY; }
"create_array"|"create_vector"      { return CREATE_ARRAY; }

{identifier}                        { yylval.string = strdup(yytext); return IDENTIFIER; }

-?[0-9]+/[^\.]                      { yylval.integer = atoi(yytext); return INTEGER; }

-?[0-9]+\.[0-9]*                    { yylval.real = atof(yytext); return FLOAT; }

-?[0-9]+\.[0-9]*E-?[0-9]+/[^\.]     { yylval.real = atof(yytext); return FLOAT; }

\+                                  { return '+'; }
\-                                  { return '-'; }
\*                                  { return '*'; }
\/                                  { return '/'; }

"=="            	                { yylval.boolOperator = LogicalExpression::Operation::EQ; return CONDITIONNAL_OP; }
"!="|"=!"       	                { yylval.boolOperator = LogicalExpression::Operation::NEQ; return CONDITIONNAL_OP; }
\>              	                { yylval.boolOperator = LogicalExpression::Operation::GREAT; return CONDITIONNAL_OP; }
\<              	                { yylval.boolOperator = LogicalExpression::Operation::LESS; return CONDITIONNAL_OP; }
">="|"=>"                           { yylval.boolOperator = LogicalExpression::Operation::GEQ; return CONDITIONNAL_OP; }
"=<"|"<="                           { yylval.boolOperator = LogicalExpression::Operation::LEQ; return CONDITIONNAL_OP; }

\=              	                { return '='; }

\,              	                { return ','; }
\;              	                { return ';'; }

\(              	                { return '('; }
\)              	                { return ')'; }

\[              	                { return '['; }
\]              	                { return ']'; }

\{              	                { return '{'; }
\}              	                { return '}'; }

\|              	                { return '|'; }

<<EOF>>				                { yyterminate(); }

. 					                { fprintf(stderr, "Unexpected character '%s' at line %d\n", yytext, yylineno); }

%%

void yyerror (char const *s) {
    fprintf (stderr, "%s at line %d (%s)\n", s, yylineno, yytext);
}