#pragma once
#include "../shared/handler.h"

class ReceiverMessageHandler : public MessageHandler
{
	void send_response(float result);
	float calc_from_str(const char * line);
protected:
	virtual void received_data(const PCOPYDATASTRUCT data);
public:
	ReceiverMessageHandler();
};