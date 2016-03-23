#pragma once
#include "../shared/handler.h"
#include "../shared/task.h"

class SenderMessageHandler : public MessageHandler, public Runnable
{
	FILE * inputFile;
	FILE * outputFile;
	void send_request(const char * line);
protected:
	virtual void received_data(const PCOPYDATASTRUCT data);
public:
	virtual void run();
	virtual void start_message_loop();
	SenderMessageHandler(const char * inputFilePath, const char * outputFilePath);
	virtual ~SenderMessageHandler();
};