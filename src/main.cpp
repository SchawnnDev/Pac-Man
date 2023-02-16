#include <SDL.h>

#include <iostream>
#include "../include/sprite-animation.h"
#include "../include/sprite-handler.h"
#include "../include/animations/banana/banana-dying-animation.h"
#include "../include/utils/constants.h"
#include "../include/board/board.h"
#include "../include/utils/position.h"
#include "../include/game.h"

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;
SDL_Surface* plancheSprites = nullptr;

// Sprite du background
SDL_Rect src_bg = { 200,3, 168,216 }; // x,y, w,h (0,0) en haut a gauche

// Background rectangle
SDL_Rect bg = { 0,0, 672,864 }; // ici scale x4

SDL_Rect ghost_r = { 3,123, 16,16 }; 
SDL_Rect ghost_l = { 37,123, 16,16 }; 
SDL_Rect ghost_d = { 105,123, 16,16 }; 
SDL_Rect ghost_u = { 71,123, 16,16 }; 
SDL_Rect ghost = { getRectCenteredPosition(1,1).x - 32 / 2,getRectCenteredPosition(1,1).y - 32 / 2, 32,32 };     // ici scale x2

int count;

BananaDyingAnimation* bananaDyingAnimation;
SDL_Renderer *m_window_renderer;
SDL_Texture* plancheTexture;
Board* board;

void init()
{
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);
    m_window_renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

    plancheSprites = SDL_LoadBMP("./assets/pacman_sprites.bmp");
    count = 0;
    plancheTexture = SDL_CreateTextureFromSurface(m_window_renderer,plancheSprites);

    SpriteHandler::importSprites("./assets/pacman.sprites");

    board = new Board("./assets/board.xml");
}

void animateGhost()
{
    // petit truc pour faire tourner le fantome
    SDL_Rect* ghost_in = nullptr;
    switch (count/128)
    {
        case 0:
            ghost_in = &(ghost_r);
            ghost.x++;
            break;
        case 1:
            ghost_in = &(ghost_d);
            ghost.y++;
            break;
        case 2:
            ghost_in = &(ghost_l);
            ghost.x--;
            break;
        case 3:
            ghost_in = &(ghost_u);
            ghost.y--;
            break;
    }
    count =(count+1)%(512);

    // ici on change entre les 2 sprites sources pour une jolie animation.
    SDL_Rect ghost_in2 = *ghost_in;
    if ((count/4)%2)
        ghost_in2.x += 17;

    // couleur transparente
    SDL_SetColorKey(plancheSprites, true,  SDL_MapRGB(plancheSprites->format, 0, 0, 0));
    // copie du sprite zoomé
    //SDL_BlitScaled(plancheSprites, &ghost_in2, win_surf, &ghost);
    SDL_RenderCopy(m_window_renderer,plancheTexture,&ghost_in2,&ghost); // Copie du sprite grâce au SDL_Renderer

    if(bananaDyingAnimation->activated())
    {
        auto sprite = bananaDyingAnimation->display();
        if(sprite != nullptr)
        {
            SDL_Rect test = { 672/2,864/2, sprite->rect().w * 4,sprite->rect().h * 4 };
            //SDL_BlitScaled(plancheSprites, &sprite->rect(), win_surf, &test);
            SDL_RenderCopy(m_window_renderer,plancheTexture, &sprite->rect(),&test); // Copie du sprite grâce au SDL_Renderer
        }
    }
}

void draw()
{
    SDL_RenderClear(m_window_renderer);

    board->draw(m_window_renderer, plancheTexture);

    animateGhost();

    SDL_SetRenderDrawColor(m_window_renderer, 255, 255, 255, 255);

    SDL_SetRenderDrawColor(m_window_renderer, 0, 0, 0, 255);

    SDL_RenderPresent(m_window_renderer);
}

int main(int argc, char** argv)
{
    Game game{};
    game.start();
    return 0;
}
