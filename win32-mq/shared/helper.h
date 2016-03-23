#pragma once
#include <windows.h>

#define WINDOW_SENDER_CLASS_NAME		"sender.sontx.blogspot.com"
#define WINDOW_RECEIVER_CLASS_NAME		"receiver.sontx.blogspot.com"
#define MAX_DATA_LENGTH					100
#define REQUEST_CODE					1
#define RESPONSE_CODE					2

HWND create_window(WNDPROC, HINSTANCE, LPCSTR);

struct REQUEST_PACKAGE
{
	char line[MAX_DATA_LENGTH];
};

struct RESPONSE_PACKAGE
{
	float result;
};