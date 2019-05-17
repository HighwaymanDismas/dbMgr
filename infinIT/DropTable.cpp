#include "pch.h"
#include "DropTable.h"


DropTable::DropTable(std::string command)
{
	this->command = command;
}

DropTable::~DropTable()
{
}

bool DropTable::validate()
{
	name = command.substr(5);
	name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());

	if (!table_exists(name))
	{
		std::cout << "!!! TABLE " << name << " DOESN'T EXIST !!!\n";
		return false;
	}

	return true;
}

void DropTable::execute()
{
	if (!validate())
		return;

	std::string tmpName = name;

	if (remove(tmpName.append(".txt").c_str()) != 0)
		std::cout << "!!! COULDN'T REMOVE FILE " << name << " !!!\n";
	else
		std::cout << "!!! TABLE " << name << " REMOVED SUCCESSFULLY !!!\n";
}
