#pragma once

class Instruction
{
public:
	Instruction();
	virtual ~Instruction();

	virtual bool validate() = 0;
	virtual void execute() = 0;

	bool table_exists(std::string name);
	std::vector<std::string> split(std::string str, std::string delimiter);

protected:
	std::smatch match;
	std::regex patternParameters;

	std::string command;
	std::string name;

	std::vector<std::string> params;
};

