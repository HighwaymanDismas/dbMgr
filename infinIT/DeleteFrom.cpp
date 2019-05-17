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

	name = command.substr(match.position() + match.length() + 1);
	name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());

	if (!table_exists(name))
	{
		std::cout << "!!! " << name << " DOESN'T EXIST !!!\n";
		return false;
	}

	return true;
}

void DeleteFrom::execute()
{
	if (!validate())
		return;

	remove_all(name);
}

void DeleteFrom::remove_all(std::string name)
{
	std::string line;

	file.open(name.append(".txt"), std::ios_base::in);
	std::getline(file, line);
	file.close();
	file.open(name, std::ios_base::out);

	file << line;
	file.close();
}
