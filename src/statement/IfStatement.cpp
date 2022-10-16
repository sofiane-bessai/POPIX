#include <statement/IfStatement.hpp>

/* Constructors & Destructor */

IfStatement::IfStatement(LogicalExpression *condition, StatementList *ifBody){
	m_condition = condition;
	m_ifBody = ifBody;
	m_elseBody = nullptr;
}

IfStatement::IfStatement(LogicalExpression *condition, StatementList *ifBody, StatementList *elseBody) {
	m_condition = condition;
	m_ifBody = ifBody;
	m_elseBody = elseBody;
}

/* Statement Methods */

bool IfStatement::NameResolution() {
	if(m_elseBody == nullptr)
		return m_condition->NameResolution() && m_ifBody->NameResolution();
	else
		return m_condition->NameResolution() && m_ifBody->NameResolution() && m_elseBody->NameResolution();
}

bool IfStatement::TypeSolving() {
	if(m_elseBody == nullptr)
		return m_condition->TypeSolving() && m_ifBody->TypeSolving();
	else
		return m_condition->TypeSolving() && m_ifBody->TypeSolving() && m_elseBody->TypeSolving();
}

bool IfStatement::CollectAnalysisItem() {
	if(m_elseBody == nullptr)
		return m_condition->CollectAnalysisItem() && m_ifBody->CollectAnalysisItem();
	else
		return m_condition->CollectAnalysisItem() && m_ifBody->CollectAnalysisItem() && m_elseBody->CollectAnalysisItem();
}

double IfStatement::EvaluateFloat() {
	if( (bool) m_condition->EvaluateFloat() )
		m_ifBody->EvaluateFloat();
	else
		if(m_elseBody != nullptr)
			m_elseBody->EvaluateFloat();
	return 0.0;
}

std::string IfStatement::ToStringPOP(int depth) {
	std::string conditionString;
	std::string ifBodyString;
	std::string elseBodyString;

	conditionString = Indent(depth) + "if(" + m_condition->ToStringPOP(0) + ") {\n";
	ifBodyString = m_ifBody->ToStringPOP(depth+1) + Indent(depth) + "}\n";
	if(m_elseBody != nullptr)
		elseBodyString = Indent(depth) + "else {\n" + m_elseBody->ToStringPOP(depth+1) + Indent(depth) + "}\n";
	else
		elseBodyString = "";

	return conditionString + ifBodyString + elseBodyString;
}

std::string IfStatement::ToStringFloat(int depth) {
	std::string conditionString;
	std::string ifBodyString;
	std::string elseBodyString;

	conditionString = Indent(depth) + "if(" + m_condition->ToStringFloat(0) + ") {\n";
	ifBodyString = m_ifBody->ToStringFloat(depth+1) + Indent(depth) + "}\n";
	if(m_elseBody != nullptr)
		elseBodyString = Indent(depth) + "else {\n" + m_elseBody->ToStringFloat(depth+1) + Indent(depth) + "}\n";
	else
		elseBodyString = "";

	return conditionString + ifBodyString + elseBodyString;
}

std::string IfStatement::ToStringFixExtended(int depth) {
	std::string conditionString;
	std::string ifBodyString;
	std::string elseBodyString;

	conditionString = Indent(depth) + "if(" + m_condition->ToStringFixExtended(0) + ") {\n";
	ifBodyString = m_ifBody->ToStringFixExtended(depth+1) + Indent(depth) + "}\n";
	if(m_elseBody != nullptr)
		elseBodyString = Indent(depth) + "else {\n" + m_elseBody->ToStringFixExtended(depth+1) + Indent(depth) + "}\n";
	else
		elseBodyString = "";

	return conditionString + ifBodyString + elseBodyString;
}