#pragma once
#include "Instruction.h"

class SelectFrom : public Instruction
{
public:
	SelectFrom(std::string command);
	~SelectFrom();

	virtual bool validate() override;
	virtual void execute() override;

private:
	std::regex patternColumn;
	std::regex patternFrom;
	std::regex patternWhere;
	std::regex patternWhereParam;

	std::fstream file;

	std::vector<std::string> data;

	void select(std::string name);
};