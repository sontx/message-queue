#pragma once
#include <windows.h>

class Runnable
{
public:
	virtual void run() = 0;
};

class Task
{
public:
	static void run(Runnable * runnable);
};