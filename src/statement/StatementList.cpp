#include <statement/StatementList.hpp>

/* Constructors & Destructor */
// no methods

/* Methods */

void StatementList::AppendStatement(Statement *statement) {
	if(statement != nullptr) {
		m_statements.push_back(statement);
	}
}

/* Statement Methods */

bool StatementList::NameResolution() {
	bool statementValue = false;
	for(const auto &statement : m_statements) {
		statementValue = statement->NameResolution();
		if(!statementValue) {
			g_LogConsole->write(LogLevel::ERROR, LogError::NAME_RESOLUTION, statement->m_lineno, __PRETTY_FUNCTION__);
			break;
		}
	}
	return statementValue;
}

bool StatementList::TypeSolving() {
	bool statementValue = false;
	for(const auto &statement : m_statements) {
		statementValue = statement->TypeSolving();
		if(!statementValue) {
			g_LogConsole->write(LogLevel::ERROR, LogError::TYPE_SOLVING, statement->m_lineno, __PRETTY_FUNCTION__);
			break;
		}
	}
	return statementValue;
}

bool StatementList::CollectAnalysisItem() {
	bool statementValue = false;
	for(const auto &statement : m_statements) {
		statementValue = statement->CollectAnalysisItem();
		if(!statementValue) {
			g_LogConsole->write(LogLevel::ERROR, LogError::COLLECT_ANALYSIS_ITEM, statement->m_lineno, __PRETTY_FUNCTION__);
			break;
		}
	}
	return statementValue;
}

double StatementList::EvaluateFloat() {
	for(const auto &statement : m_statements)
		statement->EvaluateFloat();
	return 0.0;
}

std::string StatementList::ToStringPOP(int depth) {
	std::string statementListString = "";
	std::string statementString;

	for(const auto &statement : m_statements) {
		statementString = statement->ToStringPOP(depth);
		statementListString += statementString;
	}

	return statementListString;
}

std::string StatementList::ToStringFloat(int depth) {
	std::string statementListString = "";
	std::string statementString;

	for(const auto &statement : m_statements) {
		statementString = statement->ToStringFloat(depth);
		statementListString += statementString;
	}

	return statementListString;
}

std::string StatementList::ToStringFix(int depth) {
	std::string statementListString = "";
	std::string statementString;

	for(const auto &statement : m_statements) {
		statementString = statement->ToStringFix(depth);
		statementListString += statementString;
	}

	return statementListString;
}

std::string StatementList::ToStringFixExtended(int depth) {
	std::string statementListString = "";
	std::string statementString;

	for(const auto &statement : m_statements) {
		statementString = statement->ToStringFixExtended(depth);
		statementListString += statementString;
	}

	return statementListString;
}