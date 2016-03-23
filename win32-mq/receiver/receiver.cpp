#include <windows.h>
#include <stdio.h>
#include "calc.h"
#include "receiver.h"

ReceiverMessageHandler::ReceiverMessageHandler()
	: MessageHandler(WINDOW_RECEIVER_CLASS_NAME, WINDOW_SENDER_CLASS_NAME)
{
}

void ReceiverMessageHandler::send_response(float result)
{
	RESPONSE_PACKAGE package;
	package.result = result;
	COPYDATASTRUCT data;
	data.cbData = sizeof(RESPONSE_PACKAGE);
	data.dwData = RESPONSE_CODE;
	data.lpData = &package;
	send_data(&data);
}

float ReceiverMessageHandler::calc_from_str(const char * line)
{
	Calc calc(line);
	if (calc.is_valid_expr())
	{
		float ret = calc.compute();
		LOG_I("* Calc result >> %0.2f", ret);
		return ret;
	}
	else
	{
		LOG_E("Expression is invalid!");
		return 0.0f;
	}
}

void ReceiverMessageHandler::received_data(const PCOPYDATASTRUCT data)
{
	if (data->dwData == REQUEST_CODE)
	{
		REQUEST_PACKAGE * package = (REQUEST_PACKAGE *) data->lpData;
		LOG_I("* Received expression is %s", package->line);
		float ret = calc_from_str(package->line);
		send_response(ret);
	}
}

int main()
{
	ReceiverMessageHandler receiver;
	receiver.start_message_loop();
	system("pause");
	return 0;
}