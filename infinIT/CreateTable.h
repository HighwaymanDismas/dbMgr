#pragma once

#include "Instruction.h"
#include <iostream>
#include <regex>
#include <vector>

class CreateTable : public Instruction
{
public:
	CreateTable(std::string command);
	~CreateTable();

	virtual bool validate() override;
	virtual void execute() override;

private:
	bool validate_param(std::string param);

	std::regex patternParameters;
	std::regex patternParameter;

	std::smatch match;

	std::string name;
	std::string bufferParams;

	std::vector<std::string> params;
};

