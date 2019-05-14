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
	name.append(".txt");
	std::ifstream file(name);

	return file.good();
}
