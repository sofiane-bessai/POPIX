#pragma once

#include <statement/Statement.hpp>

/**
 * @brief 
 */
class RequireStatement : public Statement {
	public:

		/**
		 * @brief Construct a new Require Statement object
		 */
		RequireStatement(std::string, int);

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

	protected:

		/**
		 * @brief 
		 */
		std::string m_id;
		
		/**
		 * @brief 
		 */
		int m_nsb;

		// double m_value;
		// std::vector<double> m_values;
};