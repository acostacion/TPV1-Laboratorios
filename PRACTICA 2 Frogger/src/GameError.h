#pragma once
#include <stdexcept>


class GameError: public std::logic_error
{
public:
	GameError(const std::string& msg) : std::logic_error(msg) { message = msg; }
	char const* what() const override {
		return std::logic_error::what();
	}
protected:
	std::string message;
};
