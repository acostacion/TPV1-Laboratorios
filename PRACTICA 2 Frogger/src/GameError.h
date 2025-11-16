#pragma once
#include <stdexcept>


class GameError: public std::logic_error
{
public:
	GameError(const std::string& msg) : std::logic_error(msg) {}


};
