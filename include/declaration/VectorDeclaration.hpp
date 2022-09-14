#pragma once

#include <declaration/VarDeclaration.hpp>
#include <vector>

/**
 * @brief vector declaration
 */
class VectorDeclaration : public VarDeclaration {
	public:

		/**
		 * @brief Construct a new Vector Declaration object
		 */
		VectorDeclaration(std::string, int);
	
		/**
		 * @brief Construct a new Vector Declaration object
		 */
		VectorDeclaration(std::string, int, Precision*);

		/* 
		** Getter & Setter
		*/

		/**
		 * @brief Get the Value object
		 * 
		 * @return double 
		 */
		virtual double GetValue();
		
		/**
		 * @brief Get the Value object
		 * 
		 * @param int 
		 * @return double 
		 */
		virtual double GetValue(unsigned int);

		/**
		 * @brief Set the Value object
		 */
		virtual void SetValue(double);

		/**
		 * @brief Set the Value object
		 * 
		 * @param int 
		 */
		virtual void SetValue(double, unsigned int);

		/* VarDeclaration */
		
		/**
		 * @brief Get the Size object
		 * 
		 * @return int 
		 */
		virtual int GetSize();

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
		int m_length;

		/**
		 * @brief 
		 */
		std::vector<double> m_value;
};