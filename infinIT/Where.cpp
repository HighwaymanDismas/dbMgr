#include "pch.h"
#include "Where.h"


Where::Where(std::string command, std::vector<std::string> tableParams)
{
	this->command = command;
	this->tableParams = tableParams;

	pattern = std::regex("(\\B(\"[\\w\\s]+\")\\B|\\b(\\d+\\.\\d+)\\b|^\\d+$|\\b(FALSE)\\b|\\b(TRUE)\\b)", std::regex::icase);
}

Where::~Where()
{
}

bool Where::validate()
{
	name = command.substr(0, command.find("="));
	name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());

	colIndex = -1;

	for (size_t i = 0; i < tableParams.size(); i++)
		if (tableParams[i] == name)
			colIndex = i;

	if (colIndex == -1)
	{
		std::cout << "!!! COLUMN " << name << " DOESN'T EXIST !!!\n";
		return false;
	}

	std::string buffer = command.substr(command.find("=") + 1);

	if (!std::regex_search(buffer, match, pattern))
	{
		std::cout << "!!! INVALID CONDITION DATA !!!\n";
		return false;
	}

	data = match[0];

	return true;
}

void Where::execute()
{
	if (!validate())
		return;
}

std::string Where::get_data()
{
	return data;
}

int Where::get_index()
{
	return colIndex;
}
