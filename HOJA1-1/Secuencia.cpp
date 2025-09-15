#include "Secuencia.h"

Secuencia::Secuencia()
{
	
}

void Secuencia::PrintResult()
{
	for (int i = 0; i < values.size(); i++) {
		std::cout << values[i] << " ";
	}
}

void Secuencia::MoveRight()
{
	int aux = values[values.size()-1]; //guardamos el ultimo elemento

	//desplazamiento a la derechoe
	for (int i = values.size() - 1; i >= 1; i--) {
		values[i] = values[i - 1];
	}

	//colocamos el ultimo valor al principio
	values[0] = aux;

	PrintResult();
	
}

