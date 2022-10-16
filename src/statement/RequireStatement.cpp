#include <statement/RequireStatement.hpp>

#include <Compiler.hpp>

/* Constructors & Destructor */

RequireStatement::RequireStatement(std::string id, int nsb) {
	m_id = id;
	m_nsb = nsb;
}

/* Statement Methods */

bool RequireStatement::NameResolution() {
	// g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return true;
}

bool RequireStatement::TypeSolving() {
	// g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return true;
}

bool RequireStatement::CollectAnalysisItem() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return true;
}

double RequireStatement::EvaluateFloat() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return 0.0;
}

std::string RequireStatement::ToStringPOP(int depth) {
	return Indent(depth) + "require_accuracy(" + m_id + ", " + std::to_string(m_nsb) + ");" + '\n';
}

std::string RequireStatement::ToStringFloat(int depth) {
	#ifdef PRINT_RESULT
		return Indent(depth) + "printf(\"\%lf\\n\", " + m_id + ");" + '\n';
	#else
		return "";
	#endif
}

std::string RequireStatement::ToStringFixExtended(int depth) {
	#ifdef PRINT_RESULT
		return Indent(depth) + "printf(\"\%lf\\n\", " + m_id + ");" + '\n';
	#else
		return "";
	#endif
}