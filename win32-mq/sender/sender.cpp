#include <windows.h>
#include <stdio.h>
#include "sender.h"

#define INPUT_FILENAME		"in.txt"
#define OUTPUT_FILENAME		"out.txt"

void SenderMessageHandler::run()
{
	char buff[25];
	while (!feof(inputFile))
	{
		fgets(buff, sizeof(buff) / sizeof(char), inputFile);
		send_request(buff);
	}
	SendMessage(get_my_hwnd(), WM_CLOSE, NULL, NULL);
}

void SenderMessageHandler::start_message_loop()
{
	Task::run(this);
	MessageHandler::start_message_loop();
}

SenderMessageHandler::SenderMessageHandler(const char * inputFilePath, const char * outputFilePath)
	: MessageHandler(WINDOW_SENDER_CLASS_NAME, WINDOW_RECEIVER_CLASS_NAME)
{
	inputFile = fopen(inputFilePath, "r");
	outputFile = fopen(outputFilePath, "w");
}

SenderMessageHandler::~SenderMessageHandler()
{
	fclose(inputFile);
	fclose(outputFile);
	MessageHandler::~MessageHandler();
}

void SenderMessageHandler::send_request(const char * line)
{
	REQUEST_PACKAGE package;
	strcpy(package.line, line);
	COPYDATASTRUCT data;
	data.cbData = sizeof(REQUEST_PACKAGE);
	data.dwData = REQUEST_CODE;
	data.lpData = &package;
	send_data(&data);
}

void SenderMessageHandler::received_data(const PCOPYDATASTRUCT data)
{
	if (data->dwData == RESPONSE_CODE)
	{
		RESPONSE_PACKAGE * package = (RESPONSE_PACKAGE *) data->lpData;
		LOG_I("* Response result >> %0.2f", package->result);
		char buff[25];
		snprintf(buff, sizeof(buff) / sizeof(char), "%f", package->result);
		fputs(buff, outputFile);
		fputs("\r\n", outputFile);
		fflush(outputFile);
	}
}

int main()
{
	SenderMessageHandler sender(INPUT_FILENAME, OUTPUT_FILENAME);
	sender.start_message_loop();
	system("pause");
	return 0;
}