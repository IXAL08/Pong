#include "Pelota.h"
#include "Game.h" //  g_game

Pelota::Pelota()
{
    Reiniciar();
    rect.w = 20;
    rect.h = 20;
}

Pelota::~Pelota()
{
}

void Pelota::Dibujar()
{
    rect.x = (int)posX;
    rect.y = (int)posY;
    SDL_SetRenderDrawColor(g_game.renderer, 0, 255, 0, SDL_ALPHA_OPAQUE); ///Seleccionamos el color Rojo //<-- Maquina de estado
    SDL_RenderFillRect(g_game.renderer, &rect); ///Dibujamos Cubo
}

void Pelota::Reiniciar()
{
    SetPos((DISPLAY_WIDTH/2), (DISPLAY_HEIGHT/2));
    velocidadX = -1.0f;
    velocidadY = -1.0f;
}

void Pelota::Mover(float _delta)
{
    // Si no se multiplica por delta, estamos hablando que la velocidad es por frame, ejemplo 1.8f px x frame
    // Si se multiplica por delta, estamos hablando que la velocidad es por segundo, ejemplo a 5px x segundo

    posX += velocidadX;
    posY += velocidadY;

    // Ya colisione con un jugador? 
    if (posX <= g_game.player.x + 20 && (posY >= g_game.player.y && posY <= (g_game.player.y + 60)))
    {
        velocidadX = -velocidadX;
    }

    
    if (posX > g_game.enemigo.x + 436 && (posY >= g_game.enemigo.y && posY <= (g_game.enemigo.y + 60)))
    {
        velocidadX = -velocidadX;
    }
    
    


    // Derecha
    if (posX + rect.w > DISPLAY_WIDTH) 
    {
        Reiniciar(); // Invertir velocidad en X
        velocidadX = -velocidadX;
        velocidadY = -velocidadY;
    }
    //Izquierda
    if (posX < 0)
    {
        Reiniciar();
        velocidadX = -velocidadX;
        velocidadY = -velocidadY;
    }
    //Abajo
    if (posY + rect.h > DISPLAY_HEIGHT) 
    {
        posY = DISPLAY_HEIGHT - rect.h;
        velocidadY = -velocidadY; // Invertir velocidad en Y
    }
    //Arriba
    if (posY < 0)
    {
        posY = 0;
        velocidadY = -velocidadY;
    }
}

void Pelota::SetPos(float _x, float _y)
{
    SetX(_x);
    SetY(_y);
}

void Pelota::SetX(float _x)
{
    posX = _x;
}

void Pelota::SetY(float _y)
{
    posY = _y;
}

void Pelota::SetActivo(bool _v)
{
    estaActivado = _v;
}

bool Pelota::GetActivo()
{
    return estaActivado;
}