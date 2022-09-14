%{

int yylex (void);
int yyerror (const char *msg);
extern int yylineno;

#include <Compiler.hpp>

#include <Log.hpp>

#define DEBUG_PARSER

%}

%code requires {
	#include <vector>

	#include <statement/StatementList.hpp>
	#include <statement/AssignmentStatement.hpp>
	#include <statement/WhileLoopStatement.hpp>
	#include <statement/IfStatement.hpp>
	#include <statement/RequireStatement.hpp>

	#include <declaration/VectorDeclaration.hpp>

	#include <expression/ArithmeticExpression.hpp>
	#include <expression/CallExpression.hpp>
	#include <expression/LogicalExpression.hpp>
	#include <expression/Precision.hpp>
	#include <expression/Scalar.hpp>
	#include <expression/SingletonInstance.hpp>
	#include <expression/VectorInstance.hpp>
}

%define parse.error verbose /* debug */

/* Type of tokens */

%union {
	int integer;
	double real;
	char *string;
	int boolOperator;

	StatementList *statementList;
	Statement *statement;

	Expression *expression;
	// ArithmeticExpression *arithmetic_expression;
	LogicalExpression *logical_expression;
	// ConstantExpression *constant_expression;

	std::vector<Expression*> *exprList;

	Precision *precision;

	VarInstance *variable;
}

/* Terminal symbols */

%token <string> IDENTIFIER
%token <integer> INTEGER 
%token <real> FLOAT

%token WHILE

%token IF ELSE

%token REQUIRE_ACCURACY
%token CREATE_ARRAY

%token '='
%token <boolOperator> CONDITIONNAL_OP
%token '+' '-' '*' '/'

%token '[' ']'
%token '(' ')'
%token '{' '}'

%token '|'

%token ';' ','

/* Nonterminal symbols */

%start Program

%type <statementList> statement_list

%type <statement> statement
%type <statement> assignment
%type <statement> loop_statement
%type <statement> cond_statement

%type <expression> bool_expression
%type <expression> add_expression
%type <expression> mul_expression
%type <expression> primary_expression

%type <precision> precision

%type <variable> identifier

%%

/* Rules */

Program : statement_list {
			g_Compiler->SetProgram($1);
		};

statement_list : statement_list statement {
			$1->AppendStatement($2);
			$$ = $1;
		}
		| statement {
			$$ = new StatementList();
			$$->AppendStatement($1);
		};

statement : loop_statement { $$ = $1; }
		| cond_statement { $$ = $1; }
		| assignment { $$ = $1; }
		| CREATE_ARRAY '(' IDENTIFIER ',' INTEGER ')' precision ';' {
			g_Compiler->AppendVariable( new VectorDeclaration($3, $5) );
			$$ = nullptr;
		}
		| REQUIRE_ACCURACY '(' IDENTIFIER ',' INTEGER ')' precision ';' {
			$$ = new RequireStatement($3, $5);
			$$->m_lineno = yylineno;
		}
		| ';' { $$ = nullptr; };

assignment : identifier '=' add_expression ';' {
			$$ = new AssignmentStatement($1, $3);
			$$->m_lineno = yylineno;
		}

loop_statement : WHILE '(' bool_expression ')' '{' statement_list '}' {
			$$ = new WhileLoopStatement( (LogicalExpression*) $3, $6);
			$$->m_lineno = $3->m_lineno;
		};

cond_statement : IF '(' bool_expression ')' '{' statement_list '}' {
			$$ = new IfStatement( (LogicalExpression*) $3, $6);
			$$->m_lineno = $3->m_lineno;
		}
		| IF '(' bool_expression ')' '{' statement_list '}' ELSE '{' statement_list '}' {
			$$ = new IfStatement( (LogicalExpression*) $3, $6, $10);
			$$->m_lineno = $3->m_lineno;
		};

bool_expression : add_expression { $$ = $1; }
		| bool_expression CONDITIONNAL_OP add_expression {
			$$ = new LogicalExpression($1, (LogicalExpression::Operation) $2, $3);
			$$->m_lineno = yylineno;
		};

add_expression : mul_expression { $$ = $1; }
		| add_expression '+' precision mul_expression {
			$$ = new ArithmeticExpression($1, ArithmeticExpression::Operation::PLUS, $3, $4);
			$$->m_lineno = yylineno;
		}
		| add_expression '-' precision mul_expression {
			$$ = new ArithmeticExpression($1, ArithmeticExpression::Operation::MINUS, $3, $4);
			$$->m_lineno = yylineno;
		};

mul_expression : primary_expression { $$ = $1; }
		| mul_expression '*' precision primary_expression {
			$$ = new ArithmeticExpression($1, ArithmeticExpression::Operation::TIMES, $3, $4);
			$$->m_lineno = yylineno;
		}
		| mul_expression '/' precision primary_expression {
			$$ = new ArithmeticExpression($1, ArithmeticExpression::Operation::DIVIDE, $3, $4);
			$$->m_lineno = yylineno;
		};

primary_expression : '(' bool_expression ')' { $$ = $2; }
		| identifier { $$ = $1; }
		| INTEGER precision {
			$$ = new Scalar($1, $2);
			$$->m_lineno = yylineno;
		}
		| FLOAT precision {
			$$ = new Scalar($1, $2);
			$$->m_lineno = yylineno;
		}
		| IDENTIFIER '(' add_expression ')' precision {
			$$ = new CallExpression($1, $3, $5);
			$$->m_lineno = yylineno;
		};

precision : '|' INTEGER '|' {
			$$ = new Precision($2);
			$$->m_lineno = yylineno;
		}
		| '|' INTEGER ',' INTEGER '|' {
			$$ = new Precision($2, $4);
			$$->m_lineno = yylineno;
		}
		| %empty {
			$$ = new Precision();
			$$->m_lineno = yylineno;
		};

identifier : IDENTIFIER precision {
			$$ = new SingletonInstance($1, $2);
			$$->m_lineno = yylineno;
		}
		| IDENTIFIER '[' add_expression ']' precision {
			$$ = new VectorInstance($1, (ArithmeticExpression*) $3, $5);
			$$->m_lineno = yylineno;
		};

%%