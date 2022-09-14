#pragma once

#include <expression/ConstantExpression.hpp>

/**
 * @brief 
 */
class Scalar : public ConstantExpression {
	public:

		/**
		 * @brief Construct a new Scalar object
		 */
		Scalar(double);

		/**
		 * @brief Construct a new Scalar object
		 */
		Scalar(double, Precision *);

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
		double m_value;
};
