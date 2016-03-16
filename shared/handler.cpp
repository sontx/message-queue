#include "handler.h"

MessageHandler * MessageHandler::instance = NULL;

LRESULT MessageHandler::wnd_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COPYDATA:
		LOG_I("* Received message is a data package from another process!");
		instance->received_data((PCOPYDATASTRUCT) lParam);
		break;
	case WM_CLOSE:
		LOG_I("Close window");
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void MessageHandler::start_message_loop()
{
	LOG_I("Message loop is running...");
	MSG msg;
	BOOL ret;
	while (ret = GetMessage(&msg, NULL, 0, 0)) {
		if (ret < 0)
		{
			LOG_E("Has some error in message loop");
			break;
		}
		else if (ret > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			break;
		}
	}
	LOG_W("Message loop is stopped!");
}

HWND MessageHandler::get_receiver_hwnd()
{
	if (receiverWindowHandle == NULL && receiverWindowClass != NULL)
	{
		receiverWindowHandle = FindWindowA(receiverWindowClass, NULL);
		if (receiverWindowHandle != NULL)
		{
			LOG_I("Receiver window[%s] handle is %lu", receiverWindowClass, (ULONG) receiverWindowHandle);
		}
		else
		{
			LOG_E("Can not get receiver window handle with title %s", receiverWindowClass);
		}
	}
	return receiverWindowHandle;
}

HWND MessageHandler::get_my_hwnd() const
{
	return myWindowHandle;
}

void MessageHandler::send_data(const PCOPYDATASTRUCT data)
{
	HWND receiverHwnd = get_receiver_hwnd();
	if (receiverHwnd != NULL)
	{
		LOG_I("Send %ld >> %lu", (ULONG) myWindowHandle, (ULONG) receiverHwnd);
		LRESULT ret = SendMessage(receiverHwnd, WM_COPYDATA, (WPARAM) myWindowHandle, (LPARAM) data);
	}
	else if (receiverWindowClass != NULL)
	{
		LOG_E("You must run receiver process which have title is %s before send message to it!", receiverWindowClass);
	}
}

MessageHandler::MessageHandler(LPCSTR myClass, LPCSTR receiverClass)
{
	receiverWindowClass = new char[strlen(receiverClass) + 1];
	strcpy(receiverWindowClass, receiverClass);
	myWindowHandle = create_window(wnd_proc, GetModuleHandle(NULL), myClass);
	if (myWindowHandle != NULL)
	{
		LOG_I("Created a hide window[%s] for receive data from another process with handle is %lu", myClass, (ULONG) myWindowHandle);
	}
	else
	{
		LOG_E("Can not create hide window for receive data from antoher process");
	}
	instance = this;
}

MessageHandler::~MessageHandler()
{
	if (receiverWindowClass != NULL)
	{
		delete[] receiverWindowClass;
		receiverWindowClass = NULL;
	}
}
