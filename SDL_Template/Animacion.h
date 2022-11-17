#pragma once

#include "Imagen.h"
#include <vector>

class Animacion
{
public:
	Animacion();
	~Animacion();
	void SetFPS(int _fps); //Indicar a cuantos FPS corre la animaci�n
	void AgregarImagen(const char* _file);
	void Dibujar(float _delta);
	void SetPos(int _x, int _y);

private:
	std::vector<Imagen*> imagenes;
	float frameActual; //Ir avanzado entre frames
	int fps; //A cuantos FPS corre esta animaci�n
	int x;
	int y;

};

