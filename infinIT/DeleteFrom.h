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
};

