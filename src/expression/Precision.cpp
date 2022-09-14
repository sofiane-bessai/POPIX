#include <expression/Precision.hpp>


/* Statement Methods */

bool Precision::NameResolution() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return false;
}

bool Precision::TypeSolving() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return false;
}

bool Precision::CollectAnalysisItem() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return false;
}

double Precision::EvaluateFloat() {
	return 0.0;
}

std::string Precision::ToStringPOP(int depth) {
	std::string precisionString;

	if(m_length == UNDEFINED_LENGTH && m_ufp == UNDEFINED_UFP)
		precisionString = "";
	else if(m_ufp == UNDEFINED_UFP)
		precisionString = "|" + std::to_string(m_length) + "|";
	else
		precisionString = "|" + std::to_string(m_ufp) + ", " + std::to_string(m_length) + "|";
	
	return precisionString;
}

std::string Precision::ToStringFloat(int depth) {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return __PRETTY_FUNCTION__;
}

std::string Precision::ToStringFixExtended(int depth) {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return __PRETTY_FUNCTION__;
}