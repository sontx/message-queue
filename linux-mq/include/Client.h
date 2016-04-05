#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <pthread.h>
#include "MessageHanlder.h"

class Client: public MessageHanlder
{
private:
    FILE * fsrc;
    FILE * fdst;
    unsigned int count_math_exprs = 0xFFFFFFFF;
    void valid_math_expr(char * buffer) const;
    void wait_result_tproc();
    void write_to_file(const char * text);
    static void * start_routine(void * _this);
public:
    void send_math_exprs_sync();
    void wait_result_async() const;
    Client(key_t key, long send_type, long recv_type, const char * src, const char * dst);
    virtual ~Client();
};

#endif // CLIENT_H
