#pragma once

#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MQ_MSGZ	    	255
#define MQ_KEY          393
#define MQ_REQTYPE		1
#define MQ_RESPTYPE     2
#define MQ_PERMS		0666

struct msgdt
{
    long mtype;
    char mtext[MQ_MSGZ];
};

extern "C"
{
    msgdt * alloc_msgreq(const char * text);
    msgdt * alloc_msgresp(float ret);
    int send_msg(int msqid, const msgdt * buf, size_t buflen);
    int recv_msg(int msqid, msgdt * buf, size_t buflen);
}
