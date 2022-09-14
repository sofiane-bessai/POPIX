/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_INCLUDE_PARSER_HPP_INCLUDED
# define YY_YY_INCLUDE_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 15 "flexbison/parser.y"

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

#line 69 "./include/Parser.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    INTEGER = 259,                 /* INTEGER  */
    FLOAT = 260,                   /* FLOAT  */
    WHILE = 261,                   /* WHILE  */
    IF = 262,                      /* IF  */
    ELSE = 263,                    /* ELSE  */
    REQUIRE_ACCURACY = 264,        /* REQUIRE_ACCURACY  */
    CREATE_ARRAY = 265,            /* CREATE_ARRAY  */
    CONDITIONNAL_OP = 266          /* CONDITIONNAL_OP  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 39 "flexbison/parser.y"

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

#line 118 "./include/Parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INCLUDE_PARSER_HPP_INCLUDED  */
