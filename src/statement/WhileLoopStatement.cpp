#include <statement/WhileLoopStatement.hpp>

/* Constructors & Destructor */

WhileLoopStatement::WhileLoopStatement(LogicalExpression *condition, StatementList *loopBody) {
	m_condition = condition;
	m_loopBody= loopBody;
}

/* Statement Methods */

bool WhileLoopStatement::NameResolution() {
	return m_condition->NameResolution() && m_loopBody->NameResolution();
}

bool WhileLoopStatement::TypeSolving() {
	return m_condition->TypeSolving() && m_loopBody->TypeSolving();
}

bool WhileLoopStatement::CollectAnalysisItem() {
	return m_condition->CollectAnalysisItem() && m_loopBody->CollectAnalysisItem();
}

// potential halting problem
double WhileLoopStatement::EvaluateFloat() {
	while ( (bool) m_condition->EvaluateFloat() )
		m_loopBody->EvaluateFloat();
	return 0.0;
}

std::string WhileLoopStatement::ToStringPOP(int depth) {
	std::string conditionString;
	std::string bodyString;

	conditionString = m_condition->ToStringPOP(0);
	bodyString = m_loopBody->ToStringPOP(depth+1);

	return Indent(depth) + "while(" + conditionString + ") {\n" + bodyString + Indent(depth) + "}\n";
}

std::string WhileLoopStatement::ToStringFloat(int depth) {
	std::string conditionString;
	std::string bodyString;

	conditionString = m_condition->ToStringFloat(0);
	bodyString = m_loopBody->ToStringFloat(depth+1);

	return Indent(depth) + "while(" + conditionString + ") {\n" + bodyString + Indent(depth) + "}\n";
}

std::string WhileLoopStatement::ToStringFix(int depth) {
	std::string conditionString;
	std::string bodyString;

	conditionString = m_condition->ToStringFix(0);
	bodyString = m_loopBody->ToStringFix(depth+1);

	return Indent(depth) + "while(" + conditionString + ") {\n" + bodyString + Indent(depth) + "}\n";
}

std::string WhileLoopStatement::ToStringFixExtended(int depth) {
	std::string conditionString;
	std::string bodyString;

	conditionString = m_condition->ToStringFixExtended(0);
	bodyString = m_loopBody->ToStringFixExtended(depth+1);

	return Indent(depth) + "while(" + conditionString + ") {\n" + bodyString + Indent(depth) + "}\n";
}