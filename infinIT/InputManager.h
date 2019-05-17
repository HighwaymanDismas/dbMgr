#pragma once

#include <string>
#include <iostream>
#include <vector>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void take_input();

	std::string get_input();
	std::vector<std::string> get_commands();

private:
	std::string inputStream;
	std::vector<std::string> commands;

	void split_commands();
};

