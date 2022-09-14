#include <Log.hpp>
#include <iostream>

LogConsole *g_LogConsole = new LogConsole();

LogConsole::LogConsole() : m_output(&std::cout) {
	m_logPrefix[VERBOSE]    	= COLOR_GREEN   + "[verbose] "      	+ COLOR_RESET;
	m_logPrefix[VERBOSE_PARSER] = COLOR_GREEN   + "[verbose parser] " 	+ COLOR_RESET;
	m_logPrefix[INFO]       	= COLOR_BLUE    + "[info] "         	+ COLOR_RESET;
	m_logPrefix[DEBUG]      	= COLOR_MAGENTA + "[debug] "        	+ COLOR_RESET;
	m_logPrefix[WARNING]    	= COLOR_YELLOW  + "[warning] "      	+ COLOR_RESET;
	m_logPrefix[ERROR]      	= COLOR_RED     + "[error] "        	+ COLOR_RESET;
	m_logPrefix[FERROR]     	= COLOR_RED     + "[fatal error] "  	+ COLOR_RESET;

	m_logAuthorized[VERBOSE] = false;
	m_logAuthorized[VERBOSE_PARSER] = false;
	m_logAuthorized[INFO] = false;
	m_logAuthorized[DEBUG] = false;
	m_logAuthorized[WARNING] = true;
	m_logAuthorized[ERROR] = true;
	m_logAuthorized[FERROR] = true;

	m_errorMessage[NULL_PTR] = "pointer null ";
	m_errorMessage[UNDECLARED_ELEMENT] = "undeclared element ";
	m_errorMessage[UNIMPLEMENTED] = "unimplemented ";
	m_errorMessage[NAME_RESOLUTION] = "can't resolve name ";
	m_errorMessage[TYPE_SOLVING] = "can't solve type ";
	m_errorMessage[COLLECT_ANALYSIS_ITEM] = "can't collect analysis item ";
	m_errorMessage[COMPOSED_EXPRESSION] = "composed expression ";
	m_errorMessage[COMPOSED_CALL_EXPRESSION] = "composed call expression ";
	m_errorMessage[UNHANDLED_CASE] = "unhandled case ";
}

void LogConsole::disableLog(LogLevel level) {
	m_logAuthorized[level] = false;
}

void LogConsole::enableLog(LogLevel level) {
	m_logAuthorized[level] = true;
}

void LogConsole::write(std::string msg) {
	*this->m_output << msg;
}

void LogConsole::write(LogLevel level, std::string msg) {
	if(m_logAuthorized[level])
		*this->m_output << m_logPrefix[level] << msg << '\n';
}

void LogConsole::write(LogLevel level, LogError error_code) {
	if(m_logAuthorized[level])
		*this->m_output << m_logPrefix[level] << m_errorMessage[error_code] << '\n';
}

void LogConsole::write(LogLevel level, LogError error_code, std::string msg) {
	if(m_logAuthorized[level])
		*this->m_output << m_logPrefix[level] << m_errorMessage[error_code] << '(' << msg << ')' << '\n';
}

void LogConsole::write(LogLevel level, LogError error_code, int line) {
	if(m_logAuthorized[level])
		*this->m_output << m_logPrefix[level] << "at line " << line << ' ' << m_errorMessage[error_code] << '\n';
}

void LogConsole::write(LogLevel level, LogError error_code, int line, std::string msg) {
	if(m_logAuthorized[level])
		*this->m_output << m_logPrefix[level] << "at line " << line << ' ' << m_errorMessage[error_code] << '(' << msg << ')' << '\n';
}