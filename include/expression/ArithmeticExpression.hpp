#pragma once

#include <expression/BinaryExpression.hpp>
#include <expression/Precision.hpp>

/**
 * @brief 
 */
class ArithmeticExpression : public BinaryExpression {
	public:

		/**
		 * @brief arithmetic operations
		 */
		enum Operation {
			PLUS,
			MINUS,
			TIMES,
			DIVIDE
		};

		/**
		 * @brief Construct a new Arithmetic Expression object
		 */
		ArithmeticExpression(Expression*, Operation, Expression*);
		
		/**
		 * @brief Construct a new Arithmetic Expression object
		 */
		ArithmeticExpression(Expression*, Operation, Precision *, Expression*);

		/**
		 * @brief Get the Op object
		 * 
		 * @return ArithmeticExpression::Operation 
		 */
		ArithmeticExpression::Operation GetOp();

		/**
		 * @brief Get the Operand 1 object
		 * 
		 * @return Expression* 
		 */
		Expression *GetOperand1();
		
		/**
		 * @brief Get the Operand 2 object
		 * 
		 * @return Expression* 
		 */
		Expression *GetOperand2();

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
		
		/**
		 * @brief 
		 */
		Precision *m_precision;
};