#include <statement/AssignmentStatement.hpp>

#include <fix/fix.hpp>

/* Constructors & Destructor */

AssignmentStatement::AssignmentStatement(VarInstance *var, Expression *expr) {
	m_variable = var;
	m_expression = expr;
	m_value = 0.0;
}

bool AssignmentStatement::IsIntegerAssignment() {
	return m_variable->IsIntegerExpression() && m_expression->IsIntegerExpression();
}

/* Statement Methods */

bool AssignmentStatement::NameResolution() {
	bool expressionValue;

	m_variable->DeclareElement();
	expressionValue = m_expression->NameResolution();
	if( !expressionValue ) g_LogConsole->write(LogLevel::ERROR, LogError::NAME_RESOLUTION, m_lineno, __PRETTY_FUNCTION__);
	return expressionValue;
}

bool AssignmentStatement::TypeSolving() {
	return m_variable->TypeSolving() && m_expression->TypeSolving();
}

bool AssignmentStatement::CollectAnalysisItem() {
	return m_variable->CollectAnalysisItem() && m_expression->CollectAnalysisItem();
}

double AssignmentStatement::EvaluateFloat() {
	double result = m_expression->EvaluateFloat();
	m_variable->SetValue(result);
	m_value = result;
	return result;
}

std::string AssignmentStatement::ToStringPOP(int depth) {
	std::string variableString = "";
	std::string expressionString= "";

	variableString = m_variable->ToStringPOP(0);
	expressionString = m_expression->ToStringPOP(0);

	return Indent(depth) + variableString + " = " + expressionString + ";\n";
}

std::string AssignmentStatement::ToStringFloat(int depth) {
	return Indent(depth) + m_variable->ToStringFloat(0) + " = " + m_expression->ToStringFloat(0) + ";\n";
}

std::string AssignmentStatement::ToStringFixExtended(int depth) {
	if(IsIntegerAssignment()) {
		return Indent(depth) + m_variable->ToStringFixExtended(0) + " = " + m_expression->ToStringFixExtended(0) + ";\n";
	}
	else {
		return FPGen_assignment(depth, m_variable, m_expression);
	}
}