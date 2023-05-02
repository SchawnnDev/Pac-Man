#include <iostream>

#include "game/game.h"
#include "SDL_mixer.h"

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
          m_globalDotsCounter{0},
          m_currentEatSound{false},
          m_state{GameState::LoadingScreen},
          m_levelState{LevelState::PlayerDisplay},
          m_gameCycle{},
          m_audioHandler{},
          m_spriteHandler{ASSETS_SPRITES_PATH},
          m_board{ASSETS_BOARD_PATH, m_currentPlayer, m_spriteHandler.boardResources()},
          m_pacman{m_board, m_spriteHandler.pacmanAnimations()},
          m_blinky{m_board, m_pacman, m_spriteHandler.blinkyAnimations()},
          m_clyde{m_board, m_pacman, m_spriteHandler.clydeAnimations()},
          m_pinky{m_board, m_pacman, m_spriteHandler.pinkyAnimations()},
          m_inky{m_board, m_pacman, m_spriteHandler.inkyAnimations()},
          m_fruit{m_board, m_spriteHandler.fruitResources()},
          m_loadingScreen{m_spriteHandler.loadingScreenResources(), m_spriteHandler.textResources(), m_credit},
          m_headerScreen{m_spriteHandler.textResources(), m_highScore, m_playerCount, m_currentPlayer},
          m_footerScreen{m_spriteHandler.textResources(), m_credit, m_state, m_currentPlayer,
                         m_spriteHandler.footerScreenResources()},
          m_gameScreen{m_spriteHandler.textResources(), m_levelState, m_state, m_currentPlayer}
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Echec de l'initialisation de la SDL " << SDL_GetError()
                  << std::endl;
        throw;
    }

    if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, AUDIO_CHANNELS, AUDIO_CHUNK_SIZE) < 0)
    {
        std::cerr << "Erreur initialisation SDL_mixer : %s" << Mix_GetError()
                  << std::endl;
        throw;
    }

    Mix_AllocateChannels(AUDIO_CHANNELS);

    m_window.reset(SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE_WIDTH,
                                    WINDOW_SIZE_HEIGHT, SDL_WINDOW_SHOWN));
    m_windowRenderer.reset(SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED));
    SDL_SetRenderDrawBlendMode(m_windowRenderer.get(), SDL_BLENDMODE_BLEND);

    m_spriteSurface.reset(SDL_LoadBMP(ASSETS_SPRITE_PATH));

    SDL_SetColorKey(m_spriteSurface.get(), SDL_TRUE, SDL_MapRGB(m_spriteSurface->format, 0, 0, 0));

    m_spriteTexture.reset(SDL_CreateTextureFromSurface(m_windowRenderer.get(), m_spriteSurface.get()));

    SDL_SetTextureBlendMode(m_spriteTexture.get(), SDL_BLENDMODE_BLEND);

    // Set SDL_mixer min volume
    for (int i = 0; i < AUDIO_CHANNELS; ++i)
    {
        Mix_Volume(i, MIX_MAX_VOLUME * .75);
    }

}

Game::~Game()
{
    Mix_CloseAudio();
    SDL_Quit();
}

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
    m_headerScreen.activated() = true;
    m_gameScreen.activated() = false;

    // Main loop
    while (m_state != GameState::End)
    {
        clock.begin_frame();

        handleEvents();
        handleKeys();
        handleLogic();
        handleAudio();
        handleTicks();
        handleDrawing();

        m_ticks++;

        clock.end_frame();
        const auto ms_per_frame = (1000.0 / FRAMERATE);
        auto wait_ms = (int) (ms_per_frame - std::min(clock.last_delta(), ms_per_frame));
        SDL_Delay(wait_ms);
    }
}

void Game::end()
{
    m_state = GameState::End;
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

    if (m_state != GameState::Playing)
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

void Game::handleLogic()
{

    if (m_state == GameState::GameOver)
    {
        // handle reset
        if (m_freezeTimeout != -1 && m_freezeTimeout < m_ticks)
        {
            // More than 1 player: maybe other player can continue to play
            if (m_playerCount > 1)
            {
                if (m_players[m_currentPlayer->id() == 1 ? 1 : 0]->lives() > 0)
                {
                    m_board.reset();
                    startLevel(true);
                } else
                {
                    // en
                    endPlaying();
                }

            } else
            {
                endPlaying();
            }

            m_freezeTimeout = -1;
        }

        return;
    }

    if (m_state != GameState::Playing)
        return;

    if (m_levelState == LevelState::PlayerDisplay && m_ticks == TIMEOUT_PRE_START_GAME)
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
    } else if (m_levelState == LevelState::Ready && m_ticks == TIMEOUT_START_GAME)
    {
        m_levelState = LevelState::Scatter;
        m_gameScreen.updateState(false);

        // Unfreeze all entities
        unfreezeEntities();

        m_blinky.startScatterMode();
        m_clyde.startHomeMode(m_currentPlayer->level(), m_currentPlayer->deadCurrentLevel());
        m_pinky.startHomeMode(m_currentPlayer->level(), m_currentPlayer->deadCurrentLevel());
        m_inky.startHomeMode(m_currentPlayer->level(), m_currentPlayer->deadCurrentLevel());

        m_audioHandler.resumeAudio(2);

        m_gameCycle.startTicks() = m_ticks;
    } else if (isLevelPlaying(m_levelState))
    {
        handleCycleChange();
        handleGhostHomePriority();

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
            if (m_freezeTimeout != -1)
            {

                if (m_freezeTimeout < m_ticks)
                {
                    m_blinky.activated() = false;
                    m_pinky.activated() = false;
                    m_clyde.activated() = false;
                    m_inky.activated() = false;
                    m_pacman.die();
                    m_audioHandler.playAudio(Audio::Death);

                    if (m_currentPlayer->lives() == 0)
                    {
                        m_state = GameState::GameOver;

                        auto displayGameOverPlay = false;

                        if (m_playerCount > 1)
                        {
                            if (m_players[m_currentPlayer->id() == 1 ? 1 : 0]->lives() > 0)
                            {
                                displayGameOverPlay = true;
                            }
                        }

                        m_gameScreen.updateState(displayGameOverPlay);
                        m_freezeTimeout = m_ticks + 3 * FRAMERATE;
                    } else
                    {
                        m_freezeTimeout = -1;
                    }
                }
            } else if (m_pacman.currentAnimation() && !m_pacman.currentAnimation()->activated())
            {
                startLevel(true);
            }
        }
    } else if (m_levelState == LevelState::End)
    {
        if (m_freezeTimeout != -1)
        {
            if (m_freezeTimeout < m_ticks)
            {
                m_blinky.activated() = false;
                m_pinky.activated() = false;
                m_clyde.activated() = false;
                m_inky.activated() = false;
                m_pacman.currentAnimation()->reset();
                m_board.startLevelEndAnimation();
                m_freezeTimeout = -1;
            }
        } else if (m_board.currentAnimation() && !m_board.currentAnimation()->activated())
        {
            // New Level
            m_currentPlayer->nextLevel();
            startLevel(false);
        }
    }

}

void Game::handleAudio()
{
}

void Game::handleTicks()
{
    m_headerScreen.tick();
    m_footerScreen.tick();
    m_loadingScreen.tick();
    m_gameScreen.tick();
    m_pacman.tick();
    m_blinky.tick();
    m_clyde.tick();
    m_pinky.tick();
    m_inky.blinkyPosition() = m_blinky.position();
    m_inky.tick();
    m_fruit.tick();
}

void Game::handleDrawing()
{
    SDL_RenderClear(m_windowRenderer.get());
    SDL_SetRenderDrawColor(m_windowRenderer.get(), 0, 0, 0, 255);

    m_board.draw(m_windowRenderer.get(), m_spriteTexture.get());

    // Draw entities
    m_pacman.draw(m_windowRenderer.get(), m_spriteTexture.get());
    m_blinky.draw(m_windowRenderer.get(), m_spriteTexture.get());
    m_clyde.draw(m_windowRenderer.get(), m_spriteTexture.get());
    m_pinky.draw(m_windowRenderer.get(), m_spriteTexture.get());
    m_inky.draw(m_windowRenderer.get(), m_spriteTexture.get());
    m_fruit.draw(m_windowRenderer.get(), m_spriteTexture.get());

    // Draw screens
    m_headerScreen.draw(m_windowRenderer.get(), m_spriteTexture.get());
    m_loadingScreen.draw(m_windowRenderer.get(), m_spriteTexture.get());
    m_footerScreen.draw(m_windowRenderer.get(), m_spriteTexture.get());
    m_gameScreen.draw(m_windowRenderer.get(), m_spriteTexture.get());

    SDL_SetRenderDrawColor(m_windowRenderer.get(), 0, 0, 0, 255);

    SDL_RenderPresent(m_windowRenderer.get());
    SDL_UpdateWindowSurface(m_window.get());
}

void Game::handleSpecialKeys(const SDL_Event &event)
{
    if (m_state != GameState::LoadingScreen || event.key.repeat != 0)
        return;

    if (event.key.keysym.sym == SDLK_c)
    {
        updateCredits(m_credit + 1);
        m_audioHandler.playAudio(Audio::Credit, 0);
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
            if (m_credit > 1)
            {
                startPlaying(2);
            }
            break;
        default:
            break;
    }

}

void Game::startPlaying(int p_players)
{
    m_playerCount = p_players;
    m_headerScreen.updatePlayerCount();
    m_state = GameState::Playing;
    m_players[0]->id() = 1; // Reset player id to 1
    updateCredits(m_credit - (p_players == 1 ? 1 : 2));
    std::for_each(m_players.begin(), m_players.end(), [this](PlayerPtr &m_p) {
        m_p->reset();
        m_headerScreen.updateScore(m_p->id());
    });
    m_gameScreen.updateCurrentPlayer();
    m_footerScreen.updateState();
    m_loadingScreen.activated() = false;
    m_gameScreen.activated() = true;
    m_board.activated() = true;
    m_board.reset();

    // remove 1 life to each player (first life is played)
    m_players[0]->lives()--;
    m_players[1]->lives()--;

    // play start audio
    m_audioHandler.playAudio(Audio::GameStart, 0);

    startLevel(false);
}

void Game::endPlaying()
{
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
    m_audioHandler.pauseAll();
}

void Game::updateCredits(int p_credits)
{
    m_credit = p_credits;
    m_loadingScreen.updateCredit();
    m_footerScreen.updateCredit();
}

void Game::updateHighScore(int p_highScore)
{
    m_highScore = p_highScore;
    m_headerScreen.updateHighScore();
}

void Game::startLevel(bool p_died)
{
    if (m_state == GameState::GameOver)
    {
        m_state = GameState::Playing;
        m_gameScreen.updateState(false);
    } else if (m_state != GameState::Playing) return;

    if (p_died)
    {
        m_currentPlayer->lives()--;

        auto &nextPlayer = m_players[m_playerCount == 2 && m_currentPlayer->id() == 1 ? 1 : 0];
        // Avoid to switch players if other player has no lifes remaining
        if (m_playerCount == 2 && nextPlayer->lives() != 0)
        {
            m_currentPlayer = nextPlayer;
            m_gameScreen.updateCurrentPlayer();
        }
    }

    m_footerScreen.updateLevels();
    m_levelState = LevelState::PlayerDisplay;
    m_gameScreen.updateState(false);
    m_pacman.activated() = false;
    m_pacman.reset();
    m_fruit.reset();
    m_fruit.unfreeze();
    m_inky.reset();
    m_blinky.reset();
    m_pinky.reset();
    m_clyde.reset();
    m_board.load();
    m_gameCycle.reset();
    m_audioHandler.playAudio(m_audioHandler.getSiren(1 + m_currentPlayer->eatenPowerPelletsCurrentLevel()), 2, -1, -1);
    m_audioHandler.pauseAudio(2);
    m_currentEatSound = false;
    m_globalDotsCounter = 0;
    m_ticks = 0;
    m_freezeTimeout = -1;
}

void Game::endLevel()
{
    m_levelState = LevelState::End;
    m_gameScreen.updateState(false);
    m_pacman.activated() = false;
    m_blinky.activated() = false;
    m_pinky.activated() = false;
    m_inky.activated() = false;
    m_clyde.activated() = false;
}

void Game::startScatter()
{
    m_blinky.startScatterMode();
    m_pinky.startScatterMode();
    m_inky.startScatterMode();
    m_clyde.startScatterMode();
}

void Game::startChase()
{
    m_blinky.startChaseMode();
    m_pinky.startChaseMode();
    m_inky.startChaseMode();
    m_clyde.startChaseMode();
}

void Game::startFrightened()
{
    auto const level = m_currentPlayer->level();
    m_blinky.startFrightenedMode(level);
    m_pinky.startFrightenedMode(level);
    m_inky.startFrightenedMode(level);
    m_clyde.startFrightenedMode(level);

    // Handle timeouts
    if (level <= GHOST_FRIGHTENED_TIMEOUTS_COUNT)
    {
        auto const ticks = GHOST_FRIGHTENED_TIMEOUTS[level - 1] / FRAMERATE * 1000;
        m_audioHandler.playAudio(Audio::PowerPellet, 1, ticks, -1);
    }

}


void Game::checkCollisions()
{
    if (m_pacman.freezed() || !m_pacman.activated()) return;

    auto const pacmanPosition = m_pacman.position();
    // Check points eating
    if (Board::isCase(pacmanPosition))
    {
        try
        {
            auto &fCase = m_board.getBoardCaseAtPixels(pacmanPosition);

            if (fCase.activated())
            {
                auto isPoint = fCase.type() == BoardCaseType::PointPath;
                auto isBonus = fCase.type() == BoardCaseType::Bonus;
                auto dotsEaten = m_currentPlayer->map().size();

                if (isPoint || isBonus)
                {
                    fCase.activated() = false;
                    dotsEaten++;
                    if(m_currentPlayer->deadCurrentLevel()) m_globalDotsCounter++;
                    updateScore(isPoint ? 10 : 50);
                    m_currentPlayer->map()[Board::getGridIndex(fCase.position())] = true;

                    // handle home dot counter
                    m_pinky.pacmanDotEaten();
                    m_inky.pacmanDotEaten();
                    m_clyde.pacmanDotEaten();

                    if (isBonus)
                    {
                        startFrightened();
                        m_eatenFrightenedGhosts = 0;
                        m_currentPlayer->eatenPowerPelletsCurrentLevel()++;
                        m_audioHandler.playAudio(
                                m_audioHandler.getSiren(1 + m_currentPlayer->eatenPowerPelletsCurrentLevel()), 2, -1,
                                -1);
                        m_audioHandler.pauseAudio(2);
                    } else
                    {
                        m_audioHandler.playAudio(m_currentEatSound ? Audio::Munch1 : Audio::Munch2);
                        m_currentEatSound = !m_currentEatSound;
                    }

                    // Check win
                    if (dotsEaten >= DOTS_TO_EAT)
                    {
                        freezeEntities();
                        m_pacman.currentAnimation()->reset();
                        m_audioHandler.pauseAudio(2);
                        m_freezeTimeout = m_ticks + FRAMERATE * 2;
                        m_levelState = LevelState::End;
                        return;
                    }
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

        } catch (...)
        {
            // Should not happen
        }

        // Handle fruit eating
        if (m_fruit.activated() && m_fruit.position() == m_pacman.position())
        {
            auto const points = getFruitValueByLevel(m_currentPlayer->level());
            m_fruit.eat(points);
            updateScore(points);
            m_audioHandler.playAudio(Audio::EatFruit);
        }

    }

    if (m_pacman.checkCollision(m_blinky) && m_blinky.ghostMode() != GhostMode::Eaten)
    {
        if (m_blinky.frightened())
        {
            m_blinky.startEatenMode();
            m_audioHandler.playAudio(Audio::EatGhost);
            freezeDisplayScore(m_blinky, calculateFrightenedGhostScore());
        } else
        {
            performPacmanDying();
        }
        return;
    }

    if (m_pacman.checkCollision(m_pinky) && m_pinky.ghostMode() != GhostMode::Eaten)
    {
        if (m_pinky.frightened())
        {
            m_pinky.startEatenMode();
            m_audioHandler.playAudio(Audio::EatGhost);
            freezeDisplayScore(m_pinky, calculateFrightenedGhostScore());
        } else
        {
            performPacmanDying();
        }
        return;
    }

    if (m_pacman.checkCollision(m_clyde) && m_clyde.ghostMode() != GhostMode::Eaten)
    {
        if (m_clyde.frightened())
        {
            m_clyde.startEatenMode();
            m_audioHandler.playAudio(Audio::EatGhost);
            freezeDisplayScore(m_clyde, calculateFrightenedGhostScore());
        } else
        {
            performPacmanDying();
        }
        return;
    }


    if (m_pacman.checkCollision(m_inky) && m_inky.ghostMode() != GhostMode::Eaten)
    {
        if (m_inky.frightened())
        {
            m_inky.startEatenMode();
            m_audioHandler.playAudio(Audio::EatGhost);
            freezeDisplayScore(m_inky, calculateFrightenedGhostScore());
        } else
        {
            performPacmanDying();
        }
        return;
    }

}

void Game::updateScore(int p_scoreToAdd)
{
    auto &score = m_currentPlayer->score();
    score += p_scoreToAdd;
    m_headerScreen.updateScore(m_currentPlayer->id());

    if (score > 10000 && !m_currentPlayer->extraLifeGiven())
    {
        m_currentPlayer->giveExtraLife();
        m_footerScreen.updateLives();
        // TODO: sound
    }

    if (score > *m_highScore)
    {
        updateHighScore(score);
    }
}

void Game::freezeDisplayScore(Entity &p_which, int p_score)
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

void Game::performPacmanDying()
{
    m_pacman.freeze();
    m_blinky.freezeMovement();
    m_pinky.freezeMovement();
    m_clyde.freezeMovement();
    m_inky.freezeMovement();
    m_fruit.freeze();
    m_pacman.state() = PacmanState::DYING;
    m_currentPlayer->deadCurrentLevel() = true;
    m_audioHandler.pauseAudio(2);
    m_freezeTimeout = m_ticks + FRAMERATE;
}

int Game::calculateFrightenedGhostScore()
{
    m_eatenFrightenedGhosts++;
    return static_cast<int>(std::pow(2, m_eatenFrightenedGhosts) * 100);
}

void Game::freezeEntities()
{
    m_pacman.freeze();
    m_blinky.freeze();
    m_pinky.freeze();
    m_clyde.freeze();
    m_inky.freeze();
}

void Game::unfreezeEntities()
{
    m_pacman.unfreeze();
    m_blinky.unfreeze();
    m_pinky.unfreeze();
    m_clyde.unfreeze();
    m_inky.unfreeze();
}

void Game::handleCycleChange()
{
    // Check cycle change
    if (m_ticks <= m_gameCycle.getCycleDuration(m_currentPlayer->level())) return;
    m_gameCycle.changeGameState();
    m_levelState = m_gameCycle.getGameState();
    m_gameCycle.startTicks() = m_ticks;

    auto const newMode = m_levelState == LevelState::Scatter ? GhostMode::Scatter : GhostMode::Chase;

    m_blinky.handleCycleChange(newMode);
    m_pinky.handleCycleChange(newMode);
    m_inky.handleCycleChange(newMode);
    m_clyde.handleCycleChange(newMode);
}

void Game::handleGhostHomePriority()
{

    if(m_currentPlayer->deadCurrentLevel()) {
        // handle global ghost counter pinky -> inky -> clyde
        m_pinky.homeExitPriority() = false;
        m_inky.homeExitPriority() = false;
        m_clyde.homeExitPriority() = false;

        if (m_pinky.ghostMode() == GhostMode::Home)
        {
            if(m_globalDotsCounter == 7) {
                m_pinky.startLastGhostMode();
            }
        }
        else if (m_inky.ghostMode() == GhostMode::Home)
        {
            if(m_globalDotsCounter == 17) {
                m_inky.startLastGhostMode();
            }
        }
        else if (m_clyde.ghostMode() == GhostMode::Home && m_globalDotsCounter == 32)
        {
            if(m_globalDotsCounter == 32) {
                m_clyde.startLastGhostMode();
            }
        }

        return;
    }

    if (m_pinky.ghostMode() == GhostMode::Home ||
        (m_pinky.ghostMode() != GhostMode::Eaten && m_pinky.currentCase() &&
         m_pinky.currentCase()->type() == BoardCaseType::GhostHome ||
         m_pinky.currentCase()->type() == BoardCaseType::GhostHomeDoor))
    {
        m_pinky.homeExitPriority() = true;
        m_inky.homeExitPriority() = false;
        m_clyde.homeExitPriority() = false;
        return;
    }

    if (m_inky.ghostMode() == GhostMode::Home ||
        (m_inky.ghostMode() != GhostMode::Eaten && m_inky.currentCase() &&
         m_inky.currentCase()->type() == BoardCaseType::GhostHome ||
         m_inky.currentCase()->type() == BoardCaseType::GhostHomeDoor))
    {
        m_pinky.homeExitPriority() = false;
        m_inky.homeExitPriority() = true;
        m_clyde.homeExitPriority() = false;
        return;
    }

    if (m_clyde.ghostMode() == GhostMode::Home ||
        (m_clyde.ghostMode() != GhostMode::Eaten && m_clyde.currentCase() &&
         m_clyde.currentCase()->type() == BoardCaseType::GhostHome ||
         m_clyde.currentCase()->type() == BoardCaseType::GhostHomeDoor))
    {
        m_pinky.homeExitPriority() = false;
        m_inky.homeExitPriority() = false;
        m_clyde.homeExitPriority() = true;
        return;
    }
}
