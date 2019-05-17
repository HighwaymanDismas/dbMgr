#pragma once
#include "Instruction.h"

class DropTable : public Instruction
{
public:
	DropTable(std::string command);
	~DropTable();

	virtual bool validate() override;
	virtual void execute() override;
};

