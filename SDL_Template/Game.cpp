#include "Game.h"

#include <iostream>
#include <string>



Game g_game; ///Singleton
int MarcadorA = 0, MarcadorB = 0;

void Game::draw()
{
    ///Limpiamos ventana
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); //RGB [0,255]
    SDL_RenderClear(renderer);

    //Se dibuja de Atras para Adelante

    ///DIBUJO--------------------
    ///Dibujo de cubo
    SDL_Rect CuboRect;
    CuboRect.x = 10;
    CuboRect.y = player.y;
    CuboRect.w = 15;
    CuboRect.h = 60;

    SDL_Rect enemy;
    enemy.x = 455;
    enemy.y = enemigo.y;
    enemy.w = 15;
    enemy.h = 60;

 


    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); ///Seleccionamos el color Rojo //<-- Maquina de estado
    SDL_RenderFillRect(renderer, &CuboRect);///Dibujamos al jugador
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &enemy);//Dibujamos el rival
   

    /// Dibujar Punto SDL_RenderDrawPoint    https://wiki.libsdl.org/SDL_RenderDrawPoint
    /// Dibujar Linea SDL_RenderDrawLine    https://wiki.libsdl.org/SDL_RenderDrawLine
    /// Dibujar Lineas SDL_RenderDrawLines    https://wiki.libsdl.org/SDL_RenderDrawLines
    ///Dibujar Cuadros sin relleno SDL_RenderDrawRect   https://wiki.libsdl.org/SDL_RenderDrawRect

    ///Dibujar texto
    std::string TextoImp = " : ";
    TextoImp = to_string(MarcadorA) + TextoImp + to_string(MarcadorB);
    txt_hola.SetText(TextoImp.c_str(), 255, 255, 255);
    txt_hola.SetPos(218, 5);
    txt_hola.Dibujar();

    
    ///Dibujar imagen
    //img.Dibujar();
    bola.Dibujar();
    //anim_mona.Dibujar(delta);

    ///Terminamos de dibujar
    SDL_RenderPresent(renderer); //Plasa en el monitor     back buffer
}

void Game::update()
{
    bola.Mover(delta);
    
    if (keys[SDLK_UP]) //En sistemas operativos, Y esta inversa   Arriba es negativo y abajo es positivo,, 0,0 es esquina superior izquierdo
    {
        enemigo.y -= enemigo.speed;
        if (enemigo.y < 0)
            enemigo.y = 0;
    }
    else if (keys[SDLK_DOWN])
    {
        enemigo.y += enemigo.speed;

        if (enemigo.y + 60 > DISPLAY_HEIGHT)
        {
            enemigo.y = DISPLAY_HEIGHT - 60;
        }
    }

    if (keys[SDLK_w])
    {
        player.y -= player.speed;
        if (player.y < 0)
            player.y = 0;
    }
    else if (keys[SDLK_s])
    {
        player.y += player.speed;

        if (player.y + 60 > DISPLAY_HEIGHT)
        {
            player.y = DISPLAY_HEIGHT - 60;
        }
    }

    if (bola.posX <= 0 )
    {
        MarcadorB++;
    }
    else if(bola.posX >= 460) {

        MarcadorA++;
    }
    

    unsigned int tiempoActual = SDL_GetTicks(); //Tomamos el tiempo actual en este frame,, le toma aprox 49 días dar la vuela (que vuelva desde 0)
    delta = (tiempoActual - tick_frameAnterior) / 1000.0f; // Convertimos milisengundos a segundos

    if (img.GetActivo() == false)
    {
        if (tiempoActual >= img_tiempo + 3000) //Esperamos 3 segundos (esta en milisegundos)
        {
            img.SetActivo(true);
        }
    }
    /*if (txt_hola.GetActivo() == true)
    {
        if (tiempoActual >= txt_hola_timepo)
        {
            txt_hola.SetActivo(false);
        }
    }*/

    tick_frameAnterior = tiempoActual; // Guardamos el valor actual del tick
}

///TECLAS: https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlkey.html
void Game::onKeyDown(SDL_Event* evt)
{
    keys[evt->key.keysym.sym] = 1; ///Indicamos que ese tecla esta activa
}

void Game::onKeyUp(SDL_Event* evt)
{
    keys[evt->key.keysym.sym] = 0; ///Ya no se esta llamando la tecla
}

void Game::onMouse(SDL_Event* evt)
{
    if (evt->type == SDL_MOUSEBUTTONDOWN) //Se dio un click
    {
        if (evt->button.button == SDL_BUTTON_LEFT) //Si con el clik izquierdo
        {
            /*txt_hola.SetPos(evt->motion.x, evt->motion.y);
            txt_hola.SetActivo(true);
            txt_hola_timepo = SDL_GetTicks() + 3000;*/ //Solo quiero que se dibuje por 3 segundos (El tiempo esta en milisegundos)

            snd_coin.Play();
        }
        if (evt->button.button == SDL_BUTTON_RIGHT)
        {
            snd_up.Play();
        }
    }
}

void Game::Init()
{
    img.CargarImagen("Recursos/test_img.bmp", 50, 50);
    txt_hola.SetText("Hola mundo!"); //Por defecto es color negro
    txt_hola.SetPos(20, DISPLAY_HEIGHT - 30);

    img.SetActivo(false);
    //txt_hola.SetActivo(false);
    txt_hola.SetActivo(true);
    //Las variables de manejar , hay que tomarlas hasta el final de Init
    img_tiempo = SDL_GetTicks(); //Totamos el tiempo actual

    //Sonido
    //msc_fondo = Mix_LoadMUS("PathFile.wav");
    //Mix_PlayMusic( msc_fondo, -1 ); //Reticiones infinitas

    snd_coin.Cargar("Recursos/smb_coin.wav");
    snd_up.Cargar("Recursos/smb_1-up.wav");

    

    //Cargamos animacion mona corriendo a la derecha
    /*anim_mona.AgregarImagen("Recursos/mona/der1.bmp");
    anim_mona.AgregarImagen("Recursos/mona/der2.bmp");
    anim_mona.AgregarImagen("Recursos/mona/der3.bmp");
    anim_mona.AgregarImagen("Recursos/mona/der4.bmp");
    anim_mona.AgregarImagen("Recursos/mona/der5.bmp");
    anim_mona.AgregarImagen("Recursos/mona/der6.bmp");
    anim_mona.AgregarImagen("Recursos/mona/der7.bmp");
    anim_mona.AgregarImagen("Recursos/mona/der8.bmp");
    anim_mona.SetFPS(6);
    anim_mona.SetPos(100, 100);*/
}


///Se llama que es hora de salir del juego
void Game::onQuit()
{
    //Mix_FreeMusic(msc_fondo);

    running = 0;
}






///NO CAMBIAR de aqui para abajo,  ---------------------------------------------------------------------------------
Game::Game() :frameSkip(0), running(0), window(NULL), renderer(NULL) {}

Game::~Game()
{
    this->stop();
}

void Game::start() ///Inicializa vetana
{
    int flags = SDL_WINDOW_SHOWN;
    if (SDL_Init(SDL_INIT_EVERYTHING))
        return;

    if (SDL_CreateWindowAndRenderer(DISPLAY_WIDTH, DISPLAY_HEIGHT, flags, &window, &renderer))
        return;

    ///Cargamos la fuente para escribir
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    gFont = TTF_OpenFont("Recursos/lazy.ttf", 12);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    this->running = 1;
    run();
}

void Game::stop() ///Liberamos memoria de SDL
{
    if (NULL != renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (NULL != window)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Game::run()
{
    //Para calculo de FPS
    int past = SDL_GetTicks();
    int now = past, pastFps = past;
    int fps = 0, framesSkipped = 0;

    SDL_Event event; // Eventos => Eventos de ventana (Minimizar, maximar, cerrar, mover ventana) , Teclado y Raton
    Init();
    ///Ciclo de juego
    while (running)
    {
        int timeElapsed = 0;
        ///Eventos (Teclado y Mouse)
        if (SDL_PollEvent(&event)) //Oye SDL, hubo un evento?, si es así, procesalo
        {
            switch (event.type)
            {
            case SDL_QUIT:    onQuit(); //X de la consola o de la ventana
                break;
            case SDL_KEYDOWN: onKeyDown(&event);
                break;
            case SDL_KEYUP:   onKeyUp(&event);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEMOTION:
                onMouse(&event);
                break;
            }
        }

        ///Update y Draw
        ///Esta formula ayuda que corra ya suave, por lo que omite la necesidad de usar DeltaTime
        timeElapsed = (now = SDL_GetTicks()) - past;
        if (timeElapsed >= UPDATE_INTERVAL)
        {
            past = now; //Calculo cuando fue la ultima vez que mostre un frame
            update(); //Calculos de fisica y movimiento
            if (framesSkipped++ >= frameSkip)  // vsync
            {
                draw(); //Dibujo la pantalla
                ++fps;
                framesSkipped = 0;
            }
        }
        /// fps
        if (now - pastFps >= 1000)
        {
            pastFps = now;
            fpsChanged(fps);
            fps = 0;
        }
        ///Retraso de 1ms o SDL se congela
        SDL_Delay(1);
    }
}

void Game::fpsChanged(int fps)
{
    char szFps[128];
    sprintf_s(szFps, "%s: %d FPS", "Nombre de Ventana", fps);
    SDL_SetWindowTitle(window, szFps);
}


/*if( Mix_PausedMusic() == 1 )
    {
        //Resume the music
        Mix_ResumeMusic();
    }
    //If the music is playing
    else
    {
        //Pause the music
        Mix_PauseMusic();
    }*/

    //Stop
    //Mix_HaltMusic();