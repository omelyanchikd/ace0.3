#include "vacancy.h"


vacancy::vacancy(void)
{
	_salary = 0;
	_group = -1;
}

double vacancy::get_salary()
{
	return _salary;
}

int vacancy::get_group()
{
	return _group;
}



