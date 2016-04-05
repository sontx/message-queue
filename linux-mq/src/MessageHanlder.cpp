#include "MessageHanlder.h"

bool MessageHanlder::take_msg_queue_id()
{
    msgqid = msgget(key, msgflag);
    if (msgqid != -1)
        log("Message queue id is %d", msgqid);
    else
        perror("msgget");
    return msgqid >= 0;
}

void MessageHanlder::log(const char * format, ...)
{
    pthread_mutex_lock(&lock);
    va_list arg;
    va_start(arg, format);
    char buffer[255];
    fprintf(stderr, "[%d] ", getpid());
    vfprintf(stderr, format, arg);
    fprintf(stderr, "\n");
    va_end(arg);
    pthread_mutex_unlock(&lock);
}

bool MessageHanlder::send_text(const char * text) const
{
    msgdt * msg = new msgdt();
    msg->mtype = send_mtype;
    strcpy(msg->mtext, text);
    int result = msgsnd(msgqid, msg, strlen(text) + 1, IPC_NOWAIT);
    delete msg;
    return result >= 0;
}

bool MessageHanlder::recv_text(char * buffer) const
{
    msgdt * msg = new msgdt();
    msg->mtype = recv_mtype;
    int result = msgrcv(msgqid, msg, MQ_MSGZ, recv_mtype, 0);
    if (result > 0)
        strcpy(buffer, msg->mtext);
    delete msg;
    return result >= 0;
}

MessageHanlder::MessageHanlder(key_t key, int msgflag, long send_type, long recv_type)
{
    this->key = key;
    this->msgflag = msgflag;
    this->send_mtype = send_type;
    this->recv_mtype = recv_type;
    bool result = take_msg_queue_id();
    if (!result)
        throw "Can not retrieve message queue id";
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        perror("mutex");
        throw "Mutex can not created";
    }
}

MessageHanlder::~MessageHanlder()
{
    pthread_mutex_destroy(&lock);
}
