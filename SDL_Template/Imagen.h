#ifndef IMAGEN_H
#define IMAGEN_H

//#include "Game.h"
#include "SDL.h"

class Imagen
{
    public:
        Imagen();
        virtual ~Imagen();

        void CargarImagen(const char* _path, int _x, int _y);
        void Dibujar();
        
        void SetPos(int _x, int _y);
        void SetX(int _x);
        void SetY(int _y);
        void SetActivo(bool _v);
        bool GetActivo();

    protected:

    private:
        SDL_Texture* texture;
        SDL_Rect rect; //x, y   
        bool estaActivado;

};

#endif // IMAGEN_H
