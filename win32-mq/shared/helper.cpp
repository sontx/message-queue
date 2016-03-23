#include "helper.h"
#include "log.h"

HWND create_window(WNDPROC proc, HINSTANCE hInstance, LPCSTR className)
{
	WNDCLASSEXA wc;
	HWND hwnd;
	MSG Msg;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = proc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = className;
	wc.hIconSm = NULL;

	if (!RegisterClassExA(&wc))
		return NULL;

	hwnd = CreateWindowExA(
		WS_EX_CLIENTEDGE,
		className,
		NULL,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,
		NULL, NULL, hInstance, NULL);

	return hwnd;
}