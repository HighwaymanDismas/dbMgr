#pragma once

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
	std::regex patternDrop;
	std::regex patternDelete;
	std::regex antiPatternCommand;

	std::vector<std::string> commands;

	void set_regex_patterns();
};

