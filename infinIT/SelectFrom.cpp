#include "pch.h"
#include "SelectFrom.h"

SelectFrom::SelectFrom()
{
}

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
		std::cout << "!!! SYNTAX ERROR !!!\n";
		return false;
	}

	name = command.substr(match.position() + match.length() + 1);
	name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());
	
	if (!table_exists(name))
	{
		std::cout << "!!! " << name << " DOESN'T EXIST !!!\n";
		return false;
	}

	columnNamesString = command.substr(6, match.position() - 7);
	columnNamesString.erase(std::remove_if(columnNamesString.begin(), columnNamesString.end(), ::isspace), columnNamesString.end());
	
	if (columnNamesString.size() == 0)
	{
		std::cout << "!!! SYNTAX ERROR !!!\n";
		return false;
	}

	params = split(columnNamesString, ",");

	return true;
}

void SelectFrom::execute()
{
	if (!validate())
		return;

	select(name, params);
}

void SelectFrom::select(std::string name, std::vector<std::string> filterColumns)
{
	std::string line;
	file.open(name.append(".txt"), std::ios::in);

	std::getline(file, line);
	tableParams = split(line, ",");

	for (size_t i = 0; i < tableParams.size(); i++)
	{
		tableParams[i] = tableParams[i].substr(0, tableParams[i].find(":"));

		if (filterColumns[0] != "*")
		{
			for (std::string colName : filterColumns)
			{
				if (colName == tableParams[i])
					columnIndex.push_back(i);
			}
		}
	}

	for (std::string colName : tableParams)
	{
		bool flag = false;

		if (colName == tableParams.back())
			flag = true;

		if (!flag)
			std::cout << colName << ", ";
		else
			std::cout << colName << "\n";
	}

	while (!file.eof())
	{
		std::getline(file, line);
		data.push_back(line);
	}

	for (std::string line : data)
	{
		std::vector<std::string> tmp = split(line, ",");

		for(int idx : columnIndex)
			std::cout << tmp[idx] << "\n";

		line.erase(line.end() - 1);
		line = std::regex_replace(line, std::regex(","), ", ");
		//std::cout << line << std::endl;
	}
}