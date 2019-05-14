#include "pch.h"
#include "CreateTable.h"

CreateTable::CreateTable(std::string command)
{
	this->command = command;

	patternParameters = std::regex("\\(\\s*(\\w+\\s+:\\s*\\w+(\\(\\d*\\))*[,\\s]*)+\\);");
	patternParameter = std::regex("[\\w]+[\\s]*:\\s*[\\w]*(\\(\\d*\\))*");
	patternName = std::regex("[\\w]+");
	patternType = std::regex("[\\w\\(\\)]+");

}

CreateTable::~CreateTable()
{
	if (file.good())
		file.close();
}

bool CreateTable::validate()
{
	if (std::regex_search(command, match, patternParameters))
		bufferParams = match[0];
	else
	{
		std::cout << "!!! CREATE TABLE : SYNTAX ERROR !!!\n";
		return false;
	}

	//TODO: VALIDATE VARCHAR SIZE 

	name = command.substr(13, match.position() - 14);
	name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());

	if (table_exists(name))
	{
		std::cout << "!!! " << name << " TABLE ALREADY EXISTS !!!\n";
		return false;
	}

	return true;
}

void CreateTable::execute()
{
	if (!validate())
	{
		return;
	}

	std::sregex_iterator first(bufferParams.begin(), bufferParams.end(), patternParameter);
	std::sregex_iterator last;

	for (std::sregex_iterator itr = first; itr != last; itr++)
	{
		std::smatch mtch = *itr;
		params.push_back(mtch[0]);
	}

	create_file(name);

	for (std::string param : params)
	{
		std::regex_search(param, match, patternName);

		file << match[0];
		std::string tmp = param.substr(match.length());

		std::regex_search(tmp, match, patternType);

		if (param == params.back())
			file << ":" << match[0] << ";";
		else
			file << ":" << match[0] << ",";
	}

	std::cout << "!!! " << name << " TABLE CREATED !!!\n";
}

bool CreateTable::validate_param(std::string param)
{


	return true;
}

void CreateTable::create_file(std::string name)
{
	file.open(name.append(".txt"), std::ios::out);
}