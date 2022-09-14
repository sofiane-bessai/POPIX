#pragma once

#include <statement/Statement.hpp>

/**
 * @brief 
 */
#define UNDEFINED_UFP (int) 32767

/**
 * @brief 
 */
#define UNDEFINED_ULP (int) 32767

/**
 * @brief 
 */
#define UNDEFINED_LENGTH (int) -1

/**
 * @brief define max var length in embedded system
 */
#define MAX_LENGHT (int) 31

/**
 * @brief 
 */
class Precision : public Statement {
	public:

		/**
		 * @brief Construct a new Precision object
		 */
        Precision() : Statement(/* args */) {
            m_ufp = UNDEFINED_UFP;
			m_ulp = UNDEFINED_ULP;
			m_length = UNDEFINED_LENGTH;
        }

		/**
		 * @brief Construct a new Precision object
		 * 
		 * @param length 
		 */
		Precision(int length) : Statement(/* args */) {
			m_ufp = UNDEFINED_UFP;
			m_ulp = UNDEFINED_ULP;
			m_length = length;
		}

		/**
		 * @brief Construct a new Precision object
		 * 
		 * @param ufp 
		 * @param length 
		 */
		Precision(int ufp, int length) : Statement(/* args */) {
			m_ufp = ufp;
			m_ulp = ufp - length + 1;
			m_length = length;
		}

		/**
		 * @brief Get the Ufp object
		 * 
		 * @return int 
		 */
		int GetUfp() { return ( m_ufp == UNDEFINED_UFP ) ? 0 : m_ufp; }
		
		/**
		 * @brief Get the Ulp object
		 * 
		 * @return int 
		 */
		int GetUlp() { return ( m_ulp == UNDEFINED_ULP ) ? 0 : m_ulp; }
		
		/**
		 * @brief Get the Length object
		 * 
		 * @return int 
		 */
		int GetLength() { return ( m_length == UNDEFINED_LENGTH ) ? 0 : m_length; }

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
		int m_ufp;

		/**
		 * @brief 
		 */
		int m_ulp;

		/**
		 * @brief 
		 */
		int m_length;
};