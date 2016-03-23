#include "task.h"

void Task::run(Runnable * runnable)
{
	DWORD threadId;
	CreateThread(NULL, 0, [](LPVOID p)->DWORD { ((Runnable *)p)->run(); return 0; }, runnable, 0, &threadId);
}
