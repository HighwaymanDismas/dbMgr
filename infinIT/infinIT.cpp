#include "pch.h"

#pragma region Libraries

#include <iostream>
#include <sstream>
#include <string>
#include <regex>

#pragma endregion

#pragma region Classes

#include "InputManager.h"

#pragma endregion

int main()
{
	InputManager inputManager;
	inputManager.take_input();
	
	std::vector<std::string> commands = inputManager.get_commands();

	for (auto cmd : commands)
		std::cout << cmd << std::endl;

	return 0;
}