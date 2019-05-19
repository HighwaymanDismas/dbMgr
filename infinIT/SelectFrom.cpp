#include "pch.h"
#include "SelectFrom.h" 

int SelectFrom::colOrderByIndex = -1;

bool SelectFrom::compareASC(std::vector<std::string> a, std::vector<std::string> b)
{
	return a[colOrderByIndex] < b[colOrderByIndex];
}

bool SelectFrom::compareDESC(std::vector<std::string> a, std::vector<std::string> b)
{
	return a[colOrderByIndex] > b[colOrderByIndex];
}

SelectFrom::SelectFrom()
{
}

SelectFrom::SelectFrom(std::string command)
{
	this->command = command;

	patternWhere = std::regex("\\b(WHERE)\\b");
	patternFrom = std::regex("\\b(FROM)\\b");
	patternOrderBy = std::regex("\\b(ORDER BY)\\b");
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

	std::smatch bufferMatch;

	if (!std::regex_search(command, bufferMatch, patternWhere))
	{
		name = command.substr(match.position() + match.length() + 1);
		name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());
	}
	else
	{
		whereCommand = command.substr(bufferMatch.position() + bufferMatch.length() + 1);
		name = command.substr(match.position() + match.length() + 1, bufferMatch.position() - (match.position() + match.length() + 1));
		name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());
	}
	
	if (!table_exists(name))
	{
		std::cout << "!!! TABLE " << name << " DOESN'T EXIST !!!\n";
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

	std::string line;
	file.open(name.append(".txt"), std::ios::in);

	std::getline(file, line);
	tableParams = split(line, ",");

	for (size_t i = 0; i < tableParams.size(); i++)
		tableParams[i] = tableParams[i].substr(0, tableParams[i].find(":"));

	bool flag = false;

	if (params.size() != 1 && params[0] != "*")
	{
		for (std::string filterColName : params)
		{
			for (std::string colName : tableParams)
				if (filterColName == colName)
					flag = true;

			if (!flag)
			{
				std::cout << "!!! TYPED COLUMN DOESN'T EXIST !!!\n";
				return false;
			}

			flag = false;
		}
	}

	return true;
}

void SelectFrom::execute()
{
	if (!validate())
		return;

	if (whereCommand.size() != 0)
	{
		Where sWhere(whereCommand, tableParams);

		if(!sWhere.validate())
			return;

		conditionValue = sWhere.get_data();
		colWhereIndex = sWhere.get_index();
		select(name, params);
	}
	else
	{
		colWhereIndex = -1;
		select(name, params);
	}
}

void SelectFrom::select(std::string name, std::vector<std::string> filterColumns)
{
	std::string line;

	if (filterColumns.size() != 0 && filterColumns[0] != "*")
	{
		for (std::string colName : filterColumns)
		{
			for (size_t i = 0; i < tableParams.size(); i++)
			{
				if (colName == tableParams[i])
				{
					columnIndex.push_back(i);
					std::cout << colName << " ";
				}
			}
		}
	}
	else
		for (std::string colName : tableParams)
			std::cout << colName << " ";

	std::cout << std::endl;

	while (!file.eof())
	{
		std::getline(file, line);
		data.push_back(line);
	}

	std::vector<std::string> lineElements;

	for (std::string line : data)
	{
		line.erase(line.size() - 1);
		lineElements = split(line, ",");

		data2D.push_back(lineElements);
	}

	colOrderByIndex = 3;
	std::sort(data2D.begin(), data2D.end(), compareDESC);

	for (std::vector<std::string> lineElements : data2D)
	{
		if (colWhereIndex == -1 || lineElements[colWhereIndex] == conditionValue)
		{
			if (filterColumns.size() != 0 && filterColumns[0] != "*")
			{
				for (int idx : columnIndex)
					if (idx != columnIndex.back())
						std::cout << lineElements[idx] << ", ";
					else
						std::cout << lineElements[idx] << std::endl;
			}
			else
			{
				for (size_t i = 0; i < lineElements.size(); i++)
				{
					if (i == lineElements.size() - 1)
						std::cout << lineElements[i] << std::endl;
					else
						std::cout << lineElements[i] << ", ";
				}
			}
		}
	}
}