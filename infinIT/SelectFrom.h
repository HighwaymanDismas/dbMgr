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
	std::regex patternColumns;
	std::regex patternFrom;
	std::regex patternWhere;
	std::regex patternWhereParams;

	std::vector<std::string> data;
	std::vector<std::string> filterColumns;

	std::string SelectedColumnNames;

	void select(std::string name, std::vector<std::string> filterColumns = std::vector<std::string>());
	void get_column_names();
};