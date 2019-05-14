#include "pch.h"

#pragma region Libraries

#include <iostream>
#include <sstream>
#include <string>

#pragma endregion

#pragma region Classes

#include "InputManager.h"
#include "CommandManager.h"

#pragma endregion

int main()
{
	CommandManager commandManager;
	commandManager.parse();

	return 0;
}