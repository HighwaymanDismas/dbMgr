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
	bool validate_param(std::string param);
	void create_file(std::string name);

	std::fstream file;

	std::regex patternParameter;
	std::regex patternName;
	std::regex patternType;
};

