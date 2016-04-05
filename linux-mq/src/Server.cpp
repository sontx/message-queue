#include "Server.h"

void Server::resp_result(const char * expr)
{
    Calc * calc = new Calc(expr);
    if (calc->is_valid_expr())
    {
        double result = calc->compute();
        char * rexpr = new char[MQ_MSGZ];
        sprintf(rexpr, "%s=%0.2f", expr, result);
        if (send_text(rexpr))
            log("Send result expression: %s", rexpr);
        else
            log("Can not send result expression: %s", rexpr);
        delete[] rexpr;
    }
    else
    {
        log("Invalid expression: %s", expr);
    }
    delete calc;
}

void Server::wait_req_sync()
{
    char buffer[MQ_MSGZ];
    while (true)
    {
        if (!recv_text(buffer))
            break;
        resp_result(buffer);
    }
    log("Server has been stopped!");
}

Server::Server(key_t key, long send_type, long recv_type)
    :MessageHanlder(key, IPC_CREAT | 0666, send_type, recv_type)
{
}
