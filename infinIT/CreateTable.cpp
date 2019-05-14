#include "pch.h"
#include "CreateTable.h"

CreateTable::CreateTable(std::string command)
{
	this->command = command;

	patternParameters = std::regex("\\([\\w\\d\\s:,\\(\\)]+");
	patternParameter = std::regex("[\\w]+[\\s]*:\\s*[\\w]*(\\(\\d*\\))*");

}

CreateTable::~CreateTable()
{
}

bool CreateTable::validate()
{
	if (std::regex_search(command, match, patternParameters))
		bufferParams = match[0];
	else
		return false;

	name = command.substr(13, match.position() - 14);

	if (!table_exists(name))
		std::cout << name << std::endl;
	else
		return false;

	std::sregex_iterator first(bufferParams.begin(), bufferParams.end(), patternParameter);
	std::sregex_iterator last;

	for (std::sregex_iterator itr = first; itr != last; itr++)
	{
		std::smatch mtch = *itr;
		params.push_back(mtch[0]);
	}

	for (auto param : params)
		std::cout << param << std::endl;

	return true;
}

void CreateTable::execute()
{
	validate();
}

bool CreateTable::validate_param(std::string param)
{
	return true;
}

