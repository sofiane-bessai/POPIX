#include <Compiler.hpp>

#include <fstream>

#include <Log.hpp>

#include <time.h>

int main(int argc, char** argv) {
	/* Declaration */
	
	std::ofstream outputFilePop;
	std::ofstream outputFileFloat;
	std::ofstream outputFileFix;
	std::ofstream outputFileFixExtended;

	std::string filePath = "./";
	std::string filePathPop = filePath + "output.pop";
	std::string filePathFloat = filePath + "output.c";
	std::string filePathFix = filePath + "output_fix.c";
	std::string filePathFixExtended = filePath + "output_fix_extended.c";

	bool parseResult;
	bool semanticAnalysisResult;

	clock_t begin_dtime = clock();
	clock_t end_dtime;

	/* Initialise */

	g_LogConsole->enableLog(LogLevel::VERBOSE);
	g_LogConsole->enableLog(LogLevel::VERBOSE_PARSER);
	g_LogConsole->enableLog(LogLevel::INFO);
	g_LogConsole->enableLog(LogLevel::DEBUG);
	
	// g_LogConsole->disableLog(LogLevel::WARNING);

	/* Begin */

	g_LogConsole->write(LogLevel::INFO, "Welcome to POPIX an extension of POP");
	g_LogConsole->write(LogLevel::INFO, "Current build : April 2022");
	g_LogConsole->write(LogLevel::INFO, "File analyzed : " + std::string(argv[1]));

	/**
	 * 		PARSING
	 */
	g_LogConsole->write(LogLevel::DEBUG, "parsing begin...");
	parseResult = g_Compiler->Parse(argv[1]);
	if( !parseResult ) {
		g_LogConsole->write(LogLevel::ERROR, "error from parser");
		return EXIT_FAILURE;
	}
	g_LogConsole->write(LogLevel::DEBUG, "parsing done");

	/**
	 * 		SEMANTIC ANALYSIS
	 */
	g_LogConsole->write(LogLevel::DEBUG, "semantic analysis begin...");
	semanticAnalysisResult = g_Compiler->SemanticAnalysis();
	if( !semanticAnalysisResult ) {
		g_LogConsole->write(LogLevel::ERROR, "error from semantic analysis");
		return EXIT_FAILURE;
	}
	g_LogConsole->write(LogLevel::DEBUG, "semantic analysis done");
	
	/**
	 * 
	 */
	g_Compiler->PrintVarList();
	// g_Compiler->m_analytics->PrintInfos();
	// g_Compiler->m_analytics->PrintDataType();

	/**
	 * 		CODE GENERATING
	 */
	g_LogConsole->write(LogLevel::DEBUG, "code generating begin... ");

	// POP
	g_LogConsole->write(LogLevel::DEBUG, "POP file generating... ");
	outputFilePop.open(filePathPop, std::ofstream::out);
	g_Compiler->SetGenerationType(GenerationType::POP);
	g_Compiler->GenerateOutput(outputFilePop);
	outputFilePop.close();

	// FLOAT
	g_LogConsole->write(LogLevel::DEBUG, "FLOAT file generating... ");
	outputFileFloat.open(filePathFloat, std::ofstream::out);
	g_Compiler->SetGenerationType(GenerationType::FLOAT);
	g_Compiler->GenerateOutput(outputFileFloat);
	outputFileFloat.close();

	// FIX
	g_LogConsole->write(LogLevel::DEBUG, "FIX file generating... ");
	outputFileFix.open(filePathFix, std::ofstream::out);
	g_Compiler->SetGenerationType(GenerationType::FIX);
	g_Compiler->GenerateOutput(outputFileFix);
	outputFileFix.close();	

	// FIX EXTENDED
	g_LogConsole->write(LogLevel::DEBUG, "FIX_EXTENDED file generating... ");
	outputFileFixExtended.open(filePathFixExtended, std::ofstream::out);
	g_Compiler->SetGenerationType(GenerationType::FIX_EXTENDED);
	g_Compiler->GenerateOutput(outputFileFixExtended);
	outputFileFixExtended.close();

	g_LogConsole->write(LogLevel::DEBUG, "code generating done");

	end_dtime = clock();
	printf("total execution time : %.3lf ms\n",  (double)( 1000.0 * (end_dtime - begin_dtime) ) / CLOCKS_PER_SEC );

	return EXIT_SUCCESS;
}