#include "pch.h"
#include "InputManager.h"


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::take_input()
{
	std::string line;

	while (!std::cin.eof())
	{
		std::getline(std::cin, line);
		inputStream.append(line);
	}
}

void InputManager::split_commands()
{
	std::string delimiter(";");
	size_t last = 0;
	size_t next = 0;

	while ((next = inputStream.find(delimiter, last)) != std::string::npos)
	{ 
		commands.push_back(inputStream.substr(last, next - last));
		last = next + 1;
	}

	commands.push_back(inputStream.substr(last));
}

std::string InputManager::get_input()
{
	return inputStream;
}

std::vector<std::string> InputManager::get_commands()
{
	split_commands();

	return commands;
}
