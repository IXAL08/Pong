#ifndef GAME_H
#define GAME_H
///Basado en http://windrealm.org/tutorials/sdl/sdl2-base-cpp.php

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <cstdio> ///Se puede remover
#include <map> //#hash tables <--- Lo usaremos para manejo de teclado
#include "Sprite.h"
#include "Texto.h"
#include "Audio.h"
#include "Animacion.h" //Imagen.h

class Game
{
    public:
        Game();
        ~Game();
        void start(); ///Iniciador
        void stop() ; ///cerrar ventana
        void Init(); ///Funcion para iniciar
        void fpsChanged( int fps ); ///Solo imprime en el titulo de la ventana los fps
        void onQuit(); ///Se llama para salir
        void onKeyDown( SDL_Event* event ); ///Detectar un DOWN
        void onKeyUp( SDL_Event* event ); ///Detectar un UP
        void onMouse(SDL_Event* event);
        void run(); ///Ejecuta la ventana
        void update();
        void draw();

        SDL_Renderer* renderer; //La hoja donde podemos dibujar
        TTF_Font *gFont = NULL; ///Fuente global
private:
        std::map<int,int> keys;
        int frameSkip ;
        int running ;
        SDL_Window* window;

        Sprite player, enemigo, bola;
        Imagen img;
        Texto txt_hola;
        unsigned int img_tiempo; //Controlar que la imagen se dibuje despues de 3 segundos de estar jugando
        unsigned int txt_hola_timepo; //Al dibujar la imagne, se ocultara despues de 3 segundos
        //Animacion anim_mona;
        //Solo se necesita 1 por todas animaciones que tendran
        unsigned int tick_frameAnterior;
        float delta;

        //Sonido
        Mix_Music* msc_fondo = NULL;
        Audio snd_up;
        Audio snd_coin;
};

extern Game g_game; //SINGLETON -> Una estancia de una clase, que es GLOBAL y solo existe 1 en mi mundo

#endif // GAME_H
