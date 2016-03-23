#include "mq.h"

extern "C"
{
	msgdt * alloc_msgreq(const char * text)
	{
		msgdt * buf = new msgdt();

		buf->mtype = MQ_REQTYPE;
		strcpy(buf->mtext, text);

		return buf;
	}

	msgdt * alloc_msgresp(float ret)
	{
		msgdt * buf = new msgdt();

		buf->mtype = MQ_RESPTYPE;
        memcpy(buf->mtext, &ret, sizeof(float));

		return buf;
	}

	int send_msg(int msqid, const msgdt * buf, size_t buflen)
	{
		int ret = msgsnd(msqid, buf, buflen, IPC_NOWAIT);
		return ret;
	}

	int recv_msg(int msqid, msgdt * buf, size_t buflen)
	{
		int ret = msgrcv(msqid, buf, buflen, buf->mtype, 0);
		return ret;
	}
}
