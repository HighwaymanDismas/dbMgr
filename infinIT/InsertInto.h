#pragma once

#include "Instruction.h"

class InsertInto : public Instruction
{
public:
	InsertInto();
	InsertInto(std::string command);
	~InsertInto();

	virtual bool validate() override;
	virtual void execute() override;

private:
	std::regex patternVarchar;
	std::regex patternBoolean;

	std::vector<std::string> data;
	std::vector<int> varcharSizes;
	
	int tableSize;

	void get_table_params();
	void get_insert_data();
	bool validate_data();
};

