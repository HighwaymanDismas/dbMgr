#pragma once

#include <string>
#include <fstream>
#include <regex>
#include <vector>

class Instruction
{
public:
	Instruction();
	virtual ~Instruction();

	virtual bool validate() = 0;
	bool table_exists(std::string name);
	virtual void execute() = 0;

protected:
	std::smatch match;

	std::regex patternParameters;

	std::string command;
	std::string name;
	std::string bufferParams;

	std::vector<std::string> params;
};

