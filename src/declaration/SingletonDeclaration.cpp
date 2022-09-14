#include <declaration/SingletonDeclaration.hpp>

#include <Compiler.hpp>

/* Constructors & Destructor */

SingletonDeclaration::SingletonDeclaration(std::string id) : VarDeclaration(id) {
    m_value = 0.0;
}

SingletonDeclaration::SingletonDeclaration(std::string id, Precision *precision) : VarDeclaration(id, precision) {
    m_value = 0.0;
}

double SingletonDeclaration::GetValue() {
	return m_value;
}

double SingletonDeclaration::GetValue(unsigned int) {
	return m_value;
}

void SingletonDeclaration::SetValue(double value) {
	m_value = value;
}

void SingletonDeclaration::SetValue(double value, unsigned int index) {
	m_value = value;
}

/* VarDeclaration Methods */

int SingletonDeclaration::GetSize() {
	return 1;
}

/* Statement Methods */

bool SingletonDeclaration::NameResolution() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return false;
}

bool SingletonDeclaration::TypeSolving() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return false;
}

bool SingletonDeclaration::CollectAnalysisItem() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return false;
}

double SingletonDeclaration::EvaluateFloat() {
	return 0.0;
}

std::string SingletonDeclaration::ToStringPOP(int depth) {
	return "";
}

std::string SingletonDeclaration::ToStringFloat(int depth) {
	return Indent(depth) + GetFloatType() + m_id + ';' + '\n';
}

std::string SingletonDeclaration::ToStringFixExtended(int depth) {
	return Indent(depth) + GetFixExtendedType() + m_id + ';' + '\n';
}