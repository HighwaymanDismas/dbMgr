#include "pch.h"
#include "SelectFrom.h"

SelectFrom::SelectFrom(std::string command)
{
	this->command = command;
}

SelectFrom::~SelectFrom()
{
}

bool SelectFrom::validate()
{
	return true;
}

void SelectFrom::execute()
{
}
