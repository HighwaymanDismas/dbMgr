#include "pch.h"
#include "DeleteFrom.h"


DeleteFrom::DeleteFrom(std::string command)
{
	this->command = command;

	patternFrom = std::regex("\\bFROM\\b");
	patternWhere = std::regex("\\bWHERE\\b");

}

DeleteFrom::~DeleteFrom()
{
}

bool DeleteFrom::validate()
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

	std::string line;
	file.open(name.append(".txt"), std::ios::in);

	std::getline(file, line);
	tableParams = split(line, ",");

	for (size_t i = 0; i < tableParams.size(); i++)
		tableParams[i] = tableParams[i].substr(0, tableParams[i].find(":"));

	return true;
}

void DeleteFrom::execute()
{
	if (!validate())
		return;

	if (whereCommand.size() != 0)
	{
		Where sWhere(whereCommand, tableParams);

		if (!sWhere.validate())
			return;

		conditionValue = sWhere.get_data();
		colWhereIndex = sWhere.get_index();

		remove_where(name);
	}
	else
		remove_all(name);
}

void DeleteFrom::remove_all(std::string name)
{
	std::string line;

	file.open(name, std::ios_base::in);
	std::getline(file, line);
	file.close();
	file.open(name, std::ios_base::out);

	file << line;
	file.close();
}

void DeleteFrom::remove_where(std::string name)
{
	std::vector<std::string> lineElements;
	std::string firstLine;
	std::string line;

	file.close();
	file.open(name, std::ios_base::in);
	std::getline(file, firstLine);

	while (!file.eof())
	{
		std::getline(file, line);
		
		line.erase(line.size() - 1);
		lineElements = split(line, ",");

		data2D.push_back(lineElements);
	}

	for (size_t i = 0; i < data2D.size(); i++)
	{
		if (data2D[i][colWhereIndex] == conditionValue)
			data2D.erase(data2D.begin() + i, data2D.begin() + i + 1);
	}

	file.close();
	file.open(name, std::ios_base::out);
	file << firstLine << std::endl;

	for (std::vector<std::string> line : data2D)
	{
		for (std::string elem : line)
		{
			if (elem != line.back())
				file << elem << ",";
			else
				file << elem << ";";
		}

		if (line != data2D.back())
			file << std::endl;
	}


	file.close();
}
