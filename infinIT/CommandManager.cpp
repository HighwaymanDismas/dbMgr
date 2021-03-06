﻿#include "pch.h"
#include "CommandManager.h"

CommandManager::CommandManager()
{
	set_regex_patterns();
	inputManager.take_input();

	this->commands = inputManager.get_commands();
}

CommandManager::CommandManager(std::vector<std::string> commands)
{
	set_regex_patterns();

	this->commands = commands;
}

CommandManager::~CommandManager()
{
	//delete instruction;
}

void CommandManager::parse()
{
	std::smatch result;

	for (std::string cmd : commands)
	{
		Instruction *instruction = nullptr;

		if (std::regex_search(cmd, result, antiPatternCommand))
		{
			std::cout << "!!! INVALID SYNTAX !!!\n";
			return;
		}

		if (std::regex_search(cmd, result, patternCreate))
		{
			instruction = new CreateTable(cmd);
			instruction->execute();
		}
		else if (std::regex_search(cmd, result, patternInsert))
		{
			instruction = new InsertInto(cmd);
			instruction->execute();
		}
		else if (std::regex_search(cmd, result, patternSelect))
		{
			instruction = new SelectFrom(cmd);
			instruction->execute();
		}
		else if (std::regex_search(cmd, result, patternDelete))
		{
			instruction = new DeleteFrom(cmd);
			instruction->execute();
		}
		else if (std::regex_search(cmd, result, patternDrop))
		{
			instruction = new DropTable(cmd);
			instruction->execute();
		}
		else
			std::cout << "!!! UNKNOWN INSTRUCTION !!!\n";

		delete instruction;
	}
}

void CommandManager::set_regex_patterns()
{
	patternCreate = std::regex("^(CREATE)\\b");
	patternInsert = std::regex("^(INSERT INTO)\\b");
	patternSelect = std::regex("^(SELECT)\\b");
	patternDelete = std::regex("^(DELETE FROM)\\b");
	patternDrop = std::regex("^(DROP)\\b");
	antiPatternCommand = std::regex("[\\)]\\s*(INSERT|CREATE|SELECT|DROP|DELETE)");
}