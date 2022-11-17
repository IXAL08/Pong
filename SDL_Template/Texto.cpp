#include "Texto.h"

#include "SDL_ttf.h"
#include "Game.h" // g_game

Texto::Texto()
{
	textura = NULL;
}
Texto::Texto(const char* _texto, int _x, int _y)
{
    SetText(_texto);
    SetPos(_x, _y);
}
Texto::Texto(const char* _texto, int _x, int _y, int _r, int _g, int _b)
{
    SetText(_texto, _r, _g, _b);
    SetPos(_x, _y);
}
Texto::~Texto()
{
    SDL_DestroyTexture(textura);
}
void Texto::Dibujar()
{
    if(estaActivo)
        SDL_RenderCopy(g_game.renderer, textura, NULL, &rect); //IMprimimos el texto
}
void Texto::SetPos(int _x, int _y)
{
    rect = { _x, _y, w, h };
}
void Texto::SetText(const char* _texto, int _r, int _g, int _b) // _r, _g y _b son opcionales y son 0 en caso de no recibir
{
    SDL_Color textColor = { _r, _g, _b, 0 }; // RGBA
    SDL_Surface* textSurface = TTF_RenderText_Solid(g_game.gFont, _texto, textColor);
    textura = SDL_CreateTextureFromSurface(g_game.renderer, textSurface);
    w = textSurface->w;
    h = textSurface->h;
    SDL_FreeSurface(textSurface);
}

void Texto::SetActivo(bool _v)
{
    estaActivo = _v;
}
bool Texto::GetActivo()
{
    return estaActivo;
}