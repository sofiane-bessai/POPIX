#pragma once

#include <expression/LogicalExpression.hpp>
#include <statement/StatementList.hpp>

/**
 * @brief 
 */
class IfStatement : public Statement {
	public:

		/**
		 * @brief Construct a new If Statement object
		 */
		IfStatement(LogicalExpression *, StatementList *);
		
		/**
		 * @brief Construct a new If Statement object
		 */
		IfStatement(LogicalExpression *, StatementList *, StatementList *);

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
		LogicalExpression *m_condition;
		
		/**
		 * @brief 
		 */
		StatementList *m_ifBody;
		
		/**
		 * @brief 
		 */
		StatementList *m_elseBody;
};