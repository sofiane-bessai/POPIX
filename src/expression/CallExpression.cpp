#include <expression/CallExpression.hpp>

#include <math.h>

/* Constructors & Destructor */

CallExpression::CallExpression(std::string id, Expression *arg, Precision *precision) : ConstantExpression(precision) {
	m_identifier = id;
	m_argument = arg;
	m_callType = CallExpressionType::UNHANDLED;
}

CallExpression::CallExpression(std::string id, Expression *arg, Precision *precision, CallExpressionType type) : ConstantExpression(precision) {
	m_identifier = id;
	m_argument = arg;
	m_callType = type;
}

CallExpression::CallExpressionType CallExpression::GetCallType() {
	return m_callType;
}

Expression * CallExpression::GetArg() {
	return m_argument;
}

/* Expression Methods */

// Can create bug if the arg is real
bool CallExpression::IsIntegerExpression() {
	g_LogConsole->write(LogLevel::WARNING, __PRETTY_FUNCTION__);
	return (m_identifier == "abs") ? true : false;
}

/* Statement Methods */

bool CallExpression::NameResolution() {
	if(m_identifier == "abs")
		m_callType = CallExpressionType::ABS;
	else if(m_identifier == "sqrt")
		m_callType = CallExpressionType::SQRT;
	else if(m_identifier == "sin")
		m_callType = CallExpressionType::SIN;
	else if(m_identifier == "cos")
		m_callType = CallExpressionType::COS;
	else if(m_identifier == "atan")
		m_callType = CallExpressionType::ATAN;
	else
		m_callType = CallExpressionType::UNHANDLED;
	return true;
}

bool CallExpression::TypeSolving() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return true;
}

bool CallExpression::CollectAnalysisItem() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return true;
}

double CallExpression::EvaluateFloat() {
	double result = 0.0;
	double arg = 0.0;
	arg = m_argument->EvaluateFloat();
	switch (this->m_callType) {
		case CallExpressionType::SQRT : result = sqrt(arg); break;
		case CallExpressionType::ABS : result = abs(arg); break;
		case CallExpressionType::SIN : result = sin(arg); break;
		case CallExpressionType::COS : result = cos(arg); break;
		case CallExpressionType::ATAN : result = atan(arg); break;
		case CallExpressionType::UNHANDLED :
			g_LogConsole->write(LogLevel::ERROR, LogError::UNHANDLED_CASE, __PRETTY_FUNCTION__);
		break;
	}
	m_evaluatedValue = result;
	return result;
}

std::string CallExpression::ToStringPOP(int depth) {
	return m_identifier + "(" + m_argument->ToStringPOP(0) + ")" + m_precision->ToStringPOP(0);
}

std::string CallExpression::ToStringFloat(int depth) {
	return m_identifier + "(" + m_argument->ToStringFloat(0) + ")";
}

std::string CallExpression::ToStringFixExtended(int depth) {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return __PRETTY_FUNCTION__;
}