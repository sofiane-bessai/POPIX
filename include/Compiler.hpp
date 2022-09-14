#pragma once

#include <statement/DeclarationList.hpp>
#include <statement/StatementList.hpp>

#define DTIME_EXECUTION
#define PRINT_RESULT

/**
 * @brief 
 */
enum class GenerationType {
	POP,
	FLOAT,
	FIX,
	FIX_EXTENDED,
	VHDL,
	UNDEFINED
};

/**
 * @brief 
 */
class Compiler {

	public:

		/**
		 * @brief Construct a new Compiler object
		 */
		Compiler();

		/**
		 * @brief Construct a new Compiler object
		 */
		Compiler(StatementList *);

		/**
		 * @brief 
		 * 
		 * @return true 
		 * @return false 
		 */
        bool Parse(const char *);
        
		/**
		 * @brief 
		 * 
		 * @return true 
		 * @return false 
		 */
		bool SemanticAnalysis();

		/**
		 * @brief Set the Program object
		 */
		void SetProgram(StatementList *);
        
		/**
		 * @brief Set the Generation Type object
		 */
		void SetGenerationType(GenerationType);

		/**
		 * @brief Get the Declaration object
		 * 
		 * @return VarDeclaration* 
		 */
		VarDeclaration *GetDeclaration(std::string);
		
		/**
		 * @brief 
		 * 
		 * @return true 
		 * @return false 
		 */
		bool IsExist(std::string);

		/**
		 * @brief 
		 * 
		 * @return true 
		 * @return false 
		 */
        bool GenerateOutput(std::ofstream &);

		/**
		 * @brief 
		 * 
		 * @return true 
		 * @return false 
		 */
		bool AppendVariable(VarDeclaration *);

		/**
		 * @brief 
		 */
		void PrintVarList();

    private:

		/**
		 * @brief 
		 */
        class Analytics {
    
        } *m_analytics;

		/**
		 * @brief 
		 */
		DeclarationList *m_declarationList;
		
		/**
		 * @brief 
		 */
		StatementList *m_program;
		
		/**
		 * @brief 
		 */
		GenerationType m_generationLangage;

		/**
		 * @brief 
		 */
		void GenerateHeader(std::ofstream &);
		
		/**
		 * @brief 
		 */
		void GenerateBody(std::ofstream &);
		
		/**
		 * @brief 
		 */
		void GenerateFoot(std::ofstream &);
};

/**
 * @brief 
 */
extern Compiler *g_Compiler;