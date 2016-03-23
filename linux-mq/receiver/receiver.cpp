
#include <stdio.h>
#include <stdlib.h>
#include "../shared/mq.h"

int msqid;
key_t key = MQ_KEY;
int msgflg = MQ_PERMS;
size_t buflen;

void get_mspid()
{
    if ((msqid = msgget(key, msgflg)) < 0)
    {
        perror("msgget");
        exit(1);
    }
    else
    {
        printf("msgget: msgget succeeded: msqid = %d\n", msqid);
    }
}

bool send_line(const char * line)
{
    msgdt * dt = alloc_msgreq(line);
    int ret = send_msg(msqid, dt, strlen(dt->mtext) + 1);
    if (ret < 0)
        perror("send error");
    else
        printf("Sent %s\n", dt->mtext);
    delete dt;
    return ret >= 0;
}

bool recv_line()
{
    msgdt * dt = new msgdt();
    dt->mtype = MQ_REQTYPE;
    int ret = recv_msg(msqid, dt, MQ_MSGZ);
    if (ret < 0)
        perror("receive error\n");
    else
        printf("Received '%s'\n", dt->mtext);
    delete dt;
    return ret >= 0;
}

int main()
{
    printf("Receiver\n");
    system("read -p \"Press any key to continue...\" a");
    get_mspid();
    recv_line();
    recv_line();
    send_line("yes");
    send_line("you got it");
    return 0;
}
