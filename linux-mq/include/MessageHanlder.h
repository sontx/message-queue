#ifndef MESSAGEHANLDER_H
#define MESSAGEHANLDER_H

#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#define MQ_MSGZ	255

class MessageHanlder
{
private:
    key_t key;
    int msgflag;
    int msgqid;
    long send_mtype;
    long recv_mtype;
    pthread_mutex_t lock;
    bool take_msg_queue_id();
protected:
    void log(const char * format, ...);
    int get_msgq_id() const { return msgqid; }
    bool send_text(const char * text) const;
    bool recv_text(char * buffer) const;
public:
    MessageHanlder(key_t key, int msgflag, long send_type, long recv_type);
    virtual ~MessageHanlder();
};

struct msgdt
{
    long mtype;
    char mtext[MQ_MSGZ];
};

#endif // MESSAGEHANLDER_H
