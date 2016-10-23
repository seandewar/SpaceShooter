#include "State.h"


State::State(std::string _name = "State") :
	name(_name),
	update(true)
{
}


State::~State()
{
}


std::string State::GetName() const
{
	return name;
}