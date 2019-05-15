#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <regex>

#include "InputManager.h"
#include "Instruction.h"
#include "CreateTable.h"
#include "InsertInto.h"

class CommandManager
{
public:
	CommandManager();
	CommandManager(std::vector<std::string> commands);
	~CommandManager();

	void parse();

private:
	InputManager inputManager;

	std::regex patternCreate;
	std::regex patternInsert;
	std::regex patternSelect;
	std::regex antiPatternCommand;

	std::vector<std::string> commands;

	void set_regex_patterns();
};

