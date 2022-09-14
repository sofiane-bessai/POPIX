#pragma once

#include <statement/Statement.hpp>

#include <expression/Expression.hpp>
#include <expression/VarInstance.hpp>

/**
 * @brief 
 */
class AssignmentStatement : public Statement {
	public:

		/**
		 * @brief Construct a new Assignment Statement object
		 */
		AssignmentStatement(VarInstance*, Expression*);

		/* Assignment */

		/**
		 * @brief 
		 * 
		 * @return true 
		 * @return false 
		 */
		bool IsIntegerAssignment();

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
		VarInstance *m_variable;
		
		/**
		 * @brief 
		 */
		Expression *m_expression;
		
		/**
		 * @brief 
		 */
		double m_value;
};