#include "pch.h"
#include "Where.h"


Where::Where(std::string command, std::vector<std::string> tableParams)
{
	this->command = command;
	this->tableParams = tableParams;

	pattern = std::regex("(\\B(\"\\w+\")\\B|\\b(\\d+\\.\\d+)\\b|^\\d+$|\\b(FALSE)\\b|\\b(TRUE)\\b)", std::regex::icase);
}

Where::~Where()
{
}

bool Where::validate()
{
	command.erase(std::remove_if(command.begin(), command.end(), ::isspace), command.end());
	name = command.substr(0, command.find("="));

	bool flag = false;

	for (std::string colName : tableParams)
		if (colName == name)
			flag = true;

	if (!flag)
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

	return true;
}

void Where::execute()
{
	if (!validate())
		return;

	data = command.substr(command.find("=") + 1);
}

std::string Where::get_data()
{
	return data;
}
