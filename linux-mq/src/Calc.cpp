#include "Calc.h"
#include <string.h>
#include <stdlib.h>

double Calc::compute() const
{
	switch (operation)
	{
	case '+': return val1 + val2;
	case '-': return val1 - val2;
	case '*': return val1 * val2;
	case '/': return val1 / val2;
	default: return 0.0f;
	}
}

bool Calc::is_valid_expr() const
{
	return operation == '+' || operation == '-' || operation == '*' || operation == '/';
}

Calc::Calc(const char * line)
{
	const char * pOperation;
	if ((pOperation = strchr(line, '+')) != NULL ||
		(pOperation = strchr(line, '-')) != NULL ||
		(pOperation = strchr(line, '*')) != NULL ||
		(pOperation = strchr(line, '/')) != NULL)

	{
		operation = *pOperation;
		char delim[] = { operation, '\0' };
		char * str = new char[strlen(line) + 1];
		strcpy(str, line);

		char * token = strtok(str, delim);
		val1 = atof(token);
		token = strtok(NULL, delim);
		val2 = atof(token);

		delete[] str;
	}
}
