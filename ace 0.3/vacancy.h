#pragma once
class vacancy
{
public:
	vacancy(void);
	vacancy(double salary, int group): _salary(salary), _group(group)
	{
	}

	double get_salary();
	int get_group();

private:
	double _salary;
	int _group;
};

