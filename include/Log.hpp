#pragma once

#include <iosfwd>
#include <map>

#define PRINT_COLORS true

#if PRINT_COLORS
	
	#define COLOR_RESET     std::string("\033[0m")

	#define COLOR_BLACK     std::string("\033[30m")
	#define COLOR_RED       std::string("\033[31m")
	#define COLOR_GREEN		std::string("\033[32m")
	#define COLOR_YELLOW	std::string("\033[33m")
	#define COLOR_BLUE		std::string("\033[34m")
	#define COLOR_MAGENTA	std::string("\033[35m")
	#define COLOR_CYAN		std::string("\033[36m")
	#define COLOR_WHITE		std::string("\033[37m")

#else

	#define COLOR_RESET     std::string("")

	#define COLOR_BLACK     std::string("")
	#define COLOR_RED       std::string("")
	#define COLOR_GREEN		std::string("")
	#define COLOR_YELLOW	std::string("")
	#define COLOR_BLUE		std::string("")
	#define COLOR_MAGENTA	std::string("")
	#define COLOR_CYAN		std::string("")
	#define COLOR_WHITE		std::string("")

#endif

/**
 * @brief 
 */
enum LogLevel {
	VERBOSE,
	VERBOSE_PARSER,
	INFO,
	DEBUG,
	WARNING,
	ERROR,
	FERROR
};

/**
 * @brief 
 */
enum LogError {
	NULL_PTR,
	UNDECLARED_ELEMENT,
	UNIMPLEMENTED,
	NAME_RESOLUTION,
	TYPE_SOLVING,
	COLLECT_ANALYSIS_ITEM,
	COMPOSED_EXPRESSION,
	COMPOSED_CALL_EXPRESSION,
	UNHANDLED_CASE
};

/**
 * @brief 
 */
class LogConsole {
	public:

		/**
		 * @brief Construct a new Log Console object
		 */
		LogConsole();

		/**
		 * @brief 
		 */
		void disableLog(LogLevel);
		
		/**
		 * @brief 
		 */
		void enableLog(LogLevel);

		/**
		 * @brief 
		 */
		void write(std::string);
		
		/**
		 * @brief 
		 */
		void write(std::string, int);
		
		/**
		 * @brief 
		 */
		void write(LogLevel, std::string);
		
		/**
		 * @brief 
		 */
		void write(LogLevel, LogError);
		
		/**
		 * @brief 
		 */
		void write(LogLevel, LogError, int);
		
		/**
		 * @brief 
		 */
		void write(LogLevel, LogError, std::string);
		
		/**
		 * @brief 
		 */
		void write(LogLevel, LogError, int, std::string);

	private:

		/**
		 * @brief 
		 */
		std::ostream *m_output;
		
		/**
		 * @brief 
		 */
		std::map <LogLevel, std::string> m_logPrefix;
		
		/**
		 * @brief 
		 */
		std::map <LogLevel, bool> m_logAuthorized;
		
		/**
		 * @brief 
		 */
		std::map <LogError, std::string> m_errorMessage;
};

/**
 * @brief 
 */
extern LogConsole *g_LogConsole;