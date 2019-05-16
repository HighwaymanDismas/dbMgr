#include "pch.h"
#include "Instruction.h"

Instruction::Instruction()
{
}


Instruction::~Instruction()
{
}

bool Instruction::table_exists(std::string name)
{
	std::fstream file(name.append(".txt"));

	return file.good();
}
