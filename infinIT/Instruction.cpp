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

std::vector<std::string> Instruction::split(std::string str, std::string delimiter)
{
	size_t last = 0;
	size_t next = 0;
	std::vector<std::string> result;

	while ((next = str.find(delimiter, last)) != std::string::npos)
	{
		result.push_back(str.substr(last, next - last));
		last = next + 1;
	}
	result.push_back(str.substr(last));

	return result;
}
