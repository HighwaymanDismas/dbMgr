#pragma once
#include "Instruction.h"

class SelectFrom : public Instruction
{
public:
	SelectFrom();
	SelectFrom(std::string command);
	~SelectFrom();

	virtual bool validate() override;
	virtual void execute() override;

protected:
	std::regex patternColumns;
	std::regex patternFrom;
	std::regex patternWhere;
	std::regex patternWhereParams;

	std::string columnNamesString;

private:

	std::vector<std::string> data;
	std::vector<std::string> tableParams;

	std::vector<int> columnIndex;

	void select(std::string name, std::vector<std::string> filterColumns = std::vector<std::string>());
};