#include <declaration/VectorDeclaration.hpp>

/* Constructors & Destructor */

VectorDeclaration::VectorDeclaration(std::string id, int length) : VarDeclaration(id), m_value(length, 0.0) {
	m_length = length;
}

VectorDeclaration::VectorDeclaration(std::string id, int length, Precision *precision) : VarDeclaration(id, precision), m_value(length, 0.0) {
	m_length = length;
}

double VectorDeclaration::GetValue() {
	return m_value[0];
}

double VectorDeclaration::GetValue(unsigned int index) {
	if(index < (unsigned int) m_length)
		return m_value[index];
	return 0.0;
}

void VectorDeclaration::SetValue(double value) {
	m_value[0] = value;
}

void VectorDeclaration::SetValue(double value, unsigned int index) {
	if(index < (unsigned int) m_length)
		m_value[index] = value;
	else {
		g_LogConsole->write(LogLevel::FERROR, __PRETTY_FUNCTION__); // add out of bound error code
		exit(EXIT_FAILURE);
	}
}

/* VarDeclaration Methods */

int VectorDeclaration::GetSize() {
	return m_length;
}

/* Statement Methods */

bool VectorDeclaration::NameResolution() {
	return false;
}

bool VectorDeclaration::TypeSolving() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return false;
}

bool VectorDeclaration::CollectAnalysisItem() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return false;
}

double VectorDeclaration::EvaluateFloat() {
	return 0.0;
}

std::string VectorDeclaration::ToStringPOP(int depth) {
	return Indent(depth) + "create_vector(" + m_id + "," + std::to_string(m_length) + ");" + '\n';
}

std::string VectorDeclaration::ToStringFloat(int depth) {
	return Indent(depth) + GetFloatType() + m_id + '[' + std::to_string(m_length) + ']' + ';' + '\n';
}

std::string VectorDeclaration::ToStringFixExtended(int depth) {
	return Indent(depth) + GetFixExtendedType() + m_id + '[' + std::to_string(m_length) + ']' + ';' + '\n';
}