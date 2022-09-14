#pragma once

#include <statement/Statement.hpp>
#include <expression/Precision.hpp>

/**
 * @brief 
 */
enum class DataType {
	REAL, 
	INT
};

/**
 * @brief 
 */
class Expression : public Statement {
	public:

		/**
		 * @brief Construct a new Expression object
		 */
		Expression() { m_precision = new Precision(); }
		
		/**
		 * @brief Construct a new Expression object
		 * 
		 * @param precision 
		 */
		Expression(Precision *precision) { m_precision = precision; }

		/**
		 * @brief Get the Length object
		 * 
		 * @return int 
		 */
		virtual int GetLength() { return m_precision->GetLength(); }
		
		/**
		 * @brief Get the Ulp object
		 * 
		 * @return int 
		 */
		virtual int GetUlp() { return m_precision->GetUlp(); }
		
		/**
		 * @brief Get the Ufp object
		 * 
		 * @return int 
		 */
		virtual int GetUfp() { return m_precision->GetUfp(); }

		/**
		 * @brief Get the Evaluated Value object
		 * 
		 * @return double 
		 */
		double GetEvaluatedValue() {
			return m_evaluatedValue;
		}

		/**
		 * @brief 
		 * 
		 * @return true 
		 * @return false 
		 */
		virtual bool IsIntegerExpression() = 0;

		/**
		 * @brief Set the Expression Type object
		 */
		virtual void SetExpressionType(DataType) = 0;
	
	protected:

		/**
		 * @brief 
		 */
		Precision *m_precision;
		
		/**
		 * @brief 
		 */
		DataType m_type = DataType::REAL;
		
		/**
		 * @brief
		 */
		double m_evaluatedValue;
};