#include <SDL.h>

#include <iostream>
#include "../include/sprite-animation.h"
#include "../include/sprite-handler.h"
#include "../include/animations/banana/banana-dying-animation.h"
#include "../include/constants.h"
#include "../include/board/board.h"

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
SDL_Rect ghost = { 34,34, 32,32 };     // ici scale x2

int count;

BananaDyingAnimation* bananaDyingAnimation;
SDL_Renderer *m_window_renderer;
SDL_Texture* plancheTexture;
Board* board;

void init()
{
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 672, 864, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);
    m_window_renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

    plancheSprites = SDL_LoadBMP("./assets/pacman_sprites.bmp");
    count = 0;
    plancheTexture = SDL_CreateTextureFromSurface(m_window_renderer,plancheSprites);

    SpriteHandler::importSprites("./assets/pacman.sprites");
    bananaDyingAnimation = new BananaDyingAnimation();

    board = new Board("./assets/board.xml");
}
// case_width 672 / 21
SDL_Rect case_rect = { 0,0, 672 / 21, 864/27 };
// fonction qui met à jour la surface de la fenetre "win_surf"

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
    //SDL_SetColorKey(plancheSprites, true, 0);
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


    //SDL_SetColorKey(plancheSprites, false, 0);

//    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);
    SDL_RenderCopy(m_window_renderer,plancheTexture,&src_bg,&bg); // Copie du sprite grâce au SDL_Renderer

    board->draw(m_window_renderer);

    animateGhost();


    SDL_SetRenderDrawColor(m_window_renderer, 255, 255, 255, 255);

/*
    for (int i = 0; i < 27; ++i) {
        for (int j = 0; j < 21; ++j) {
            SDL_Rect sdlRect = { j* (672 / 21),i * (864/27), 672 / 21, 864/27 };
            SDL_RenderDrawRect(m_window_renderer, &sdlRect);
        }
    }
*/


    SDL_SetRenderDrawColor(m_window_renderer, 0, 0, 0, 255);

    SDL_RenderPresent(m_window_renderer);
}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
		std::cerr <<"Echec de l'initialisation de la SDL "<<SDL_GetError() << std::endl;
		return 1;
    }

	init();
    // BOUCLE PRINCIPALE
	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		while (!quit && SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			default: break;
			}
		}

        // Gestion du clavier        
        int nbk;
        const Uint8* keys = SDL_GetKeyboardState(&nbk);
        if (keys[SDL_SCANCODE_ESCAPE])
            quit = true;
        if (keys[SDL_SCANCODE_LEFT]) { puts("LEFT"); ghost.x = std::max(ghost.x - 1, 0); }
        if (keys[SDL_SCANCODE_RIGHT]) { puts("RIGHT"); ghost.x++; }
        if(keys[SDL_SCANCODE_SPACE]) { bananaDyingAnimation->start(); }

       // printf("(x: %d , y: %d)\n", ghost.x, ghost.y);

        // AFFICHAGE
		draw();
		SDL_UpdateWindowSurface(pWindow); 
        // LIMITE A 60 FPS
		SDL_Delay(16); // utiliser SDL_GetTicks64() pour plus de precisions
	}

    SDL_DestroyTexture(plancheTexture);
    SDL_DestroyRenderer(m_window_renderer);
    SDL_Quit(); // ON SORT
    return 0;
}
