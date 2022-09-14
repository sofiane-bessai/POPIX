#pragma once

#include <expression/VarInstance.hpp>

/**
 * @brief 
 */
class SingletonInstance : public VarInstance {
	public:

		/**
		 * @brief Construct a new Singleton Instance object
		 */
		SingletonInstance(std::string);

		/**
		 * @brief Construct a new Singleton Instance object
		 */
		SingletonInstance(std::string, Precision *);

		/* VarInstance */

		/**
		 * @brief 
		 */
		virtual void DeclareElement();
		
		/**
		 * @brief Set the Value object
		 */
		virtual void SetValue(double);

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
		virtual std::string ToStringFixExtended(int);
};