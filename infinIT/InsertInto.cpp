#include "pch.h"
#include "InsertInto.h"

InsertInto::InsertInto()
{
}

InsertInto::InsertInto(std::string command)
{
	this->command = command;

	patternParameters = std::regex("\\(.+\\)");
	patternVarchar = std::regex("\"[\\s\\S]+?\"");
	patternBoolean = std::regex("\\b(TRUE|FALSE)\\b", std::regex_constants::icase);
}

InsertInto::~InsertInto()
{
	file.close();
}

bool InsertInto::validate()
{
	if (!std::regex_search(command, match, patternParameters))
		return false;

	name = command.substr(12, match.position() - 13);
	command = command.substr(match.position());
	name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());

	if (!table_exists(name))
	{
		std::cout << name << " Tabela NIE istnieje XDDDDDDD\n";
		return false;
	}

	get_table_params();
	get_insert_data();
	
	if (!validate_data())
		return false;

	file.close();

	return true;
}

void InsertInto::execute()
{
	if (!validate())
		return;

	file.open(name, std::ios::out | std::ios::app);

	file << "\n";
	for (std::string word : data)
	{
		if(word != data.back())
			file << word << ",";
		else
			file << word << ";";
	}

	std::cout << "!!! DATA ADDED SUCCESSFULLY !!!\n";
}

void InsertInto::get_table_params()
{
	file.open(name.append(".txt"));

	std::string buffer;
	std::getline(file, buffer);
	params = split(buffer, ",");

	for (size_t itr = 0; itr < params.size(); itr++)
	{
		if (std::regex_search(params[itr], match, std::regex("Integer")))
			params[itr] = "Integer";
		else if (std::regex_search(params[itr], match, std::regex("Float")))
			params[itr] = "Float";
		else if (std::regex_search(params[itr], match, std::regex("Boolean")))
			params[itr] = "Boolean";
		else if (std::regex_search(params[itr], match, std::regex("Varchar")))
		{
			std::regex_search(params[itr], match, std::regex("\\(\\d+\\)"));
			std::string tmp = match[0];
			std::regex_search(tmp, match, std::regex("\\d+"));

			varcharSizes.push_back(std::stoi(match[0]));
			params[itr] = "Varchar";
		}
	}

	tableSize = params.size();
}

void InsertInto::get_insert_data()
{
	command.erase(0, 1);
	command.erase(command.find(")"));
	
	data = split(command, ",");

	for (size_t itr = 0; itr < data.size(); itr++)
	{
		if (std::regex_search(data[itr], match, patternVarchar))
			data[itr] = match[0];
		else if (std::regex_search(data[itr], match, patternBoolean))
			data[itr] = match[0];
		else if (std::regex_search(data[itr], match, std::regex("\\d+.\\d+")))
			data[itr] = match[0];
		else if (std::regex_search(data[itr], match, std::regex("\\d+")))
			data[itr] = match[0];
		else
			data[itr] = "_INVALID";
	}

}

bool InsertInto::validate_data()
{
	if (tableSize != data.size())
	{
		std::cout << "!!! WRONG NUMBNER OF PARAMETERS !!!\n";
		return false;
	}

	int i = 0;

	for (size_t itr = 0; itr < tableSize; itr++)
	{
		if (data[itr] == "_INVALID")
		{
			std::cout << "!!! INVALID PARAMETERS !!!\n";
			return false;
		}

		if (params[itr] == "Varchar")
		{
			if (!std::regex_search(data[itr], match, patternVarchar))
			{
				std::cout << "!!! WRONG DATA TYPE; EXPECTED VARCHAR !!!\n";
				return false;
			}

			if (data[itr].size() > varcharSizes[i++])
			{
				std::cout << "!!! VARCHAR TYPE DATA TOO LONG !!!\n";
				return false;
			}
		}

		if (params[itr] == "Float")
		{
			if (!std::regex_search(data[itr], match, std::regex("\\d+.\\d+")))
			{
				std::cout << "!!! WRONG DATA TYPE; EXPECTED FLOAT !!!\n";
				return false;
			}

		}

		if (params[itr] == "Integer")
		{
			if (!std::regex_search(data[itr], match, std::regex("^\\d+$")))
			{
				std::cout << "!!! WRONG DATA TYPE; EXPECTED INTEGER !!!\n";
				return false;
			}

		}

		if (params[itr] == "Boolean")
		{
			if (!std::regex_search(data[itr], match, patternBoolean))
			{
				std::cout << "!!! WRONG DATA TYPE; EXPECTED BOOLEAN !!!\n";
				return false;
			}

		}
	}

	return true;
}
