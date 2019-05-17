#include "pch.h"
#include "SelectFrom.h"

SelectFrom::SelectFrom(std::string command)
{
	this->command = command;

	patternWhere = std::regex("\\bWHERE\\b");
	patternFrom = std::regex("\\bFROM\\b");
}

SelectFrom::~SelectFrom()
{
}

bool SelectFrom::validate()
{
	std::regex_search(command, match, patternFrom);
	
	if (std::regex_search(command, match, patternFrom) != 1)
	{
		std::cout << "SYNTAX ERROR\n";
		return false;
	}

	name = command.substr(match.position() + match.length() + 1);
	name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());
	
	if (!table_exists(name))
	{
		std::cout << "!!! " << name << " DOESN'T EXIST !!!\n";
		return false;
	}

	SelectedColumnNames = (command.substr(7, match.position() - 8));
	SelectedColumnNames.erase(std::remove_if(SelectedColumnNames.begin(), SelectedColumnNames.end(), ::isspace), SelectedColumnNames.end());

	get_column_names();
	
	if (SelectedColumnNames != "*")
	{
		std::cout << "!!! ONLY * WORKS AT THIS POINT !!!\n";
		return false;
	}

	return true;
}

void SelectFrom::execute()
{
	if (!validate())
		return;

	select(name);
}

void SelectFrom::get_column_names()
{
	//USE params
}

void SelectFrom::select(std::string name, std::vector<std::string> filterColumns)
{
	std::string line;
	file.open(name.append(".txt"), std::ios::in);

	std::getline(file, line);
	params = split(line, ",");

	for (std::string param : params)
	{
		bool flag = false;

		if (param == params.back())
			flag = true;

		param = param.substr(0, param.find(":"));

		if(!flag)
			std::cout << param << ", ";
		else
			std::cout << param << std::endl;
	}

	while (!file.eof())
	{
		std::getline(file, line);
		data.push_back(line);
	}

	for (std::string line : data)
	{
		line.erase(line.end() - 1);
		line = std::regex_replace(line, std::regex(","), ", ");
		std::cout << line << std::endl;
	}
}