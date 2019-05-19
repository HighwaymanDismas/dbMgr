#pragma once
#include "SelectFrom.h"

class Where : public Instruction
{
public:
	Where(std::string command, std::vector<std::string> tableParams);
	~Where();

	virtual bool validate() override;
	virtual void execute() override;

	std::string get_data();
	int get_index();

private:
	std::regex pattern;

	std::vector<std::string> tableParams;

	std::string data;

	int colIndex;
};

