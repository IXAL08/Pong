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

protected:

private:

    SDL_Rect rect; // Posicion
    bool estaActivado;

    float posX;
    float posY;
    float velocidadX; // Velocidad
    float velocidadY;
};
