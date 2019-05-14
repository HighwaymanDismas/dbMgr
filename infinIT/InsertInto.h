#pragma once

#include "Instruction.h"
#include <iostream>

class InsertInto : public Instruction
{
public:
	InsertInto(std::string command);
	~InsertInto();

	virtual bool validate() override;
	virtual void execute() override;

private:
	std::regex patternTableName;
};

