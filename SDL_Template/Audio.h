#pragma once

#include "SDL_mixer.h"

class Audio
{
public:
	~Audio(); //Destructor
	void Cargar(const char* _archivoPath);
	void Play();

private:

	Mix_Chunk* sonido;
};

