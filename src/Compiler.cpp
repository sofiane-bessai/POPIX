#include <Compiler.hpp>

#include <Log.hpp>
#include <Lexer.hpp>
#include <Parser.hpp>

#include <fstream>

#include <fix/fix.hpp>

Compiler *g_Compiler = new Compiler();

Compiler::Compiler() {
	m_analytics = new Analytics();
	m_declarationList = new DeclarationList();
	m_program = nullptr;
}

Compiler::Compiler(StatementList *program) {
	m_analytics = new Analytics();
	m_declarationList = new DeclarationList();
	m_program = program;
}

bool Compiler::Parse(const char *filename) {
	FILE* inputFile;
	
	inputFile = fopen(filename, "r");

	if(filename == nullptr) {
		g_LogConsole->write(LogLevel::FERROR, "no file to compile");
		exit(EXIT_FAILURE);
	}

	if(inputFile == nullptr) {
		g_LogConsole->write(LogLevel::FERROR, "impossible to open file " + std::string(filename));
		exit(EXIT_FAILURE);
	}

	yyrestart(inputFile);

	if( yyparse() ) {
		g_LogConsole->write(LogLevel::ERROR, "an error occured while parsing file " + std::string(filename));
		return false;
	}

	return true;
}

void Compiler::SetGenerationType(GenerationType type) {
	m_generationLangage = type;
}

void Compiler::SetProgram(StatementList *program) {
	m_program = program;
}

VarDeclaration * Compiler::GetDeclaration(std::string id) {
	return m_declarationList->GetDeclaration(id);
}

bool Compiler::IsExist(std::string id) {
	return m_declarationList->IsExist(id);
}

bool Compiler::SemanticAnalysis() {
	bool nameResolutionValue = true;
	bool typeSolvingValue = true;
	bool CollectAnalysisItemValue = true;

	if (m_program == nullptr) {
		g_LogConsole->write(LogLevel::FERROR, "statements list NULL in " + std::string(__PRETTY_FUNCTION__));
		exit(EXIT_FAILURE);
	}
	
	nameResolutionValue = m_program->NameResolution();
	if(!nameResolutionValue) {
		g_LogConsole->write(LogLevel::ERROR, "NameResolution on compiler statements list return false"  " in " + std::string(__PRETTY_FUNCTION__) );
		return false;
	}

	typeSolvingValue = m_program->TypeSolving();
	if(!typeSolvingValue) { 
		g_LogConsole->write(LogLevel::ERROR, "TypeSolving on compiler statements list return false"  " in " + std::string(__PRETTY_FUNCTION__) );
		return false;
	}

	// CollectAnalysisItemValue = m_program->CollectAnalysisItem();
	// if(!CollectAnalysisItemValue) {
	// 	g_LogConsole->write(LogLevel::ERROR, "CollectAnalysisItem on compiler statements list return false"  " in " + std::string(__PRETTY_FUNCTION__) );
	// 	return false;	
	// }

	m_program->EvaluateFloat();

	// m_varList->CollectAnalysisItem();

	return nameResolutionValue && typeSolvingValue && CollectAnalysisItemValue;
}

void Compiler::PrintVarList() {
	m_declarationList->PrintVariables();
}

bool Compiler::AppendVariable(VarDeclaration *singleton) {
	return m_declarationList->AppendVariable(singleton);
}

bool Compiler::GenerateOutput(std::ofstream &outputFile) {
	switch (m_generationLangage) {
		case GenerationType::POP :
			GenerateBody(outputFile);
			break;
		
		case GenerationType::FLOAT :
		case GenerationType::FIX_EXTENDED :
			#ifdef DTIME_EXECUTION
				outputFile << "#include <time.h>" << '\n';
			#endif
			GenerateHeader(outputFile);
			#ifdef DTIME_EXECUTION
				outputFile << "\tclock_t begin_dtime = clock();" << '\n';
				outputFile << "\tclock_t end_dtime;" << '\n';
				outputFile << "\tdouble exec_time;" << '\n';
			#endif
			GenerateBody(outputFile);
			#ifdef DTIME_EXECUTION
				outputFile << "\tend_dtime = clock();" << '\n';
				outputFile << "\texec_time = (double) (end_dtime - begin_dtime) / CLOCKS_PER_SEC;" << '\n';
				outputFile << "\texec_time = exec_time * 1000;" << '\n';
				outputFile << "\tprintf(\"\%.3lf\\n\", exec_time);" << '\n';
			#endif
			GenerateFoot(outputFile);
			break;

		case GenerationType::VHDL :

			break;

		default:
			g_LogConsole->write(LogLevel::ERROR, "Unknow generation function");
			return false;
			break;
	}

	return true;
}

void Compiler::GenerateHeader(std::ofstream &outputFile) {	
	switch (m_generationLangage) {
		case GenerationType::FLOAT :
		case GenerationType::FIX_EXTENDED :
			outputFile << "#include <stdio.h>" << '\n';
			outputFile << "#include <stdlib.h>" << '\n';
			outputFile << "#include <math.h>" << '\n';
			outputFile << "#include <stdint.h>" << '\n';
			outputFile << '\n';
			outputFile << "int main() {" << '\n';
			break;
		case GenerationType::VHDL : g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, "VHDL GenerateHeader"); break;
		default: g_LogConsole->write(LogLevel::ERROR, "Unknow generation function"); break;
	}
}

void Compiler::GenerateBody(std::ofstream &outputFile) {
	std::string declarationListString = "";
	std::string bodyString = "";
	
	switch (m_generationLangage) {
		case GenerationType::POP :
			declarationListString = m_declarationList->ToStringPOP(0);
			bodyString = m_program->ToStringPOP(0);
			break;
		case GenerationType::FLOAT :
			declarationListString = m_declarationList->ToStringFloat(1);
			bodyString = m_program->ToStringFloat(1);
			break;
		case GenerationType::FIX_EXTENDED :
			outputFile << '\t' << "int32_t " << REGISTER_1 << ";" << '\n';
			outputFile << '\t' << "int32_t " << REGISTER_2 << ";" << '\n';
			outputFile << '\t' << "int32_t " << REGISTER_3 << ";" << '\n';
			outputFile << '\t' << "int32_t " << REGISTER_4 << ";" << '\n';
			outputFile << '\t' << "int32_t " << REGISTER_5 << ";" << '\n';
			declarationListString = m_declarationList->ToStringFixExtended(1);
			bodyString = m_program->ToStringFixExtended(1);
			break;
		case GenerationType::VHDL : g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, "VHDL GenerateBody"); break;
		default: g_LogConsole->write(LogLevel::ERROR, "Unknow generation function"); break;
	}
	outputFile << declarationListString << bodyString;
}

void Compiler::GenerateFoot(std::ofstream &outputFile) {
	switch (m_generationLangage) {
		case GenerationType::FLOAT :
		case GenerationType::FIX_EXTENDED :
			outputFile << '\n';
			outputFile << "\treturn 0;" << '\n';
			outputFile << '}' << '\n';
			break;
		case GenerationType::VHDL : g_LogConsole->write(LogLevel::DEBUG, LogError::UNIMPLEMENTED, "VHDL GenerateFoot"); break;
		default: g_LogConsole->write(LogLevel::ERROR, "Unknow generation function"); break;
	}
}