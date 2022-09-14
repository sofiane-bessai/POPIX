######################################################################################
###################################### MAKEFILE ######################################
######################################################################################
# Makefile for OPTFloat project - Master CHPS UPVD 2020-2022 #########################
# Realised by BESSAI Sofiane #########################################################
######################################################################################

######################################################################################
################################# GLOBALE VARIABLES ##################################
######################################################################################

#
CC = g++

CFLAGS = -I./$(INCLUDE_DIR) -Wall -std=c++17 # -O3 
LDFLAGS = -lm

BISON_FLAGS = -v # --debug -Wall
LEXER_FLAGS = 

EXECUTABLE = popix

#
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj

#
DECLARATION_DIR = declaration
EXPRESSION_DIR = expression
STATEMENT_DIR = statement
FIX_DIR = fix

FLEXBISON_DIR = flexbison

#
ABSTRACT_CLASS_HEADERS = 	./$(INCLUDE_DIR)/$(DECLARATION_DIR)/VarDeclaration.hpp \
							./$(INCLUDE_DIR)/$(EXPRESSION_DIR)/Expression.hpp \
							./$(INCLUDE_DIR)/$(EXPRESSION_DIR)/BinaryExpression.hpp \
							./$(INCLUDE_DIR)/$(EXPRESSION_DIR)/ConstantExpression.hpp \
							./$(INCLUDE_DIR)/$(EXPRESSION_DIR)/VarInstance.hpp \
							./$(INCLUDE_DIR)/$(STATEMENT_DIR)/Statement.hpp \

SRC_FILES = $(wildcard ./$(SRC_DIR)/*.cpp) $(wildcard ./$(SRC_DIR)/*/*.cpp)
OBJ_FILES = $(patsubst ./src/%.cpp, ./obj/%.o, $(SRC_FILES))

######################################################################################
################################## GLOBALE RULES #####################################
######################################################################################

all : bison flex $(EXECUTABLE)

bison : ./flexbison/parser.y
	@bison $(BISON_FLAGS) $< --output=./$(SRC_DIR)/Parser.cpp --defines=./$(INCLUDE_DIR)/Parser.hpp
	@rm -f ./$(SRC_DIR)/$(FLEXBISON_DIR)/Parser.output

flex: ./flexbison/lexer.l
	@flex $(LEXER_FLAGS) --outfile=./$(SRC_DIR)/Lexer.cpp --header-file=./$(INCLUDE_DIR)/Lexer.hpp -s $<

$(EXECUTABLE) : $(GEN_OBJ_FILES) $(OBJ_FILES)
	@$(CC) -o $(EXECUTABLE) $^ $(LIB_OBJ_FILES) $(CFLAGS) $(LDFLAGS)

./obj/main.o : ./src/main.cpp $(ABSTRACT_CLASS_HEADERS)
	@$(CC) $(CFLAGS) -o $@ -c $<

./obj/%.o : ./src/%.cpp ./include/%.hpp $(ABSTRACT_CLASS_HEADERS)
	@$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: lib flex bison

######################################################################################
################################## VARIOUS RULES #####################################
######################################################################################

clean :
	@rm -f ./obj/*.o
	@rm -f ./obj/*/*.o
	@rm -f ./$(EXECUTABLE)

print-% :
	@echo $* = $($*)

test:
	@echo ""
	@make -C data all

.PHONY: clean test