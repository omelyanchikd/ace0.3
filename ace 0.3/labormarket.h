#pragma once

#include <map>
#include <vector>

using namespace std;

class labormarket
{
public:
	labormarket(void);
	
	void set(vector<int> group_sizes);


	void set_vacancies(map<int, double> vacancies);
	map<int,double> get_vacancies(int group);

	void set_resumes(map<int, vector<int>> resumes);
	map<int, vector<int>> get_resumes();

	void set_invites(map<int, vector<int>> invites);
	map<int, vector<int>> get_invites();

	void clear();
	void full_clear();

private:
	map<int, double> _vacancies;
	map<int, vector<int>> _resumes;	
	map<int, vector<int>> _invites;
	vector<int> _group_sizes;
	int _current_group;

};

