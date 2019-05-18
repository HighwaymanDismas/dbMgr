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

	std::vector<std::string> tableParams;

	std::string columnNamesString;

private:
	std::vector<std::string> data;
	std::vector<int> columnIndex;

	std::string whereCommand;
	std::string conditionValue;

	void select(std::string name, std::vector<std::string> filterColumns = std::vector<std::string>());
};