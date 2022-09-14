#pragma once

#include <expression/ConstantExpression.hpp>

/**
 * @brief 
 */
class CallExpression : public ConstantExpression {
	public:

		/**
		 * @brief 
		 */
        enum class CallExpressionType {
            ABS,
            SQRT,
            SIN,
            COS,
            ATAN,
            UNHANDLED
        };

		/**
		 * @brief Construct a new Call Expression object
		 */
		CallExpression(std::string, Expression*, Precision*);
        
		/**
		 * @brief Construct a new Call Expression object
		 */
		CallExpression(std::string, Expression*, Precision*, CallExpressionType);

		/**
		 * @brief Get the Call Type object
		 * 
		 * @return CallExpression::CallExpressionType 
		 */
		CallExpression::CallExpressionType GetCallType();
		
		/**
		 * @brief Get the Arg object
		 * 
		 * @return Expression* 
		 */
		Expression *GetArg();

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
		std::string m_identifier;

		/**
		 * @brief 
		 */
		Expression *m_argument;
		
		/**
		 * @brief 
		 */
		CallExpressionType m_callType = CallExpressionType::UNHANDLED;
};