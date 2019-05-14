#include "pch.h"
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
	delete instruction;
}

void CommandManager::parse()
{
	std::smatch result;

	for (std::string cmd : commands)
	{
		if (std::regex_search(cmd, result, patternCreate))
		{
			instruction = new CreateTable(cmd);
			instruction->validate();
		}
		else if (std::regex_search(cmd, result, patternInsert))
			std::cout << "zjebalem sie\n";
		else if (std::regex_search(cmd, result, patternSelect))
			std::cout << "select XD\n";
	}

}

void CommandManager::set_regex_patterns()
{
	this->patternCreate = std::regex("CREATE");
	this->patternInsert = std::regex("INSERT INTO");
	this->patternSelect = std::regex("SELECT");
}