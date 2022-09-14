#include <expression/SingletonInstance.hpp>

#include <Compiler.hpp>
#include <declaration/SingletonDeclaration.hpp>

/* Constructors & Destructor */

SingletonInstance::SingletonInstance(std::string id) : VarInstance(id) {}
SingletonInstance::SingletonInstance(std::string id, Precision *precision) : VarInstance(id, precision) {}

/* VarInstance */
void SingletonInstance::DeclareElement() {
	g_Compiler->AppendVariable(new SingletonDeclaration(m_id, m_precision));
}

void SingletonInstance::SetValue(double value) {
	VarDeclaration *declaration = g_Compiler->GetDeclaration(m_id);
	if(declaration == nullptr) {
		g_LogConsole->write(LogLevel::FERROR, __PRETTY_FUNCTION__);
		exit(EXIT_FAILURE);
	}
	declaration->SetValue(value);
}

/* ConstantExpression */
// no methods

/* Expression Methods */

bool SingletonInstance::IsIntegerExpression() {
	if(g_Compiler->GetDeclaration(m_id)->GetType() == DataType::INT)
		return true;
	else
		return false;
}

void SingletonInstance::SetExpressionType(DataType type) {
	g_Compiler->GetDeclaration(m_id)->SetType(type);
	m_type = type;
}

/* Statement Methods */

bool SingletonInstance::NameResolution() {
	return g_Compiler->IsExist(m_id);
}

bool SingletonInstance::TypeSolving() {
	m_type = g_Compiler->GetDeclaration(m_id)->GetType();
	return true;
}

bool SingletonInstance::CollectAnalysisItem() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return false;
}

double SingletonInstance::EvaluateFloat() {
	VarDeclaration *declaration = g_Compiler->GetDeclaration(m_id);
	if(declaration == nullptr) {
		g_LogConsole->write(LogLevel::FERROR, __PRETTY_FUNCTION__);
		exit(EXIT_FAILURE);
	}
	m_evaluatedValue = declaration->GetValue();
	return m_evaluatedValue;
}

std::string SingletonInstance::ToStringPOP(int depth) {
	return m_id + m_precision->ToStringPOP(0);
}

std::string SingletonInstance::ToStringFloat(int depth) {
	return m_id;
}

std::string SingletonInstance::ToStringFixExtended(int depth) {
	return m_id;
}