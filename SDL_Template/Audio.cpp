#include "Audio.h"

Audio::~Audio() //Destructor
{
	Mix_FreeChunk(sonido);
}
void Audio::Cargar(const char* _archivoPath)
{
	sonido= Mix_LoadWAV(_archivoPath);
}
void Audio::Play()
{
	Mix_PlayChannel(-1, sonido, 0); //Canal, sonido, repeticiones
}