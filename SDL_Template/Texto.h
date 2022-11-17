#pragma once

#include "SDL.h"
#include <string>

using namespace std;

class Texto
{
public:
	Texto();
	Texto(const char* _texto, int _x, int _y);
	Texto(const char* _texto, int _x, int _y, int _r, int _g, int _b);
	~Texto();
	void Dibujar();
	void SetPos(int _x, int _y);
	void SetText(const char* _texto, int _r = 0, int _g = 0, int _b = 0);
	void SetActivo(bool _v);
	bool GetActivo();

private:
	SDL_Texture* textura; //Imagen con formato compatible con SDL
	SDL_Rect rect;
	int w; //Ancho y alto de la palabara, para si lo movemos de lugar
	int h;
	bool estaActivo;
};

