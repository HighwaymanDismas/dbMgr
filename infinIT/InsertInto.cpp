#include "pch.h"
#include "InsertInto.h"

InsertInto::InsertInto(std::string command)
{
	this->command = command;

	patternParameters = std::regex("\\(.+\\)");
}

InsertInto::~InsertInto()
{
}

/*TODO: 
	getting column types from table; check them against insert args
*/

bool InsertInto::validate()
{
	if (std::regex_search(command, match, patternParameters))
		std::cout << match[0] << std::endl;
	else
		return false;

	name = command.substr(12, match.position() - 13);
	name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());

	if (table_exists(name))
		std::cout << name << " Tabela istnieje XDDDDDDD\n";
	else
		std::cout << name << " Tabela NIE istnieje XDDDDDDD\n";

	return true;
}

void InsertInto::execute()
{
}
