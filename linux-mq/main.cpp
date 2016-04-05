#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "Client.h"
#include "Server.h"

#define MQ_CLIENT_TYPE      1
#define MQ_SERVER_TYPE      2
#define MQ_KEY              3393
#define MQ_CLIENT_INPUT     "input.txt"
#define MQ_CLIENT_OUTPUT    "output.txt"

void start_parent()
{
    printf("Process 1 is running: pid = %d\n", getpid());

    Server * server = NULL;

    try
    {
        server = new Server(MQ_KEY, MQ_SERVER_TYPE, MQ_CLIENT_TYPE);
        server->wait_req_sync();
    }
    catch (const char * what)
    {
        fprintf(stderr, "%s\n", what);
    }

    if (server != NULL)
        delete server;

    printf("Process 1 is stopping!\n");
}

void start_child()
{
    printf("Process 2 is running: pid = %d\n", getpid());
    Client * client = NULL;

    try
    {
        client = new Client(MQ_KEY, MQ_CLIENT_TYPE, MQ_SERVER_TYPE, MQ_CLIENT_INPUT, MQ_CLIENT_OUTPUT);
        client->wait_result_async();
        client->send_math_exprs_sync();
    }
    catch (const char * what)
    {
        fprintf(stderr, "%s\n", what);
    }

    system("read -p \"Press ENTER to exit process 2....\n\" t");
    delete client;

    printf("Process 2 is stopping!\n");
}

int main()
{
    int child_pid = fork();
    if (child_pid != 0)
        start_parent();
    else
        start_child();
	return 0;
}
