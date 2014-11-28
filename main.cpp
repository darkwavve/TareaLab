
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<list>
#include<vector>
#include<map>
#include<fstream>
#include "PersonajeJugador.h"
#include "NPC.h"
#include <stdlib.h>     /* srand, rand */

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character;
SDL_Rect rect_background,rect_character;

class Tile
{
public:
    int fuente_x;
    int fuente_y;
    int destino_x;
    int destino_y;
    Tile(int fuente_x, int fuente_y, int destino_x, int destino_y)
    {
        this->fuente_x=fuente_x;
        this->fuente_y=fuente_y;
        this->destino_x=destino_x;
        this->destino_y=destino_y;
    }
};

vector<Tile*> cargarTiles(string nombre_archivo)
{
    vector<Tile*> tiles;
    ifstream archivo(nombre_archivo.c_str());
    for(int destino_y=0; destino_y<10; destino_y++)
    {
        for(int destino_x=0; destino_x<10; destino_x++)
        {
            int fuente_x;
            int fuente_y;
            archivo>>fuente_x;
            archivo>>fuente_y;
            tiles.push_back(new Tile(fuente_x,fuente_y,destino_x,destino_y));
        }
    }
    archivo.close();
    return tiles;
}

void dibujarTile(SDL_Texture *tileset_texture, SDL_Renderer* renderer,
        int fuente_x, int fuente_y, int destino_x, int destino_y)
{
    SDL_Rect fuente,destino;
    fuente.x = 32*fuente_x;
    fuente.y = 32*fuente_y;
    fuente.w = 32;
    fuente.h = 32;

    destino.x = 32*destino_x;
    destino.y = 32*destino_y;
    destino.w = 32;
    destino.h = 32;


    SDL_RenderCopy(renderer,tileset_texture,&fuente,&destino);
}

int main( int argc, char* args[] )
{
    cargarTiles("assets/tile.map");
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 500/*WIDTH*/, 250/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0; rect_background.y = 0; rect_background.w = w; rect_background.h = h;

    character = IMG_LoadTexture(renderer, "assets/personaje/down.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 0;
    rect_character.y = 100;
    rect_character.w = w;
    rect_character.h = h;


    list<Personaje*>personajes;
    personajes.push_back(new PersonajeJugador (0,128,renderer,&personajes));

    SDL_Texture* tileset_texture = IMG_LoadTexture(renderer, "assets/tileset.png");
    vector<Tile*>tiles=cargarTiles("assets/tile.map");

    //Main Loop
    int frame=0;
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
        }

        for(list<Personaje*>::iterator i = personajes.begin();
                i!=personajes.end();
                i++)
            (*i)->logic((Uint8*)SDL_GetKeyboardState( NULL ));

        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        for(int i=0;i<tiles.size();i++)
        {
            dibujarTile(tileset_texture,renderer,
                    tiles[i]->fuente_x,tiles[i]->fuente_y,
                    tiles[i]->destino_x,tiles[i]->destino_y);
        }

       for(int x = 0; x < 16; x++)
        {
            for(int y = 0 ; y < 8 ; y++)
            {
            dibujarTile(tileset_texture,renderer,
                            1,11,
                            x ,y);
            }
        }
         for(int x = 0; x <= 15; x++)
        {
            for(int y = 3; y < 5; y++)
//                if(x != 11)
                dibujarTile(tileset_texture,renderer,
                            11,15,
                            x,y);
        }
        //Grama
        for(int x = 0; x <= 11 ; x++)
        {
            if(x == 0)
            {
            dibujarTile(tileset_texture,renderer,
                            12,8,
                            x,5);
            dibujarTile(tileset_texture,renderer,
                            12,9,
                            x,6);
            dibujarTile(tileset_texture,renderer,
                            12,10,
                            x,7);
            }
            if(x > 0 && x < 10)
            {
                dibujarTile(tileset_texture,renderer,
                            13,8,
                            x,5);
                dibujarTile(tileset_texture,renderer,
                            13,9,
                            x,6);
                dibujarTile(tileset_texture,renderer,
                            13,10,
                            x,7);
            }
            if(x == 10)
            {
            dibujarTile(tileset_texture,renderer,
                            14,8,
                            x,5);
            dibujarTile(tileset_texture,renderer,
                            14,9,
                            x,6);
            dibujarTile(tileset_texture,renderer,
                            14,10,
                            x,7);
            }
        }
        //Lago
        for(int x = 11; x <= 15; x++)
        {
                if(x == 11)
                {
                dibujarTile(tileset_texture,renderer,
                            27,2,
                             x,5);
                dibujarTile(tileset_texture,renderer,
                            27,3,
                             x,6);
                dibujarTile(tileset_texture,renderer,
                            27,3,
                             x,7);
                }
                if(x <= 15 && x > 11)
                {
                dibujarTile(tileset_texture,renderer,
                            28,2,
                             x,5);
                dibujarTile(tileset_texture,renderer,
                            28,3,
                             x,6);
                dibujarTile(tileset_texture,renderer,
                            28,3,
                            x,7);
                }
            }
        for(int x = 0 ; x < 16 ; x++)
        {
            if(x == 0 || x == 2 || x == 12 || x == 14)
            {
            dibujarTile(tileset_texture,renderer,
                            24,19,
                            x,0);
            dibujarTile(tileset_texture,renderer,
                            24,20,
                            x,1);
            }
            if(x == 4 || x== 11 )
            {
            dibujarTile(tileset_texture,renderer,
                            28,19,
                            x,0);
            dibujarTile(tileset_texture,renderer,
                            28,20,
                            x,1);
            }
            if(x == 1 || x == 3 || x == 13 || x == 15)
            {
            dibujarTile(tileset_texture,renderer,
                            25,19,
                            x,0);
            dibujarTile(tileset_texture,renderer,
                            25,20,
                            x,1);
            }

        }
        //Pasaje
        dibujarTile(tileset_texture,renderer,
                            24,6,
                            5,0);
        dibujarTile(tileset_texture,renderer,
                            25,6,
                            6,0);
        dibujarTile(tileset_texture,renderer,
                            26,6,
                            7,0);
        dibujarTile(tileset_texture,renderer,
                            24,7,
                            5,1);
        dibujarTile(tileset_texture,renderer,
                            25,7,
                            6,1);
        dibujarTile(tileset_texture,renderer,
                            26,7,
                            7,1);
        dibujarTile(tileset_texture,renderer,
                            24,8,
                            5,2);
        dibujarTile(tileset_texture,renderer,
                            25,8,
                            6,2);
        dibujarTile(tileset_texture,renderer,
                            26,8,
                            7,2);
        dibujarTile(tileset_texture,renderer,
                            24,9,
                            5,3);
        dibujarTile(tileset_texture,renderer,
                            25,9,
                            6,3);
        dibujarTile(tileset_texture,renderer,
                            26,9,
                            7,3);
        dibujarTile(tileset_texture,renderer,
                            27,6,
                            8,0);
        dibujarTile(tileset_texture,renderer,
                            28,6,
                            9,0);
        dibujarTile(tileset_texture,renderer,
                            29,6,
                            10,0);
        dibujarTile(tileset_texture,renderer,
                            27,7,
                            8,1);
        dibujarTile(tileset_texture,renderer,
                            28,7,
                            9,1);
        dibujarTile(tileset_texture,renderer,
                            29,7,
                            10,1);
        dibujarTile(tileset_texture,renderer,
                            27,8,
                            8,2);
        dibujarTile(tileset_texture,renderer,
                            28,8,
                            9,2);
        dibujarTile(tileset_texture,renderer,
                            29,8,
                            10,2);
        dibujarTile(tileset_texture,renderer,
                            27,9,
                            8,3);
        dibujarTile(tileset_texture,renderer,
                            28,9,
                            9,3);
        dibujarTile(tileset_texture,renderer,
                            29,9,
                            10,3);


        for(list<Personaje*>::iterator i = personajes.begin();
                i!=personajes.end();
                i++)
            (*i)->render(renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(16.66);
    }

	return 0;
}
