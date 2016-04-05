#include "Client.h"

void Client::wait_result_tproc()
{
    char * buffer = new char[MQ_MSGZ];
    int count_math_exprs_received = 0;
    while (count_math_exprs_received < this->count_math_exprs)
    {
        if (!recv_text(buffer))
            break;
        count_math_exprs_received++;
        log("Received %s", buffer);
        write_to_file(buffer);
    }
    delete[] buffer;
}

void Client::valid_math_expr(char * buffer) const
{
    int expr_length = strlen(buffer);
    if (expr_length > 2 && buffer[expr_length - 1] == '\n')
        buffer[expr_length - 1] = '\0';
}

void Client::write_to_file(const char * text)
{
    fputs(text, fdst);
    fputs("\n", fdst);
    fflush(fdst);
}

void * Client::start_routine(void * _this)
{
    ((Client *) _this)->wait_result_tproc();
}

void Client::send_math_exprs_sync()
{
    char * buffer = new char[MQ_MSGZ];
    int count_math_exprs = 0;
    while (!feof(fsrc) && fgets(buffer, MQ_MSGZ, fsrc))
    {
        valid_math_expr(buffer);
        if (send_text(buffer))
        {
            log("Sent %s", buffer);
            count_math_exprs++;
        }
        else
        {
            log("Can not send '%s' to server", buffer);
            break;
        }
    }
    this->count_math_exprs = count_math_exprs;
    delete[] buffer;
}

void Client::wait_result_async() const
{
    pthread_t threadid;
    int result = pthread_create(&threadid, NULL, start_routine, const_cast<Client *>(this));
    if (result)
        throw "Unable to create thread";
}

Client::Client(key_t key, long send_type, long recv_type, const char * src, const char * dst)
    :MessageHanlder(key, 0666, send_type, recv_type)
{
    fsrc = fopen(src, "r");
    fdst = fopen(dst, "w");
}

Client::~Client()
{
    fclose(fsrc);
    fclose(fdst);
    msgctl(get_msgq_id(), IPC_RMID, NULL);
}
