#pragma once
#include <stdexcept>


class GameError: public std::logic_error
{
public:
	GameError(const std::string& msg) : std::logic_error(msg) { message = msg; }
	inline char const* what() const override {
		return message.c_str();
	}
protected:
	std::string message;
};
