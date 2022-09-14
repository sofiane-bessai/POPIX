#include <statement/DeclarationList.hpp>

/* Constructors & Destructor */

DeclarationList::DeclarationList() {}

/* Methods */

void DeclarationList::ModifyLength(std::string, int) {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, m_lineno, __PRETTY_FUNCTION__);
}

void DeclarationList::ModifyUfp(std::string, int) {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, m_lineno, __PRETTY_FUNCTION__);
}

int DeclarationList::GetListSize() {
	return m_variables.size();
}

int DeclarationList::GetLengthFromId(std::string) {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return 0;
}

int DeclarationList::GetMaxIdSize() {
	return m_maxIdSize;
}

VarDeclaration * DeclarationList::GetDeclaration(std::string id) {
	const auto &var = m_variables.find(id);
	return ( var == m_variables.end() ) ? nullptr : var->second;
}

bool DeclarationList::AppendVariable(VarDeclaration *declaration) {
	int varIdSize = declaration->GetId().length();
	m_maxIdSize = (varIdSize > m_maxIdSize) ? varIdSize : m_maxIdSize;
	std::pair<std::string, VarDeclaration *> element_declaration (declaration->GetId(), declaration);
	this->m_variables.insert(element_declaration);
	return true;
}

bool DeclarationList::IsExist(std::string id) {
	const auto &var = m_variables.find(id);
	return ( var == m_variables.end() ) ? false : true;
}

void DeclarationList::PrintVariables() {
	VarDeclaration *decl;
	std::string id;
	int size;
	int varSize;
	int lastUfp;
	std::string type;
	g_LogConsole->write(LogLevel::INFO, "Ce programme contient " + std::to_string(m_variables.size()) + " variables");
	g_LogConsole->write(LogLevel::INFO, "+------+--" + std::string(m_maxIdSize, '-') + "+-------------+---------------+---------------+");
	g_LogConsole->write(LogLevel::INFO, "| TYPE | ID" + std::string(m_maxIdSize-2, ' ') + " | " + "SIZE" + "\t| " + "VAR_SIZE" + "\t| " + "LAST_UFP" + "\t|");
	g_LogConsole->write(LogLevel::INFO, "+------+--" + std::string(m_maxIdSize, '-') + "+-------------+---------------+---------------+");
	for(const auto &var : m_variables) {
		decl = var.second;
		id = decl->GetId();
		size = decl->GetSize();
		varSize = decl->GetVarSize();
		lastUfp = decl->GetLastUfp();
		type = (decl->GetType() == DataType::REAL) ? "REAL" : "INT ";
		g_LogConsole->write(LogLevel::INFO, "| " + type + " | " + id + std::string(m_maxIdSize-id.length(), ' ') + " | " + std::to_string(size) + "\t| " + std::to_string(varSize) + "\t\t| " + std::to_string(lastUfp) + "\t\t|");
	}
	g_LogConsole->write(LogLevel::INFO, "+------+--" + std::string(m_maxIdSize, '-') + "+-------------+---------------+---------------+");
}

/* Statement Methods */

bool DeclarationList::NameResolution() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return false;
}

bool DeclarationList::TypeSolving() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return false;
}

bool DeclarationList::CollectAnalysisItem() {
	g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, __PRETTY_FUNCTION__);
	return false;
}

double DeclarationList::EvaluateFloat() {
	return 0.0;
}

std::string DeclarationList::ToStringPOP(int depth) {
	std::string declarationListString;
	std::string declarationString;
	
	for(const auto &var : m_variables) {
		declarationString = var.second->ToStringPOP(depth);
		declarationListString += declarationString;
	}

	return declarationListString;
}

std::string DeclarationList::ToStringFloat(int depth) {
	std::string declarationListString;
	std::string declarationString;
	for(const auto &var : m_variables) {
		declarationString = var.second->ToStringFloat(depth);
		declarationListString += declarationString;
	}
	return declarationListString;
}

std::string DeclarationList::ToStringFixExtended(int depth) {
	std::string declarationListString;
	std::string declarationString;
	for(const auto &var : m_variables) {
		declarationString = var.second->ToStringFixExtended(depth);
		declarationListString += declarationString;
	}
	return declarationListString;
}