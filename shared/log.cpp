#include "log.h"
#include <stdarg.h>

#ifdef _DEBUG
#if DEBUG_OUTPUT_MODE == DEBUG_OUTPUT_IDE
#include <windows.h>

void log_to_ide(const char * format, ...)
{
	char szBuff[1024];
	va_list arg;
	va_start(arg, format);
	_vsnprintf(szBuff, sizeof(szBuff), format, arg);
	va_end(arg);
	OutputDebugStringA(szBuff);
	OutputDebugStringA("\n");
}

#elif DEBUG_OUTPUT_MODE == DEBUG_OUTPUT_FILE

void log_to_file(const char * format, ...)
{
	FILE * pLog = fopen(DEBUG_FILENAME, "a");
	if (pLog == NULL)
		return;
	va_list args;
    va_start(args, format);
    vfprintf(pLog, format, args);
	fputc('\n', pLog);
    va_end(args);
	fclose(pLog);

}

#endif
#endif