#include <expression/VectorInstance.hpp>
#include <Compiler.hpp>

/* Constructors & Destructor */

VectorInstance::VectorInstance(std::string id, ArithmeticExpression *index) : VarInstance(id) {
	m_indexExpr = index;
}

VectorInstance::VectorInstance(std::string id, ArithmeticExpression *index, Precision *precision) : VarInstance(id, precision) {
	m_indexExpr = index;
}

/* VarInstance */
void VectorInstance::DeclareElement() {
	g_Compiler->GetDeclaration(m_id)->SetMaxVarSize(m_precision->GetLength());
}

void VectorInstance::SetValue(double value) {
	unsigned int index = (unsigned int) m_indexExpr->EvaluateFloat();
	VarDeclaration *declaration = g_Compiler->GetDeclaration(m_id);
	if(declaration == nullptr) {
		g_LogConsole->write(LogLevel::FERROR, __PRETTY_FUNCTION__);
		exit(EXIT_FAILURE);
	}
	declaration->SetValue(value, index);
}

/* ConstantExpression */
// no methods

/* Expression Methods */

bool VectorInstance::IsIntegerExpression() {
	if(g_Compiler->GetDeclaration(m_id)->GetType() == DataType::INT)
		return true;
	else
		return false;
}

void VectorInstance::SetExpressionType(DataType type) {
	g_Compiler->GetDeclaration(m_id)->SetType(type);
	m_type = type;
}

/* Statement Methods */

bool VectorInstance::NameResolution() {
	return g_Compiler->IsExist(m_id);
}

bool VectorInstance::TypeSolving() {
	// g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	m_indexExpr->SetExpressionType(DataType::INT);
	m_type = g_Compiler->GetDeclaration(m_id)->GetType();
	return true;
}

bool VectorInstance::CollectAnalysisItem() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return false;
}

double VectorInstance::EvaluateFloat() {
	unsigned int index = (unsigned int) m_indexExpr->EvaluateFloat();
	VarDeclaration *declaration = g_Compiler->GetDeclaration(m_id);
	if(declaration == nullptr) {
		g_LogConsole->write(LogLevel::FERROR, __PRETTY_FUNCTION__);
		exit(EXIT_FAILURE);
	}
	m_evaluatedValue = declaration->GetValue(index);
	return m_evaluatedValue;
}

std::string VectorInstance::ToStringPOP(int depth) {
	return m_id + "[" + m_indexExpr->ToStringPOP(0) + "]" + m_precision->ToStringPOP(0);
}

std::string VectorInstance::ToStringFloat(int depth) {
	return m_id + "[" + m_indexExpr->ToStringFloat(0) + "]";
}

std::string VectorInstance::ToStringFixExtended(int depth) {
	return m_id + "[" + m_indexExpr->ToStringFixExtended(0) + "]";
}