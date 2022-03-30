#ifndef util_Log_h
#define util_Log_h

#include <iostream>

/// <summary>
/// A utility class for doing logging across the engine.
/// </summary>
class OLog
{
public:
	inline static void Info(const char* const message, const bool isEngine, const char* const endl = "\n")
	{
		Print((isEngine) ? _enginePrefix : "", message, endl, _infoInfix);
	}
	inline static void Info(const char* const message, const char* const prefix = "", const char* const endl = "\n")
	{
		Print(prefix, message, endl, _infoInfix);
	}

	inline static void Warn(const char* const message, const bool isEngine, const char* const endl = "\n")
	{
		Print((isEngine) ? _enginePrefix : "", message, endl, _warnInfix);
	}
	inline static void Warn(const char* const message, const char* const prefix = "", const char* const endl = "\n")
	{
		Print(prefix, message, endl, _warnInfix);
	}

	inline static void Error(const char* const message, const bool isEngine, const char* const endl = "\n")
	{
		Print((isEngine) ? _enginePrefix : "", message, endl, _errInfix);
	}
	inline static void Error(const char* const message, const char* const prefix = "", const char* const endl = "\n")
	{
		Print(prefix, message, endl, _errInfix);
	}

private:
	const inline static char* _infoInfix = "[*]";
	const inline static char* _warnInfix = "[?]";
	const inline static char* _errInfix = "[!]";
	const inline static char* _enginePrefix = "[OkuLite] ";

	inline static void Print(const char* const prefix, const char* const message, const char* const endl, const char* const infix)
	{
		std::cout << prefix << infix << "\t" << message << endl;
	}
};

#endif//util_Log_h