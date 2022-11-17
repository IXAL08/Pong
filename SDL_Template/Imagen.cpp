#include "Imagen.h"
#include <iostream>

#include "Game.h"
// SDL_IMAGE // PNG y JPG

Imagen::Imagen()
{
    estaActivado = true;
}

Imagen::~Imagen()
{
    SDL_DestroyTexture(texture); ///kuLiberamos memoria
}

void Imagen::CargarImagen(const char* _path, int _x=0, int _y=0)
{
    SDL_Surface* temp = NULL;
    temp = SDL_LoadBMP(_path); ///Cargamos imagen png, jpg, jpeg, bmp, gif

    //Que color al cargar imagenes, lo cambie como transparente
    //SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 0, 2, 20)); //RGB
    texture = SDL_CreateTextureFromSurface(g_game.renderer, temp);

    //Movemos x, y la mitad de w a la izquierda y mitad de h a hacia arriba, para que X,Y sea el centro de la imagen (Y no esquina superior izquierda)
    //En otras palabras, estamos moviendo el pivote al centro de la imagen
    int mitadW = temp->w / 2;
    int mitadH = temp->h / 2;

    rect.x = _x - mitadW;
    rect.y = _y - mitadH;
    rect.w = temp->w;
    rect.h = temp->h;

    SDL_FreeSurface(temp); ///Liberamos temp
}

void Imagen::Dibujar()
{
    if(estaActivado)
        SDL_RenderCopy(g_game.renderer, texture, NULL, &rect);
}

//Al indicar posición, tengo que mover un poco el pivote para que represente el centro de la imagen
void Imagen::SetPos(int _x, int _y)
{
    rect.x = _x - rect.w / 2;
    rect.y = _y - rect.h / 2;
}

void Imagen::SetX(int _x)
{
    rect.x = _x - rect.w / 2;
}

void Imagen::SetY(int _y)
{
    rect.y = _y - rect.h / 2;
}

void Imagen::SetActivo(bool _v)
{
    estaActivado = _v;
}

bool Imagen::GetActivo()
{
    return estaActivado;
}