#pragma once

#include <statement/Statement.hpp>
#include <expression/Expression.hpp>

/**
 * @brief abstract class of element declaration
 */
class VarDeclaration : public Statement {
	public:
		/**
		 * @brief Construct a new Var Declaration object
		 * 
		 * @param id 
		 */
		VarDeclaration(std::string id) {
			m_type = DataType::REAL;
			m_id = id;
			m_varSize = UNDEFINED_LENGTH;
			m_lastUfp = UNDEFINED_UFP;
		}

		/**
		 * @brief Construct a new Var Declaration object
		 * 
		 * @param id 
		 * @param length 
		 */
		VarDeclaration(std::string id, int length) {
			m_type = DataType::REAL;
			m_id = id;
			m_varSize = length;
			m_lastUfp = UNDEFINED_UFP;
		}

		/**
		 * @brief Construct a new Var Declaration object
		 * 
		 * @param id 
		 * @param precision 
		 */
		VarDeclaration(std::string id, Precision *precision) {
			m_type = DataType::REAL;
			m_id = id;
			m_varSize = precision->GetLength();
			m_lastUfp = UNDEFINED_UFP;
		}

		/**
		 * @brief Destroy the Var Declaration object
		 * 
		 */
		virtual ~VarDeclaration() {}

		/* 
		** Getter & Setter
		*/

		/**
		 * @brief Get the Type object
		 * 
		 * @return DataType 
		 */
		DataType GetType() { return m_type; }

		/**
		 * @brief Get the Id object
		 * 
		 * @return std::string 
		 */
		std::string GetId() { return m_id; }

		/**
		 * @brief Get the Var Size object
		 * 
		 * @return int 
		 */
		int GetVarSize() { return m_varSize; }
		
		/**
		 * @brief Get the Last Ufp object
		 * 
		 * @return int 
		 */
		int GetLastUfp() { return m_lastUfp; }

		/**
		 * @brief Get the Size object
		 * 
		 * @return * int 
		 */
		virtual int GetSize() = 0;

		/**
		 * @brief Set the Max Var Size object
		 * 
		 * @param size 
		 */
		void SetMaxVarSize(int size) {
			if(abs(size) > m_varSize)
				m_varSize = abs(size);
		}

		/**
		 * @brief Set the Last Ufp object
		 * 
		 * @param ufp 
		 */
		void SetLastUfp(int ufp) {
			m_lastUfp = ufp;
		}

		/**
		 * @brief Set the Type object
		 * 
		 * @param type 
		 */
		void SetType(DataType type) {
			m_type = type;
		}

		/**
		 * @brief Get the Float Type object
		 * 
		 * @return std::string 
		 */
		std::string GetFloatType() {
			return ( m_type == DataType::INT ) ? "int " : "float ";
		}

		/**
		 * @brief Get the Fix Type object
		 * 
		 * @return std::string 
		 */
		std::string GetFixType() {
			return ( m_type == DataType::INT ) ? "int " : "FIX ";
		}

		/**
		 * @brief Get the Fix Extended Type object
		 * 
		 * @return std::string 
		 */
		std::string GetFixExtendedType() {
			std::string type = "UNKNOWN ";
			if( m_type == DataType::INT ) type = "int ";
			else {
				if( ( m_varSize + 3 ) < 8 ) { type = "int8_t "; }
				else if( ( m_varSize + 3 ) < 16 ) { type = "int16_t "; }
				else if( ( m_varSize + 3 ) < 32 ) { type = "int32_t "; }
				else if( ( m_varSize + 3 ) < 64 ) { type = "int64_t "; }
				else type = "TOO_LONG_FORMAT ";
			}
			return type;
		}

		/**
		 * @brief Get the Value object
		 * 
		 * @return double 
		 */
		virtual double GetValue() = 0;

		/**
		 * @brief Get the Value object
		 * 
		 * @param int 
		 * @return double 
		 */
		virtual double GetValue(unsigned int) = 0;

		/**
		 * @brief Set the Value object
		 */
		virtual void SetValue(double) = 0;

		/**
		 * @brief Set the Value object
		 * 
		 * @param int 
		 */
		virtual void SetValue(double, unsigned int) = 0;

		/* 
		** Common Methods
		*/

	protected:

		/**
		 * @brief 
		 */
		DataType m_type;

		/**
		 * @brief 
		 */
		std::string m_id;

		/**
		 * @brief 
		 */
		int m_varSize;

		/**
		 * @brief 
		 */
		int m_lastUfp;
};