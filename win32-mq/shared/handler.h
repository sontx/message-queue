#pragma once
#include "helper.h"
#include "log.h"

class MessageHandler
{
	static MessageHandler * instance;
	HWND myWindowHandle = NULL;
	HWND receiverWindowHandle = NULL;
	char * receiverWindowClass = NULL;

	HWND get_receiver_hwnd();
	static LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	HWND get_my_hwnd() const;
	virtual void received_data(const PCOPYDATASTRUCT data) = 0;
public:
	virtual void start_message_loop();
	void send_data(const PCOPYDATASTRUCT data);
	MessageHandler(LPCSTR myClass, LPCSTR receiverClass);
	virtual ~MessageHandler();
};