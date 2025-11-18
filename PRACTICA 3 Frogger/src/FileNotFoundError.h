#pragma once
#include "GameError.h"
class FileNotFoundError : public GameError
{
public:
	FileNotFoundError(const std::string& msg) : GameError(msg) {}
};


