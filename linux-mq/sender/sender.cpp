#include <stdio.h>
#include <stdlib.h>
#include "../shared/mq.h"

int msqid;
key_t key = MQ_KEY;
int msgflg = IPC_CREAT | MQ_PERMS;
size_t buflen;

void create_mspid()
{
    if ((msqid = msgget(key, MQ_PERMS)) < 0)
        msgctl(msqid, IPC_RMID, NULL);
    if ((msqid = msgget(key, msgflg )) < 0)
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
    printf("Sender\n");
    system("read -p \"Press any key to continue...\" a");
    create_mspid();
    send_line("did you get this?");
    send_line("ok?");
    system("read -p \"Press any key to continue...\" a");
    recv_line();
    recv_line();
    return 0;
}
