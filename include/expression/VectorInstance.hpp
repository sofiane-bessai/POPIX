#pragma once

#include <expression/VarInstance.hpp>
#include <expression/ArithmeticExpression.hpp>

/**
 * @brief 
 */
class VectorInstance : public VarInstance {
	public:

		/**
		 * @brief Construct a new Vector Instance object
		 */
		VectorInstance(std::string, ArithmeticExpression *);

		/**
		 * @brief Construct a new Vector Instance object
		 */
		VectorInstance(std::string, ArithmeticExpression *, Precision *);

		/* VarInstance */

		/**
		 * @brief 
		 */
		virtual void DeclareElement();

		/**
		 * @brief Set the Value object
		 * 
		 * @param value 
		 */
		virtual void SetValue(double value);

		/* ConstantExpression */
		// no methods

		/* Expression */
		/**
		 * @brief 
		 * 
		 * @return true 
		 * @return false 
		 */
		virtual bool IsIntegerExpression();
		
		/**
		 * @brief Set the Expression Type object
		 */
		virtual void SetExpressionType(DataType);

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
		virtual std::string ToStringFix(int);
		
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
		ArithmeticExpression *m_indexExpr;
};