#pragma once

#include <declaration/VarDeclaration.hpp>
#include <unordered_map>

/**
 * @brief 
 */
class DeclarationList : public Statement {
	public:

		/**
		 * @brief Construct a new Declaration List object
		 */
		DeclarationList();

		/**
		 * @brief 
		 */
		void ModifyLength(std::string, int);
		
		/**
		 * @brief 
		 */
		void ModifyUfp(std::string, int);
		
		/**
		 * @brief Get the List Size object
		 * 
		 * @return int 
		 */
		int GetListSize();
		
		/**
		 * @brief Get the Length From Id object
		 * 
		 * @return int 
		 */
		int GetLengthFromId(std::string);
		
		/**
		 * @brief Get the Max Id Size object
		 * 
		 * @return int 
		 */
		int GetMaxIdSize();
		
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
		bool AppendVariable(VarDeclaration *);
		
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
		 */
		void PrintVariables();

		/* Statement */
		
		/**
		 * @brief 
		 * 
		 * @return true 
		 * @return false 
		 */
		virtual bool NameResolution();
		
		/**
		 * @brief 
		 * 
		 * @return true 
		 * @return false 
		 */
		virtual bool TypeSolving();
		
		/**
		 * @brief 
		 * 
		 * @return true 
		 * @return false 
		 */
		virtual bool CollectAnalysisItem();
		
		/**
		 * @brief 
		 * 
		 * @return double 
		 */
		virtual double EvaluateFloat();
		
		/**
		 * @brief 
		 * 
		 * @return std::string 
		 */
		virtual std::string ToStringPOP(int);
		
		/**
		 * @brief 
		 * 
		 * @return std::string 
		 */
		virtual std::string ToStringFloat(int);
		
		/**
		 * @brief 
		 * 
		 * @return std::string 
		 */
		virtual std::string ToStringFixExtended(int);

	private:

		/**
		 * @brief 
		 */
		std::unordered_map <std::string, VarDeclaration*> m_variables;
		
		/**
		 * @brief 
		 */
		int m_maxIdSize = -1;
};