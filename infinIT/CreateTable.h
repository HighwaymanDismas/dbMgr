#pragma once

#include "Instruction.h"
#include <iostream>
#include <regex>
#include <vector>
#include <fstream>

class CreateTable : public Instruction
{
public:
	CreateTable(std::string command);
	~CreateTable();

	virtual bool validate() override;
	virtual void execute() override;

private:
	bool validate_params();
	void create_file(std::string name);

	std::fstream file;

	std::regex patternParameter;
	std::regex patternVarchar;

	const static int MAX_SIZE = 256;
	const static int MIN_SIZE = 1;
};

