#include "pch.h"
#include "CreateTable.h"

CreateTable::CreateTable(std::string command)
{
	this->command = command;

	patternParameters = std::regex("\\([\\w,:]*\\(\\d*\\)[\\w,:()]*\\)$");
	patternParameter = std::regex("[\\w]+[\\s]*:\\s*[\\w]*(\\(\\d*\\))*");
	patternVarchar = std::regex("Varchar\\(\\d+\\)");
}

CreateTable::~CreateTable()
{
	if (file.good())
		file.close();
}

bool CreateTable::validate()
{
	command.erase(std::remove_if(command.begin(), command.end(), ::isspace), command.end());
	command = command.substr(11);

	if (!std::regex_search(command, match, patternParameters))
	{
		std::cout << "SYNTAX ERROR\n";
		return false;
	}

	name = command.substr(0, command.find("("));
	command = command.substr(command.find("("));


	if (table_exists(name))
	{
		std::cout << "!!! TABLE " << name << " ALREADY EXISTS !!!\n";
		return false;
	}

	if (!validate_params())
		return false;

	return true;
}

void CreateTable::execute()
{
	if (!validate())
		return;

	create_file(name);

	for (std::string param : params)
	{
		if (param != params.back())
			file << param << ",";
		else
			file << param << ";";
	}

	file.close();

	if (table_exists(name))
		std::cout << "!!! TABLE " << name << " CREATED SUCESSFULLY !!!\n";
	else
		std::cout << "!!! COULDN'T CREATE NEW FILE !!!\n";
}

bool CreateTable::validate_params()
{
	std::sregex_iterator first(command.begin(), command.end(), patternParameter);
	std::sregex_iterator last;

	for (std::sregex_iterator itr = first; itr != last; itr++)
	{
		std::smatch mtch = *itr;
		params.push_back(mtch[0]);
	}

	for (std::string param : params)
	{
		if (std::regex_search(param, match, std::regex("Varchar")))
		{
			if (!std::regex_search(param, match, patternVarchar))
			{
				std::cout << "SYNTAX ERROR: WRONG USE OF VARCHAR\n";
				return false;
			}

			std::regex_search(param, match, std::regex("\\d+"));

			if (std::stoi(match[0]) > CreateTable::MAX_SIZE || std::stoi(match[0]) < CreateTable::MIN_SIZE)
			{
				std::cout << "WRONG SIZE OF VARCHAR";
				return false;
			}
		}
		else if (!std::regex_search(param, match, std::regex("Integer")) && !std::regex_search(param, match, std::regex("Float")) && !std::regex_search(param, match, std::regex("Boolean")))
		{
			std::cout << "SYNTAX ERROR\n";
			return false;
		}
	}

	return true;
}

void CreateTable::create_file(std::string name)
{
	file.open(name.append(".txt"), std::ios::out);
}