#pragma once

#include <Log.hpp>

#include <string>

class Statement {
	public:
		/**
		 * @brief part of semantic analysis, resolve every name inside the program
		 * 
		 * @return true : no error
		 * @return false : a name can't be resolved
		 */
		virtual bool NameResolution() = 0;

		/**
		 * @brief 
		 * 
		 * @return true 
		 * @return false 
		 */
		virtual bool TypeSolving() = 0;
		
		/**
		 * @brief 
		 * 
		 * @return true 
		 * @return false 
		 */
		virtual bool CollectAnalysisItem() = 0;

		/**
		 * @brief 
		 * 
		 * @return double 
		 */
		virtual double EvaluateFloat() = 0;

		/**
		 * @brief 
		 * 
		 * @return std::string 
		 */
		virtual std::string ToStringPOP(int) = 0;
		
		/**
		 * @brief 
		 * 
		 * @return std::string 
		 */
		virtual std::string ToStringFloat(int) = 0;
		
		/**
		 * @brief 
		 * 
		 * @return std::string 
		 */
		virtual std::string ToStringFixExtended(int) = 0;

		/**
		 * @brief 
		 */
		int m_lineno = -1;
	
	protected:

		/**
		 * @brief 
		 * 
		 * @param depth 
		 * @return std::string 
		 */
		std::string Indent(int depth) {
			return std::string(depth, '\t');
		}
};