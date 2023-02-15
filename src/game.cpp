#include "../include/game.h"

void Game::start()
{

    if (m_state != GameState::WaitingStart)
        return;

    while (m_state != GameState::End)
    {
        handleEvents();
        handleKeys();

        SDL_Delay(1000 / FRAMERATE);
    }

}

void Game::end()
{
    m_state = GameState::End;
}


std::vector<std::shared_ptr<Entity>>
Game::getEntitiesByType(EntityType p_entityType)
{
    std::vector<std::shared_ptr<Entity>> entities = {};

    for (const std::shared_ptr<Entity> &entity: m_entities)
    {
        if (entity->entityType() == p_entityType)
            entities.push_back(entity);
    }

    return entities;
}

Game::Game()
{
    m_window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE_WIDTH,
                                WINDOW_SIZE_HEIGHT, SDL_WINDOW_SHOWN);
    m_windowRenderer = SDL_CreateRenderer(m_window, -1,
                                          SDL_RENDERER_ACCELERATED);
}

Game::~Game()
{
    SDL_FreeSurface(m_spriteSurface);
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_windowRenderer);
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
