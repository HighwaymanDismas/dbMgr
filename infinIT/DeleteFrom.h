#pragma once
#include "Instruction.h"

class DeleteFrom : public SelectFrom
{
public:
	DeleteFrom(std::string command);
	~DeleteFrom();

	virtual bool validate() override final;
	virtual void execute() override;

private:
	void remove_all(std::string name);
	void remove_where(std::string name);

	std::vector<std::vector<std::string>> data2D;

	std::string whereCommand;
	std::string conditionValue;

	int colWhereIndex;
};

