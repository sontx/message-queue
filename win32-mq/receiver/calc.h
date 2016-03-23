#pragma once
class Calc
{
	double val1;
	double val2;
	char operation = 0;
public:
	double compute() const;
	bool is_valid_expr() const;
	Calc(const char * line);
};

