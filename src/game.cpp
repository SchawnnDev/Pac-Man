#include <iostream>

#include "game.h"

using namespace pacman;

void Game::start()
{
    if (m_state != GameState::LoadingScreen)
        return;

    // Init
    Clock clock{};
    m_board.activated() = false;
    m_pacman.activated() = false;
    m_blinky.activated() = false;
    m_pinky.activated() = false;
    m_inky.activated() = false;
    m_clyde.activated() = false;

    // Main loop
    while (m_state != GameState::End)
    {
        clock.begin_frame();

        handleEvents();
        handleKeys();
        handleLogic();
        handleDrawing();

        clock.end_frame();

        const auto ms_per_frame = (1000.0 / FRAMERATE);
        auto wait_ms = (int)(ms_per_frame - std::min(clock.last_delta(), ms_per_frame));
        SDL_Delay(wait_ms);
    }
}

void Game::end()
{
    m_state = GameState::End;
}

Game::Game()
        : m_spriteHandler{"./assets/pacman.sprites"},
          m_board{"./assets/board.xml", m_spriteHandler.boardResources()},
          m_pacman{m_board, m_spriteHandler.pacmanAnimations()},
          m_blinky{m_board, m_pacman, m_spriteHandler.blinkyAnimations()},
          m_clyde{m_board, m_pacman, m_spriteHandler.clydeAnimations()},
          m_pinky{m_board, m_pacman, m_spriteHandler.pinkyAnimations()},
          m_inky{m_board, m_pacman, m_blinky, m_spriteHandler.inkyAnimations()},
          m_credits{0},
          m_loadingScreen{m_spriteHandler.loadingScreenResources(), m_spriteHandler.textResources(), m_credits},
          m_state{GameState::LoadingScreen},
          m_level{1},
          m_players{1},
          m_currentPlayer{0}
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Echec de l'initialisation de la SDL " << SDL_GetError()
                  << std::endl;
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

    SDL_SetColorKey(m_spriteSurface.get(), true,  SDL_MapRGB(m_spriteSurface->format, 0, 0, 0));

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
            case SDL_KEYDOWN:
                handleSpecialKeys(event);
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

    if(m_state != GameState::Playing)
        return;

    if (keys[SDL_SCANCODE_LEFT])
    {
        m_pacman.move(Direction::LEFT);
    }
    if (keys[SDL_SCANCODE_RIGHT])
    {
        m_pacman.move(Direction::RIGHT);
    }
    if (keys[SDL_SCANCODE_UP])
    {
        m_pacman.move(Direction::UP);
    }
    if (keys[SDL_SCANCODE_DOWN])
    {
        m_pacman.move(Direction::DOWN);
    }
}

void Game::handleLogic()
{

    if(m_state == GameState::LoadingScreen)
    {
        // be sure it is always activated
        m_loadingScreen.activated() = true;
        m_loadingScreen.tick();
        return;
    }

    m_pacman.tick();

    // Scatter test
    // std::foreach
/*    m_blinky.startScatterMode();
    m_clyde.startScatterMode();
    m_pinky.startScatterMode();
    m_inky.startScatterMode();*/

    // Chase test
    m_blinky.startChaseMode();
    m_clyde.startChaseMode();
    m_pinky.startChaseMode();
    m_inky.startChaseMode();

    m_blinky.handleChaseTarget();
    m_clyde.handleChaseTarget();
    m_pinky.handleChaseTarget();
    m_inky.handleChaseTarget();

    m_blinky.tick();
    m_clyde.tick();
    m_pinky.tick();
    m_inky.tick();
}

void Game::handleDrawing()
{
    SDL_RenderClear(m_windowRenderer.get());
    SDL_SetRenderDrawColor(m_windowRenderer.get(), 0,0,0,255);

    m_board.draw(m_windowRenderer.get(), m_spriteTexture);

    // Draw entities
    m_pacman.draw(m_windowRenderer.get(), m_spriteTexture);
    m_blinky.draw(m_windowRenderer.get(), m_spriteTexture);
    m_clyde.draw(m_windowRenderer.get(), m_spriteTexture);
    m_pinky.draw(m_windowRenderer.get(), m_spriteTexture);
    m_inky.draw(m_windowRenderer.get(), m_spriteTexture);

    // Draw screens
    m_loadingScreen.draw(m_windowRenderer.get(), m_spriteTexture);

    SDL_SetRenderDrawColor(m_windowRenderer.get(), 0, 0, 0, 255);

    SDL_RenderPresent(m_windowRenderer.get());
    SDL_UpdateWindowSurface(m_window.get());
}

void Game::updateCredits(int p_credits) {
    m_credits = p_credits;
    m_loadingScreen.credit()->text() = "credit  " + std::to_string(p_credits);
}

void Game::handleSpecialKeys(const SDL_Event &event)
{
    if(m_state == GameState::LoadingScreen)
    {
        if(event.key.keysym.sym == SDLK_c && event.key.repeat == 0)
        {
            updateCredits(credits() + 1);
            return;
        }

        if(m_credits > 0)
        {
            if(event.key.keysym.sym == SDLK_1 && event.key.repeat == 0)
            {
                startPlaying(1);
                return;
            }
        }

    }
}

void Game::startPlaying(int p_players)
{
    m_players = p_players;
    m_state = GameState::Playing;
    m_loadingScreen.activated() = false;
    m_board.activated() = true;
    m_pacman.activated() = true;
    m_blinky.activated() = true;
    m_pinky.activated() = true;
    m_inky.activated() = true;
    m_clyde.activated() = true;
}
