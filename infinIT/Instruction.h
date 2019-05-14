#pragma once

#include <string>
#include <fstream>

class Instruction
{
public:
	Instruction();
	virtual ~Instruction();

	virtual bool validate() = 0;
	bool table_exists(std::string name);
	virtual void execute() = 0;

protected:
	std::string command;
};

