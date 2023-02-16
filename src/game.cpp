#include <iostream>
#include "../include/game.h"
#include "../include/sprite-handler.h"

void Game::start()
{

    if (m_state != GameState::WaitingStart)
        return;

    while (m_state != GameState::End)
    {
        handleEvents();
        handleKeys();

        handleLogic();
        handleDrawing();

        SDL_Delay(1000 / FRAMERATE);
    }

}

void Game::end()
{
    m_state = GameState::End;
}


Game::Game()
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        std::cerr <<"Echec de l'initialisation de la SDL "<<SDL_GetError() << std::endl;
        return;
    }

    m_window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE_WIDTH,
                                WINDOW_SIZE_HEIGHT, SDL_WINDOW_SHOWN);
    m_windowRenderer = SDL_CreateRenderer(m_window, -1,
                                          SDL_RENDERER_ACCELERATED);

    m_spriteSurface = SDL_LoadBMP("./assets/pacman_sprites.bmp");
    m_spriteTexture = SDL_CreateTextureFromSurface(m_windowRenderer,
                                                   m_spriteSurface);

    SpriteHandler::importSprites("./assets/pacman.sprites");

    m_board = {"./assets/board.xml"};
    m_state = GameState::WaitingStart;
}

Game::~Game()
{
    SDL_FreeSurface(m_spriteSurface);
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_windowRenderer);
    SDL_Quit();
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                m_state = GameState::End;
                return;
            default:
                break;
        }
    }
}

void Game::handleKeys()
{
    int nbk;
    const Uint8 *keys = SDL_GetKeyboardState(&nbk);
    if (keys[SDL_SCANCODE_ESCAPE])
        m_state = GameState::End;
    // if (keys[SDL_SCANCODE_LEFT]) { puts("LEFT"); ghost.x = std::max(ghost.x - 1, 0); }
    // if (keys[SDL_SCANCODE_RIGHT]) { puts("RIGHT"); ghost.x++; }
    // if(keys[SDL_SCANCODE_SPACE]) { bananaDyingAnimation->start(); }
}

void Game::handleLogic()
{

}

void Game::handleDrawing()
{
    SDL_RenderClear(m_windowRenderer);

    m_board.draw(m_windowRenderer, m_spriteTexture);

    // Draw entities
    m_pacMan.draw(m_windowRenderer, m_spriteTexture);
    m_blinky.draw(m_windowRenderer, m_spriteTexture);

    SDL_RenderPresent(m_windowRenderer);
    SDL_UpdateWindowSurface(m_window);
}
