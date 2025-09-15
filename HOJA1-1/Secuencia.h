#pragma once
#include <array>
#include <iostream>
class Secuencia
{

public:

	Secuencia();

	//FUNCIONES
	//a)
	void MoveRight();


private:

	std::array <int, 5> values { 1, 2, 3, 4, 5 };

	void PrintResult();

};

