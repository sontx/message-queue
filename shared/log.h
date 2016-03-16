#pragma once
#include <stdio.h>
/*
* Author: sontx, www.sontx.in
* A simple log header for debug, support log output to stderr, file, console and IDE(only win32)
* Log will auto be removed in release mode before source compile for performance.
*/

#ifdef _DEBUG

#define DEBUG_D_TAG				"DEBUG"				/* debug tag */
#define DEBUG_E_TAG				"ERROR"				/* error tag */
#define DEBUG_W_TAG				"WARN"				/* warning tag */
#define DEBUG_I_TAG				"INFO"				/* info tag */

#ifdef WIN32
#define DEBUG_OUTPUT_IDE		(1)					/* debug info will be written to visual studio ide */
#endif
#define DEBUG_OUTPUT_STREAM		(2)					/* debug info will be written to stream(stderr) */
#define DEBUG_OUTPUT_FILE		(3)					/* debug info will be written to file debug.log in current directory */
#define DEBUG_OUTPUT_CON		(4)					/* debug info will be written to console with simple message */
#define DEBUG_OUTPUT_MODE		DEBUG_OUTPUT_CON	/* output mode */

#define DEBUG_FORMAT			"[%s] %20s:%10d:%25s(): "
#define __FILENAME__			(strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#if DEBUG_OUTPUT_MODE == DEBUG_OUTPUT_IDE
#define LOG_D(format, ...) {log_to_ide(DEBUG_FORMAT format, DEBUG_D_TAG, __FILENAME__, __LINE__, __func__, __VA_ARGS__);}
#define LOG_E(format, ...) {log_to_ide(DEBUG_FORMAT format, DEBUG_E_TAG, __FILENAME__, __LINE__, __func__, __VA_ARGS__);}
#define LOG_W(format, ...) {log_to_ide(DEBUG_FORMAT format, DEBUG_W_TAG, __FILENAME__, __LINE__, __func__, __VA_ARGS__);}
#define LOG_I(format, ...) {log_to_ide(DEBUG_FORMAT format, DEBUG_I_TAG, __FILENAME__, __LINE__, __func__, __VA_ARGS__);}
#define LOG(format, ...) LOG_D(format, __VA_ARGS__)
// write a log to output window of visual studio ide 
void log_to_ide(const char * format, ...);
#elif DEBUG_OUTPUT_MODE == DEBUG_OUTPUT_STREAM
#define DEBUG_STREAM			stderr
#define LOG_D(format, ...) {fprintf(DEBUG_STREAM, DEBUG_FORMAT format, DEBUG_D_TAG, __FILENAME__, __LINE__, __func__, __VA_ARGS__); fprintf(DEBUG_STREAM, "\n");}
#define LOG_E(format, ...) {fprintf(DEBUG_STREAM, DEBUG_FORMAT format, DEBUG_E_TAG, __FILENAME__, __LINE__, __func__, __VA_ARGS__); fprintf(DEBUG_STREAM, "\n");}
#define LOG_W(format, ...) {fprintf(DEBUG_STREAM, DEBUG_FORMAT format, DEBUG_W_TAG, __FILENAME__, __LINE__, __func__, __VA_ARGS__); fprintf(DEBUG_STREAM, "\n");}
#define LOG_I(format, ...) {fprintf(DEBUG_STREAM, DEBUG_FORMAT format, DEBUG_I_TAG, __FILENAME__, __LINE__, __func__, __VA_ARGS__); fprintf(DEBUG_STREAM, "\n");}
#define LOG(format, ...) LOG_D(format, __VA_ARGS__)
#elif DEBUG_OUTPUT_MODE == DEBUG_OUTPUT_FILE
#define LOG_D(format, ...) {log_to_file(DEBUG_FORMAT format, DEBUG_D_TAG, __FILENAME__, __LINE__, __func__, __VA_ARGS__);}
#define LOG_E(format, ...) {log_to_file(DEBUG_FORMAT format, DEBUG_E_TAG, __FILENAME__, __LINE__, __func__, __VA_ARGS__);}
#define LOG_W(format, ...) {log_to_file(DEBUG_FORMAT format, DEBUG_W_TAG, __FILENAME__, __LINE__, __func__, __VA_ARGS__);}
#define LOG_I(format, ...) {log_to_file(DEBUG_FORMAT format, DEBUG_I_TAG, __FILENAME__, __LINE__, __func__, __VA_ARGS__);}
#define LOG(format, ...) LOG_D(format, __VA_ARGS__)
#define DEBUG_FILENAME			"debug.log"
// write a log to file
void log_to_file(const char * format, ...);
#elif DEBUG_OUTPUT_MODE == DEBUG_OUTPUT_CON
#define DEBUG_STREAM			stderr
#define DEBUG_SFORMAT			"[%s] "
#define LOG_D(format, ...) {fprintf(DEBUG_STREAM, DEBUG_SFORMAT format, DEBUG_D_TAG, __VA_ARGS__); fprintf(DEBUG_STREAM, "\n");}
#define LOG_E(format, ...) {fprintf(DEBUG_STREAM, DEBUG_SFORMAT format, DEBUG_E_TAG, __VA_ARGS__); fprintf(DEBUG_STREAM, "\n");}
#define LOG_W(format, ...) {fprintf(DEBUG_STREAM, DEBUG_SFORMAT format, DEBUG_W_TAG, __VA_ARGS__); fprintf(DEBUG_STREAM, "\n");}
#define LOG_I(format, ...) {fprintf(DEBUG_STREAM, DEBUG_SFORMAT format, DEBUG_I_TAG, __VA_ARGS__); fprintf(DEBUG_STREAM, "\n");}
#define LOG(format, ...) LOG_D(format, __VA_ARGS__)
#endif

#else
#define LOG(s, ...)
#define LOG_D(s, ...)
#define LOG_E(s, ...)
#define LOG_W(s, ...)
#define LOG_I(s, ...)
#endif