#pragma once
#include "Instruction.h"
#include "Where.h"

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
	std::regex patternOrderBy;
	std::regex patternOrderByParam;
	std::regex patternOrderByDESC;

	std::vector<std::string> tableParams;

	std::string columnNamesString;

private:
	std::vector<std::string> data;
	std::vector<std::vector<std::string>> data2D;
	std::vector<int> columnIndex;

	std::string whereCommand;
	std::string conditionValue;
	std::string orderByValue;

	static int colOrderByIndex;
	int colWhereIndex;

	bool orderByFlag;
	bool orderByFlagDESC;

	static bool compareASC(std::vector<std::string> a, std::vector<std::string> b);
	static bool compareDESC(std::vector<std::string> a, std::vector<std::string> b);
	void select(std::string name, std::vector<std::string> filterColumns = std::vector<std::string>());
};