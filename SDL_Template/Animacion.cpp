#include "Animacion.h"

Animacion::Animacion()
{
	frameActual = 0.0f;
}

Animacion::~Animacion()
{
	for (int i = 0; i<imagenes.size(); i++)
	{
		delete imagenes[i];
	}
}

void Animacion::SetFPS(int _fps)
{
	fps = _fps;
}
void Animacion::AgregarImagen(const char* _file)
{
	Imagen* img = new Imagen();
	img->CargarImagen(_file, 0, 0);
	imagenes.push_back(img);
}
void Animacion::Dibujar(float _delta)
{
	frameActual += _delta * fps;
	if (frameActual >= imagenes.size())
	{
		frameActual = frameActual - imagenes.size();
	}
	int frameDibujar = (int)frameActual; // Eliminamos los puntos decimales

	imagenes[frameDibujar]->SetPos(x, y);
	imagenes[frameActual]->Dibujar();
}
void Animacion::SetPos(int _x, int _y)
{
	x = _x;
	y = _y;
}
