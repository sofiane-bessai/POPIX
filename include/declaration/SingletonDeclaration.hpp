#pragma once

#include <declaration/VarDeclaration.hpp>

/**
 * @brief unique element declaration
 */
class SingletonDeclaration : public VarDeclaration {
	public:
		/**
		 * @brief Construct a new Singleton Declaration object
		 * 
		 * @param id 
		 */
		SingletonDeclaration(std::string);

		/**
		 * @brief Construct a new Singleton Declaration object
		 * 
		 * @param id 
		 * @param precision 
		 */
		SingletonDeclaration(std::string, Precision*);

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
		 * @param int index
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
		 * @param double value
		 * @param int index
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
		 * @param int depth
		 * 
		 * @return std::string 
		 */
		virtual std::string ToStringPOP(int);
	
		/**
		 * @brief 
		 * 
		 * @param int depth
		 * 
		 * @return std::string 
		 */
		virtual std::string ToStringFloat(int);
	
		/**
		 * @brief 
		 * 
		 * @param int depth
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