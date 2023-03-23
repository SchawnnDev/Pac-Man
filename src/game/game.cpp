#include <iostream>

#include "game/game.h"

using namespace pacman;

Game::Game()
        : m_ticks{0},
          m_playerCount{1},
          m_players{std::make_shared<Player>(-1), std::make_shared<Player>(2)},
          m_currentPlayer{m_players[0]},
          m_credit{0},
          m_highScore{0},
          m_freezeTimeout{-1},
          m_eatenFrightenedGhosts{0},
          m_state{GameState::LoadingScreen},
          m_levelState{LevelState::PlayerDisplay},
          m_spriteHandler{"./assets/pacman.sprites"},
          m_board{"./assets/board.xml", m_currentPlayer, m_spriteHandler.boardResources()},
          m_pacman{m_board, m_spriteHandler.pacmanAnimations()},
          m_blinky{m_board, m_pacman, m_spriteHandler.blinkyAnimations()},
          m_clyde{m_board, m_pacman, m_spriteHandler.clydeAnimations()},
          m_pinky{m_board, m_pacman, m_spriteHandler.pinkyAnimations()},
          m_inky{m_board, m_pacman, m_blinky, m_spriteHandler.inkyAnimations()},
          m_fruit{m_board, m_spriteHandler.fruitResources()},
          m_loadingScreen{m_spriteHandler.loadingScreenResources(), m_spriteHandler.textResources(), m_credit},
          m_headerScreen{m_spriteHandler.textResources(), m_highScore, m_playerCount, m_currentPlayer},
          m_footerScreen{m_spriteHandler.textResources(), m_credit, m_state, m_currentPlayer, m_spriteHandler.footerScreenResources()},
          m_gameScreen{m_spriteHandler.textResources(), m_levelState, m_state, m_currentPlayer}
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
    SDL_SetRenderDrawBlendMode(m_windowRenderer.get(), SDL_BLENDMODE_BLEND);

    m_spriteSurface.reset(SDL_LoadBMP("./assets/pacman_sprites.bmp"));

    SDL_SetColorKey(m_spriteSurface.get(), SDL_TRUE, SDL_MapRGB(m_spriteSurface->format, 0, 0, 0));
    SDL_SetTextureBlendMode(m_spriteTexture, SDL_BLENDMODE_BLEND);

    m_spriteTexture = SDL_CreateTextureFromSurface(m_windowRenderer.get(),
                                                   m_spriteSurface.get());

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
    if (!isLevelPlaying(m_levelState) || m_pacman.state() != PacmanState::LIVING)
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
            m_gameScreen.updateState(false);

            // Activate all entities but freeze them
            m_pacman.activated() = true;
            m_blinky.activated() = true;
            m_pinky.activated() = true;
            m_inky.activated() = true;
            m_clyde.activated() = true;

            freezeEntities();

            m_footerScreen.updateLives();

        }

        if(m_levelState == LevelState::Ready && m_ticks == 360)
        {
            m_levelState = LevelState::Scatter;
            m_gameScreen.updateState(false);

            // Unfreeze all entities
            unfreezeEntities();

            m_blinky.startScatterMode();
            m_clyde.startHomeMode();
            m_pinky.startHomeMode();
            m_inky.startHomeMode();
        }

        if(m_levelState == LevelState::Scatter)
        {
            if (m_ticks == 360*2) {
                m_pinky.startScatterMode();
            } else if(m_ticks == 360*2+60) {
                m_clyde.startScatterMode();
            } else if(m_ticks == 360*2+120) {
                m_inky.startScatterMode();
            }
        }

        if (isLevelPlaying(m_levelState))
        {
            if (m_pacman.state() == PacmanState::LIVING)
            {
                checkCollisions();

                if (m_freezeTimeout != -1 && m_freezeTimeout < m_ticks)
                {
                    m_pacman.activated() = true;
                    unfreezeEntities();

                    m_freezeTimeout = -1;
                }
            } else if (m_pacman.state() == PacmanState::DYING)
            {
                if (m_freezeTimeout != -1) {

                    if (m_freezeTimeout < m_ticks) {
                        m_blinky.activated() = false;
                        m_pinky.activated() = false;
                        m_clyde.activated() = false;
                        m_inky.activated() = false;
                        m_pacman.die();

                        if (m_currentPlayer->lives() == 0) {
                            m_state = GameState::GameOver;

                            auto displayGameOverPlay = false;

                            if (m_playerCount > 1) {
                                if (m_players[m_currentPlayer->id() == 1 ? 1 : 0]->lives() > 0) {
                                    displayGameOverPlay = true;
                                }
                            }

                            m_gameScreen.updateState(displayGameOverPlay);
                            m_freezeTimeout = m_ticks + 3 * FRAMERATE;
                        } else {
                            m_freezeTimeout = -1;
                        }
                    }
                } else if (m_pacman.currentAnimation() && !m_pacman.currentAnimation()->activated()) {
                    startLevel(true);
                }
            }
        } else if (m_levelState == LevelState::End) {
            if (m_freezeTimeout != -1) {
                if(m_freezeTimeout < m_ticks)
                {
                    m_blinky.activated() = false;
                    m_pinky.activated() = false;
                    m_clyde.activated() = false;
                    m_inky.activated() = false;
                    m_pacman.currentAnimation()->reset();
                    m_board.startLevelEndAnimation();
                    m_freezeTimeout = -1;
                }
            } else if (m_board.currentAnimation() && !m_board.currentAnimation()->activated()) {
                // New Level
                m_currentPlayer->nextLevel();
                startLevel(false);
            }
        }
    }

    if(m_state == GameState::GameOver) {
        // handle reset
        if (m_freezeTimeout != -1 && m_freezeTimeout < m_ticks)
        {
            // More than 1 player: maybe other player can continue to play
            if(m_playerCount > 1)
            {
                if(m_players[m_currentPlayer->id() == 1 ? 1 : 0]->lives() > 0)
                {
                    m_board.reset();
                    startLevel(true);
                } else {
                    // en
                    endPlaying();
                }

            } else {
                endPlaying();
            }

            m_freezeTimeout = -1;
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
    m_fruit.tick();
}

void Game::handleDrawing() noexcept
{
    SDL_RenderClear(m_windowRenderer.get());
    SDL_SetRenderDrawColor(m_windowRenderer.get(), 0, 0, 0, 255);

    m_board.draw(m_windowRenderer.get(), m_spriteTexture);

    // Draw entities
    m_pacman.draw(m_windowRenderer.get(), m_spriteTexture);
    m_blinky.draw(m_windowRenderer.get(), m_spriteTexture);
    m_clyde.draw(m_windowRenderer.get(), m_spriteTexture);
    m_pinky.draw(m_windowRenderer.get(), m_spriteTexture);
    m_inky.draw(m_windowRenderer.get(), m_spriteTexture);
    m_fruit.draw(m_windowRenderer.get(), m_spriteTexture);

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
    if (m_state != GameState::LoadingScreen || event.key.repeat != 0)
        return;

    if(event.key.keysym.sym == SDLK_c)
    {
        updateCredits(credit() + 1);
        return;
    }

    if (m_credit == 0)
        return;

    switch (event.key.keysym.sym)
    {
        case SDLK_1:
            startPlaying(1);
            break;
        case SDLK_2:
            if(m_credit > 1) {
                startPlaying(2);
            }
            break;
        default:
            break;
    }

}

void Game::startPlaying(int p_players) noexcept
{
    m_playerCount = p_players;
    m_headerScreen.updatePlayerCount();
    m_state = GameState::Playing;
    m_players[0]->id() = 1; // Reset player id to 1
    updateCredits(m_credit - (p_players == 1 ? 1 : 2));
    std::for_each(m_players.begin(), m_players.end(), [this](PlayerPtr &m_p) { m_p->reset(); m_headerScreen.updateScore(m_p->id()); });
    m_gameScreen.updateCurrentPlayer();
    m_footerScreen.updateState();
    m_loadingScreen.activated() = false;
    m_gameScreen.activated() = true;
    m_board.activated() = true;
    m_board.reset();

    // remove 1 life to each player (first life is played)
    m_players[0]->lives()--;
    m_players[1]->lives()--;

    startLevel(false);
}

void Game::endPlaying() noexcept {
    m_state = GameState::LoadingScreen;
    m_pacman.activated() = false;
    m_blinky.activated() = false;
    m_inky.activated() = false;
    m_pinky.activated() = false;
    m_clyde.activated() = false;
    m_loadingScreen.activated() = true;
    m_gameScreen.activated() = false;
    m_board.activated() = false;
    m_headerScreen.reset();
    m_currentPlayer = m_players[0];
    m_currentPlayer->id() = -1;
    m_footerScreen.updateState();
    m_gameScreen.updateCurrentPlayer();
}

void Game::updateCredits(int p_credits) noexcept
{
    m_credit = p_credits;
    m_loadingScreen.updateCredit();
    m_footerScreen.updateCredit();
}

void Game::updateHighScore(int p_highScore) noexcept
{
    m_highScore = p_highScore;
    m_headerScreen.updateHighScore();
}

void Game::startLevel(bool p_died) noexcept
{
    if(m_state == GameState::GameOver) {
        m_state = GameState::Playing;
        m_gameScreen.updateState(false);
    } else if (m_state != GameState::Playing) return;

    if(p_died)
    {
        m_currentPlayer->lives()--;

        auto& nextPlayer = m_players[m_playerCount == 2 && m_currentPlayer->id() == 1 ? 1 : 0];
        // Avoid to switch players if other player has no lifes remaining
        if(m_playerCount == 2 && nextPlayer->lives() != 0) {
            m_currentPlayer = nextPlayer;
            m_gameScreen.updateCurrentPlayer();
        }
    }

    m_footerScreen.updateLevels();
    m_levelState = LevelState::PlayerDisplay;
    m_gameScreen.updateState(false);
    m_pacman.activated() = false;
    m_pacman.reset();
    m_blinky.reset();
    m_pinky.reset();
    m_inky.reset();
    m_clyde.reset();
    m_board.load();
    m_ticks = 0;
    m_freezeTimeout = -1;
}

void Game::endLevel() noexcept
{
    m_levelState = LevelState::End;
    m_gameScreen.updateState(false);
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

void Game::startFrightened() noexcept
{
    m_blinky.startFrightenedMode();
    m_pinky.startFrightenedMode();
    m_inky.startFrightenedMode();
    m_clyde.startFrightenedMode();
}


void Game::checkCollisions() noexcept
{
    if(m_pacman.freezed() || !m_pacman.activated()) return;

    auto const pacmanPosition = m_pacman.position();
    // Check points eating
    if(Board::isCase(pacmanPosition))
    {
        try {
            auto& fCase = m_board.getBoardCaseAtPixels(pacmanPosition);

            if(fCase.activated()) {
                fCase.activated() = false;

                if(fCase.type() == BoardCaseType::PointPath) {
                    updateScore(10);
                } else if(fCase.type() == BoardCaseType::Bonus) {
                    updateScore(50);
                    startFrightened();
                    m_eatenFrightenedGhosts = 0;
                }

                m_currentPlayer->map()[Board::getGridIndex(fCase.position())] = true;
                auto const dotsEaten = m_currentPlayer->map().size();

                // Check win
                if(dotsEaten >= DOTS_TO_EAT) {
                    freezeEntities();
                    m_pacman.currentAnimation()->reset();
                    m_freezeTimeout = m_ticks + FRAMERATE * 2;
                    m_levelState = LevelState::End;
                    return;
                }

                // Check fruit
                auto const eatenFruits = m_currentPlayer->eatenFruitsCurrentLevel();
                if ((dotsEaten >= DOTS_TO_EAT_FIRST_FRUIT && eatenFruits == 0) ||
                    (dotsEaten >= DOTS_TO_EAT_SECOND_FRUIT && eatenFruits == 1))
                {
                    m_fruit.display(m_currentPlayer->level());
                    m_currentPlayer->eatenFruitsCurrentLevel()++;
                }

            }

        } catch (...){ }

        // Handle fruit eating
        if(m_fruit.activated() && m_fruit.position() == m_pacman.position()) {
            auto const points = getFruitValueByLevel(m_currentPlayer->level());
            m_fruit.eat(points);
            updateScore(points);
        }

    }

    if (m_pacman.checkCollision(m_blinky) && m_blinky.ghostMode() != GhostMode::Eaten)
    {
        if (m_blinky.frightened())
        {
            m_blinky.startEatenMode();
            freezeDisplayScore(m_blinky, calculateFrightenedGhostScore());
        } else {
            performPacmanDying();
        }
        return;
    }

    if(m_pacman.checkCollision(m_pinky) && m_pinky.ghostMode() != GhostMode::Eaten)
    {
        if(m_pinky.frightened())
        {
            m_pinky.startEatenMode();
            freezeDisplayScore(m_pinky, calculateFrightenedGhostScore());
        } else {
            performPacmanDying();
        }
        return;
    }

    if(m_pacman.checkCollision(m_clyde) && m_clyde.ghostMode() != GhostMode::Eaten)
    {
        if(m_clyde.frightened())
        {
            m_clyde.startEatenMode();
            freezeDisplayScore(m_clyde, calculateFrightenedGhostScore());
        } else {
            performPacmanDying();
        }
        return;
    }


    if(m_pacman.checkCollision(m_inky) && m_inky.ghostMode() != GhostMode::Eaten)
    {
        if(m_inky.frightened())
        {
            m_inky.startEatenMode();
            freezeDisplayScore(m_inky, calculateFrightenedGhostScore());
        } else {
            performPacmanDying();
        }
        return;
    }

}

void Game::updateScore(int p_scoreToAdd) noexcept
{
    auto& score = m_currentPlayer->score();
    score += p_scoreToAdd;
    m_headerScreen.updateScore(m_currentPlayer->id());

    if(score > 10000 && !m_currentPlayer->extraLifeGiven())
    {
        m_currentPlayer->giveExtraLife();
        m_footerScreen.updateLives();
        // TODO: sound
    }

    if(score > *m_highScore)
    {
        updateHighScore(score);
    }
}

void Game::freezeDisplayScore(Entity& p_which, int p_score) noexcept
{
    m_pacman.activated() = false;
    freezeEntities();

    if (auto it = m_spriteHandler.scoreSprites().find(p_score); it != std::end(
            m_spriteHandler.scoreSprites()))
    {
        p_which.currentAnimation() = SpriteAnimation{{it->second}, false, 1, true, true};
    }

    m_freezeTimeout = m_ticks + FRAMERATE;
    updateScore(p_score);
}

void Game::performPacmanDying() noexcept
{
    m_pacman.freeze();
    m_blinky.freezeMovement();
    m_pinky.freezeMovement();
    m_clyde.freezeMovement();
    m_inky.freezeMovement();
    m_pacman.state() = PacmanState::DYING;
    m_freezeTimeout = m_ticks + FRAMERATE;
}

int Game::calculateFrightenedGhostScore() noexcept {
    m_eatenFrightenedGhosts++;
    return static_cast<int>(std::pow(2, m_eatenFrightenedGhosts) * 100);
}

void Game::freezeEntities() noexcept {
    m_pacman.freeze();
    m_blinky.freeze();
    m_pinky.freeze();
    m_clyde.freeze();
    m_inky.freeze();
}

void Game::unfreezeEntities() noexcept {
    m_pacman.unfreeze();
    m_blinky.unfreeze();
    m_pinky.unfreeze();
    m_clyde.unfreeze();
    m_inky.unfreeze();
}
