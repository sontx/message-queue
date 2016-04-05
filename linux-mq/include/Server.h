#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include "MessageHanlder.h"
#include "Calc.h"

class Server: public MessageHanlder
{
private:
    void resp_result(const char * expr);
public:
    void wait_req_sync();
    Server(key_t key, long send_type, long recv_type);
};

#endif // SERVER_H
