#pragma once

#include <expression/Expression.hpp>

/**
 * @brief 
 */
class BinaryExpression : public Expression {
	public:

		/**
		 * @brief Construct a new Binary Expression object
		 * 
		 * @param lExpr 
		 * @param rExpr 
		 */
		BinaryExpression(Expression *lExpr, Expression *rExpr) : Expression() {
			m_leftExpression = lExpr;
			m_rightExpression = rExpr;
		}

		/**
		 * @brief Construct a new Binary Expression object
		 * 
		 * @param lExpr 
		 * @param precision 
		 * @param rExpr 
		 */
		BinaryExpression(Expression *lExpr, Precision *precision, Expression *rExpr) : Expression(precision) {
			m_leftExpression = lExpr;
			m_rightExpression = rExpr;
		}

		/**
		 * @brief 
		 * 
		 * @return true 
		 * @return false 
		 */
		virtual bool IsIntegerExpression() {
			return m_leftExpression->IsIntegerExpression() && m_rightExpression->IsIntegerExpression();
		}

		/**
		 * @brief Set the Expression Type object
		 * 
		 * @param type 
		 */
		virtual void SetExpressionType(DataType type) {
			m_leftExpression->SetExpressionType(type);
			m_rightExpression->SetExpressionType(type);
		}

	protected:

		/**
		 * @brief 
		 */
		Expression* m_leftExpression;
		
		/**
		 * @brief 
		 */
		Expression* m_rightExpression;
};