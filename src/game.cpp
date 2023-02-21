#include <iostream>

#include "game.h"

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
: m_board("./assets/board.xml"),
    m_spriteHandler("./assets/pacman.sprites"),
    m_pacMan(m_board, {m_spriteHandler.pacmanAnimations()})
    ,m_state{GameState::WaitingStart}
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        std::cerr <<"Echec de l'initialisation de la SDL "<<SDL_GetError() << std::endl;
        return;
    }

    m_window.reset(SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE_WIDTH,
                                WINDOW_SIZE_HEIGHT, SDL_WINDOW_SHOWN));
    m_windowRenderer.reset(SDL_CreateRenderer(m_window.get(), -1,
                                          SDL_RENDERER_ACCELERATED));

    m_spriteSurface.reset(SDL_LoadBMP("./assets/pacman_sprites.bmp"));
    m_spriteTexture = SDL_CreateTextureFromSurface(m_windowRenderer.get(),
                                                   m_spriteSurface.get());


}

Game::~Game()
{
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
    if (keys[SDL_SCANCODE_LEFT]) {
        m_pacMan.move(Direction::LEFT);
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        m_pacMan.move(Direction::RIGHT);
    }
    if (keys[SDL_SCANCODE_UP]) {
        m_pacMan.move(Direction::UP);
    }
    if (keys[SDL_SCANCODE_DOWN]) {
        m_pacMan.move(Direction::DOWN);
    }
    // if(keys[SDL_SCANCODE_SPACE]) { bananaDyingAnimation->start(); }
}

void Game::handleLogic()
{

}

void Game::handleDrawing()
{
    SDL_RenderClear(m_windowRenderer.get());

    m_board.draw(m_windowRenderer.get(), m_spriteTexture);

    // Draw entities
    m_pacMan.draw(m_windowRenderer.get(), m_spriteTexture);
    m_blinky.draw(m_windowRenderer.get(), m_spriteTexture);

    SDL_RenderPresent(m_windowRenderer.get());
    SDL_UpdateWindowSurface(m_window.get());
}
