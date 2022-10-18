#include <expression/Scalar.hpp>

#include <math.h>

#include <sstream>

/* Constructors & Destructor */

Scalar::Scalar(double value) : ConstantExpression() {
	m_value = value;
}

Scalar::Scalar(double value, Precision *precision) : ConstantExpression(precision) {
	m_value = value;
}

/* ConstantExpression Methods */
// no methods

/* Expression Methods */

bool Scalar::IsIntegerExpression() {
	int X = m_value;
	if(this->m_value - X != 0)
		return false;
	return true;
}

/* Statement Methods */

bool Scalar::NameResolution() {
	return true;
}

bool Scalar::TypeSolving() {
	return true;
}

bool Scalar::CollectAnalysisItem() {
	return true;
}

double Scalar::EvaluateFloat() {
	m_evaluatedValue = m_value;
	return m_value;
}

std::string Scalar::ToStringPOP(int depth) {
	std::string scalarString;
	std::ostringstream out;

	if(IsIntegerExpression())
		scalarString = std::to_string( (int) m_value);
	else {
		out.precision(8);
		out << std::fixed << m_value;
		scalarString = out.str();
	}

	return scalarString + m_precision->ToStringPOP(0);
}

std::string Scalar::ToStringFloat(int depth) {
	std::string scalarString;
	std::ostringstream out;

	if(IsIntegerExpression())
		scalarString = std::to_string( (int) m_value);
	else {
		out.precision(8);
		out << std::fixed << m_value;
		scalarString = out.str();
	}

	return scalarString;
}

std::string Scalar::ToStringFixExtended(int depth) {
	std::string scalarString;
	
	if(IsIntegerExpression())
		scalarString = std::to_string( (int) m_value);
	else {
		int ufp = m_precision->GetUfp();
		int length = m_precision->GetLength();
		int ulp = ( length == ufp ) ? 1 : length - abs(ufp);

		g_LogConsole->write(LogLevel::DEBUG, std::to_string(ufp) + ", " + std::to_string(ulp) + ", " + std::to_string(length));

		double value = ( this->m_value / ( pow(2, ( -ulp ) ) ) );
		int valueFix = (int) round(value);

		scalarString = std::to_string(valueFix);
	}

	return scalarString;
}