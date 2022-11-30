#pragma once

#include "SDL.h"

class Pelota
{
public:
    Pelota();
    virtual ~Pelota();

    void Dibujar();

    void Reiniciar();
    void Mover(float _delta);
    void SetPos(float _x, float _y);
    void SetX(float _x);
    void SetY(float _y);
    void SetActivo(bool _v);
    bool GetActivo();
    float posX;
    float posY;
    SDL_Rect rect; // Posicion

protected:

private:

    bool estaActivado;

    
    float velocidadX; // Velocidad
    float velocidadY;
};
