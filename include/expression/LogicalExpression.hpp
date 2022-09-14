#pragma once

#include <expression/BinaryExpression.hpp>

/**
 * @brief 
 */
class LogicalExpression : public BinaryExpression {
	public:

		/**
		 * @brief boolean operators
		 */
		enum Operation {
			EQ,
			NEQ,
			LESS,
			LEQ,
			GREAT,
			GEQ
		};

		/**
		 * @brief Construct a new Logical Expression object
		 */
		LogicalExpression(Expression *, Operation, Expression *);

		/* BinaryExpression */
		// no methods

		/* Expression */
		// no methods

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
		Operation m_op;
};