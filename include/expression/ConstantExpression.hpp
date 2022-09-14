#pragma once

#include <expression/Expression.hpp>

/**
 * @brief 
 */
class ConstantExpression : public Expression {
	public:

		/**
		 * @brief Construct a new Constant Expression object
		 */
		ConstantExpression() : Expression() {}

		/**
		 * @brief Construct a new Constant Expression object
		 * 
		 * @param precision 
		 */
		ConstantExpression(Precision *precision) : Expression(precision) {}

		/**
		 * @brief Set the Expression Type object
		 * 
		 * @param type 
		 */
		virtual void SetExpressionType(DataType type) {
			m_type = type;
		}
};