#pragma once

#include <expression/ConstantExpression.hpp>

/**
 * @brief 
 */
class VarInstance : public ConstantExpression {
	public:

		/**
		 * @brief Construct a new Var Instance object
		 * 
		 * @param id 
		 */
		VarInstance(std::string id) : ConstantExpression() {
			m_id = id;
		}

		/**
		 * @brief Construct a new Var Instance object
		 * 
		 * @param id 
		 * @param precision 
		 */
		VarInstance(std::string id, Precision *precision) : ConstantExpression(precision) {
			m_id = id;
		}

		/**
		 * @brief 
		 */
		virtual void DeclareElement() = 0;

		/**
		 * @brief Set the Value object
		 */
		virtual void SetValue(double) = 0;

	protected:

		/**
		 * @brief 
		 */
		std::string m_id;
};