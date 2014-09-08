#include "world.h"


world::world(void)
{
}

world::world(int firmnumber, int householdnumber, double firmmoney, double householdmoney, scenario choice, string model_name)
{
	_firms_consume = (firms(firmnumber, firmmoney, model_name, 0));
	_firms_raw = (firms(2, 0, model_name, firmnumber));
	_households = (households(householdnumber, householdmoney, model_name));
	_rawmarket.clear();
	_goodmarket.clear();
	_labormarket.clear();
	_scenario = choice;
	_model = model_name;

}


world::world(int firmnumber, int householdnumber, double firmmoney, double householdmoney, scenario choice, string model_name, string rules_price, string rules_salary, string rules_plan)
{
	_firms_consume = (firms(firmnumber, firmmoney, model_name, 0));
	_firms_raw = (firms(2, firmmoney, model_name, firmnumber));
	_households = (households(householdnumber, householdmoney, model_name));
	_rawmarket.clear();
	_goodmarket.clear();
	_labormarket.clear();
	_scenario = choice;
	_model = model_name;
	ifstream fin;
	fin.open(rules_price);
	while (!fin.eof())
	{
		string line;
		getline(fin, line);
		stringstream input(line);
		vector<double> values;
		while (!input.eof())
		{
			double val;
			input>>val;
			values.push_back(val);
		}
		_rules_price.push_back(values);
		values.clear();
		input.str("");
	}
	fin.close();
	fin.open(rules_salary);
	while (!fin.eof())
	{
		string line;
		getline(fin, line);
		stringstream input(line);
		vector<double> values;
		while (!input.eof())
		{
			double val;
			input>>val;
			values.push_back(val);
		}
		_rules_salary.push_back(values);
		values.clear();
		input.str("");
	}
	fin.close();
    fin.open(rules_plan);
	while (!fin.eof())
	{
		string line;
		getline(fin, line);
		stringstream input(line);
		vector<double> values;
		while (!input.eof())
		{
			double val;
			input>>val;
			values.push_back(val);
		}
		_rules_plan.push_back(values);
		values.clear();
		input.str("");
	}
	fin.close();
}

void world::step()
{
//	_households.die();
	_households.birth();
	_households.quit(_firms_consume.fire());
	_households.quit(_firms_raw.fire());
	_households.update_salary(_firms_consume.set_vacancies());
	_households.update_salary(_firms_raw.set_vacancies());
	for (int iter = 0; iter < 2; iter++)
	{
		_labormarket.set_vacancies(_firms_consume.set_vacancies());
	    _labormarket.set_vacancies(_firms_raw.set_vacancies());
		_labormarket.set_resumes(_households.search_work(_labormarket.get_vacancies()));
		_labormarket.set_invites(_firms_consume.check_resumes(_labormarket.get_resumes()));
		_labormarket.set_invites(_firms_raw.check_resumes(_labormarket.get_resumes()));
		_firms_consume.hire(_households.choose_employee(_labormarket.get_invites(), _labormarket.get_vacancies()));
		_firms_raw.hire(_households.choose_employee(_labormarket.get_invites(), _labormarket.get_vacancies()));
		_labormarket.clear();
	}
	_firms_raw.produce_raw();
	_rawmarket.set_supply(_firms_raw.set_supply());
	_firms_consume.buy_raw(_rawmarket._demand);
	_firms_raw.get_sales(_rawmarket.get_sales());
	_firms_consume.produce_consume();
	_households.get_income();
	_goodmarket.set_supply(_firms_consume.set_supply());
	_households.buy(_goodmarket._demand);
	_firms_consume.get_sales(_goodmarket.get_sales());
	get_statistics();
	_firms_consume.set_info();
	_firms_consume.write_log(_model);
	_firms_raw.set_info();
	_firms_raw.write_log(_model);
	_households.write_log(_model);
	_firms_consume.print_info();
	_firms_raw.print_info();
//	_households.print_info();
//	_firms.learn(_rules_price, _rules_salary, _rules_plan);
	_firms_consume.learn(_scenario);
	_firms_raw.learn(_scenario);
	_goodmarket.clear();
	_labormarket.clear();
	_rawmarket.clear();
}

/*double world::inflation()
{
	double sum = 0;
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		sum += (i->second).getprice() * (i->second).getstock();
	}
	return sum/_statistics.inflation();
}//*/

void world::get_statistics()
{
/*	_statistics.set_unemployment(_households.unemployment());		// Уровень безработицы.
	_statistics.set_production(_firms.production());			// Объем производства.
	_statistics.set_consumption(_firms.consumption());			// Объем потребления.
	_statistics.set_average_price(_firms.average_price());		// Средняя цена.
	_statistics.set_average_salary(_firms.average_salary());	// Средняя заработная плата.
	//_statistics.set_inflation(inflation());				// Инфляция.
	_statistics.set_gdp(_firms.gdp());							// Валовый внутренний продукт.
	_statistics.set_firm(_firms.firm_number());					// Количество фирм.
	_statistics.set_household(_households.household_number());	// Количество домохозяйств.
	//*/
}

