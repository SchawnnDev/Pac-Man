#include <iostream>

#include "game.h"

using namespace pacman;

Game::Game()
        : m_ticks{0},
          m_level{1},
          m_players{1},
          m_currentPlayer{-1},
          m_credit{0},
          m_highScore{0},
          m_scores{shared_value{0}, shared_value{0}},
          m_state{GameState::LoadingScreen},
          m_levelState{LevelState::PlayerDisplay},
          m_spriteHandler{"./assets/pacman.sprites"},
          m_board{"./assets/board.xml", m_spriteHandler.boardResources()},
          m_pacman{m_board, m_spriteHandler.pacmanAnimations()},
          m_blinky{m_board, m_pacman, m_spriteHandler.blinkyAnimations()},
          m_clyde{m_board, m_pacman, m_spriteHandler.clydeAnimations()},
          m_pinky{m_board, m_pacman, m_spriteHandler.pinkyAnimations()},
          m_inky{m_board, m_pacman, m_blinky, m_spriteHandler.inkyAnimations()},
          m_loadingScreen{m_spriteHandler.loadingScreenResources(), m_spriteHandler.textResources(), m_credit},
          m_headerScreen{m_spriteHandler.textResources(), m_highScore, m_currentPlayer, m_scores},
          m_footerScreen{m_spriteHandler.textResources(), m_credit, m_state, m_level, {}, m_spriteHandler.footerResources()},
          m_gameScreen{m_spriteHandler.textResources(), m_levelState}
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

    SDL_SetColorKey(m_spriteSurface.get(), true, SDL_MapRGB(m_spriteSurface->format, 0, 0, 0));

}

Game::~Game()
{
    SDL_Quit();
}

void Game::start() noexcept
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
    m_headerScreen.activated() = true;
    m_gameScreen.activated() = false;

    // Main loop
    while (m_state != GameState::End)
    {
        clock.begin_frame();

        handleEvents();
        handleKeys();
        handleLogic();
        handleTicks();
        handleDrawing();

        m_ticks++;

        clock.end_frame();
        const auto ms_per_frame = (1000.0 / FRAMERATE);
        auto wait_ms = (int)(ms_per_frame - std::min(clock.last_delta(), ms_per_frame));
        SDL_Delay(wait_ms);
    }
}

void Game::end() noexcept
{
    m_state = GameState::End;
}

void Game::handleEvents() noexcept
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

void Game::handleKeys() noexcept
{
    int nbk;
    const Uint8 *keys = SDL_GetKeyboardState(&nbk);
    if (keys[SDL_SCANCODE_ESCAPE])
        m_state = GameState::End;

    if(m_state != GameState::Playing)
        return;

    // Check level states
    if (m_levelState != LevelState::Scatter && m_levelState != LevelState::Chase)
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

void Game::handleLogic() noexcept
{

    if(m_state == GameState::Playing)
    {
        if(m_levelState == LevelState::PlayerDisplay && m_ticks == 180)
        {
            m_levelState = LevelState::Ready;
            m_gameScreen.updateState();

            // Activate all entities but freeze them
            m_pacman.activated() = true;
            m_blinky.activated() = true;
            m_pinky.activated() = true;
            m_inky.activated() = true;
            m_clyde.activated() = true;

            m_pacman.freeze();
            m_blinky.freeze();
            m_pinky.freeze();
            m_inky.freeze();
            m_clyde.freeze();
        }

        if(m_levelState == LevelState::Ready && m_ticks == 360)
        {
            m_levelState = LevelState::Scatter;
            m_gameScreen.updateState();

            // Unfreeze all entities
            m_pacman.unfreeze();
            m_blinky.unfreeze();
            m_pinky.unfreeze();
            m_inky.unfreeze();
            m_clyde.unfreeze();

            m_blinky.startScatterMode();
            m_clyde.startHomeMode();
            m_pinky.startHomeMode();
            m_inky.startHomeMode();
        }

        if(m_levelState == LevelState::Scatter)
        {
            if ( m_ticks == 360*2) {
                m_pinky.startScatterMode();
            } else if(m_ticks == 360*2+60) {
                m_clyde.startScatterMode();
            } else if(m_ticks == 360*2+120) {
                m_inky.startScatterMode();
            }
        }

    }

}

void Game::handleTicks() noexcept {
    m_headerScreen.tick();
    m_footerScreen.tick();
    m_loadingScreen.tick();
    m_gameScreen.tick();
    m_pacman.tick();
    m_blinky.tick();
    m_clyde.tick();
    m_pinky.tick();
    m_inky.tick();
}

void Game::handleDrawing() noexcept
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
    m_headerScreen.draw(m_windowRenderer.get(), m_spriteTexture);
    m_loadingScreen.draw(m_windowRenderer.get(), m_spriteTexture);
    m_footerScreen.draw(m_windowRenderer.get(), m_spriteTexture);
    m_gameScreen.draw(m_windowRenderer.get(), m_spriteTexture);

    SDL_SetRenderDrawColor(m_windowRenderer.get(), 0, 0, 0, 255);

    SDL_RenderPresent(m_windowRenderer.get());
    SDL_UpdateWindowSurface(m_window.get());
}

void Game::handleSpecialKeys(const SDL_Event &event) noexcept
{
    if(m_state == GameState::LoadingScreen)
    {
        if(event.key.keysym.sym == SDLK_c && event.key.repeat == 0)
        {
            updateCredits(credit() + 1);
            return;
        }

        if(m_credit > 0)
        {
            if(event.key.keysym.sym == SDLK_1 && event.key.repeat == 0)
            {
                startPlaying(1);
                return;
            }
        }

    }

    if(m_state == GameState::Playing) {
        if(event.key.keysym.sym == SDLK_b && event.key.repeat == 0)
        {
            updateHighScore(m_highScore + 10);
            return;
        }

    }
}

void Game::startPlaying(int p_players) noexcept
{
    m_players = p_players;
    m_state = GameState::Playing;
    m_footerScreen.updateState();
    m_loadingScreen.activated() = false;
    m_gameScreen.activated() = true;
    m_board.activated() = true;
    startLevel();
}

void Game::updateCredits(int p_credits) noexcept {
    m_credit = p_credits;
    m_loadingScreen.updateCredit();
    m_footerScreen.updateCredit();
}

void Game::updateHighScore(int p_highScore) noexcept
{
    m_highScore = p_highScore;
    m_headerScreen.updateHighScore();
}

void Game::startLevel() noexcept
{
    if(m_state != GameState::Playing) return;

    m_currentPlayer = m_players > 1 && m_currentPlayer == 0 ? 1 : 0;
    m_levelState = LevelState::PlayerDisplay;
    m_gameScreen.updateState();
    m_pacman.reset();
    m_blinky.reset();
    m_pinky.reset();
    m_inky.reset();
    m_clyde.reset();
    m_ticks = 0;
}

void Game::endLevel() noexcept
{
    m_levelState = LevelState::End;
    m_gameScreen.updateState();
    m_pacman.activated() = false;
    m_blinky.activated() = false;
    m_pinky.activated() = false;
    m_inky.activated() = false;
    m_clyde.activated() = false;
}

void Game::startScatter() noexcept
{
    m_blinky.startScatterMode();
    m_pinky.startScatterMode();
    m_inky.startScatterMode();
    m_clyde.startScatterMode();
}

void Game::startChase() noexcept
{
    m_blinky.startChaseMode();
    m_pinky.startChaseMode();
    m_inky.startChaseMode();
    m_clyde.startChaseMode();
}
