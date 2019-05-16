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

};