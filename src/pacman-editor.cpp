#include <SDL.h>

#include <iostream>
#include "../include/sprite-animation.h"
#include "../include/sprite-handler.h"
#include "../include/utils/constants.h"
#include "../include/board/board.h"

SDL_Window *pWindow = nullptr;
SDL_Surface *win_surf = nullptr;
SDL_Surface *plancheSprites = nullptr;

// Sprite du background
SDL_Rect src_bg = {200, 3, 168, 216}; // x,y, w,h (0,0) en haut a gauche

// Background rectangle
SDL_Rect bg = {0, 0, 672, 864}; // ici scale x4

int count;
int actualX = 0, actualY = 0;

SDL_Renderer *m_window_renderer;
SDL_Texture *plancheTexture;

Board *board;

void init() {
    pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 672, 864, SDL_WINDOW_SHOWN);
    win_surf = SDL_GetWindowSurface(pWindow);
    m_window_renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

    plancheSprites = SDL_LoadBMP("./assets/pacman_sprites.bmp");
    count = 0;
    plancheTexture = SDL_CreateTextureFromSurface(m_window_renderer, plancheSprites);

    SpriteHandler::importSprites("./assets/pacman.sprites");

    board = new Board("./assets/board.xml");
}

// fonction qui met à jour la surface de la fenetre "win_surf"

void draw() {
    SDL_RenderClear(m_window_renderer);


    SDL_RenderCopy(m_window_renderer, plancheTexture, &src_bg, &bg); // Copie du sprite grâce au SDL_Renderer
    SDL_SetRenderDrawColor(m_window_renderer, 255, 255, 255, 255);

    for (int i = 0; i < 27; ++i) {
        for (int j = 0; j < 21; ++j) {
            if (i == actualY && j == actualX) {
                SDL_SetRenderDrawColor(m_window_renderer, 127, 0, 255, 255);
                SDL_Rect sdlRect = {j * (672 / BOARD_SIZE_X), i * (864 / BOARD_SIZE_Y), 672 / BOARD_SIZE_X,
                                    864 / BOARD_SIZE_Y};
                SDL_RenderFillRect(m_window_renderer, &sdlRect);
                continue;
            }

            switch (board->getCase(j, i).type()) {
                case BoardCaseType::Nothing:
                    SDL_SetRenderDrawColor(m_window_renderer, 255, 255, 255, 255);
                    break;
                case BoardCaseType::PointPath:
                    SDL_SetRenderDrawColor(m_window_renderer, 0, 0, 255, 255);
                    break;
                case BoardCaseType::BasicPath:
                    SDL_SetRenderDrawColor(m_window_renderer, 255, 255, 255, 255);
                    break;
                case BoardCaseType::Bonus:
                    SDL_SetRenderDrawColor(m_window_renderer, 200, 100, 2, 255);
                    break;
                case BoardCaseType::Wall:
                    SDL_SetRenderDrawColor(m_window_renderer, 255, 0, 0, 255);
                    break;
                case BoardCaseType::GhostHome:
                    SDL_SetRenderDrawColor(m_window_renderer, 23, 255, 23, 255);
                    break;
                case BoardCaseType::GhostHomeDoorLeft:
                    SDL_SetRenderDrawColor(m_window_renderer, 64, 255, 64, 255);
                    break;
                case BoardCaseType::GhostHomeDoorRight:
                    SDL_SetRenderDrawColor(m_window_renderer, 23, 255, 64, 255);
                    break;
                case BoardCaseType::GhostHomeDoor:
                    SDL_SetRenderDrawColor(m_window_renderer, 0, 200, 0, 255);
                    break;
            }

            SDL_Rect sdlRect = {j * (672 / BOARD_SIZE_X), i * (864 / BOARD_SIZE_Y), 672 / BOARD_SIZE_X,
                                864 / BOARD_SIZE_Y};
            SDL_RenderDrawRect(m_window_renderer, &sdlRect);
        }
    }


    SDL_SetRenderDrawColor(m_window_renderer, 0, 0, 0, 255);

    SDL_RenderPresent(m_window_renderer);
}


int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Echec de l'initialisation de la SDL " << SDL_GetError() << std::endl;
        return 1;
    }

    init();
    // BOUCLE PRINCIPALE
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (!quit && SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }

        // Gestion du clavier        
        int nbk;
        const Uint8 *keys = SDL_GetKeyboardState(&nbk);
        if (keys[SDL_SCANCODE_ESCAPE])
            quit = true;
        if (keys[SDL_SCANCODE_LEFT]) { actualX = std::max(actualX - 1, 0); }
        if (keys[SDL_SCANCODE_RIGHT]) { actualX = std::min(actualX + 1, BOARD_SIZE_X - 1); }
        if (keys[SDL_SCANCODE_UP]) { actualY = std::max(actualY - 1, 0); }
        if (keys[SDL_SCANCODE_DOWN]) { actualY = std::min(actualY + 1, BOARD_SIZE_Y - 1); }
        auto boardCase = board->getCase(actualX, actualY);
        if (keys[SDL_SCANCODE_A]) {
            std::cout << "Set (" << actualX << ", " << actualY << ") to BoardCaseType::PointPath\n";
            boardCase.type() = BoardCaseType::PointPath;
        }
        if (keys[SDL_SCANCODE_Z]) {
            std::cout << "Set (" << actualX << ", " << actualY << ") to BoardCaseType::BasicPath\n";
            boardCase.type() = BoardCaseType::BasicPath;
        }
        if (keys[SDL_SCANCODE_E]) {
            std::cout << "Set (" << actualX << ", " << actualY << ") to BoardCaseType::Bonus\n";
            boardCase.type() = BoardCaseType::Bonus;
        }
        if (keys[SDL_SCANCODE_R]) {
            std::cout << "Set (" << actualX << ", " << actualY << ") to BoardCaseType::Wall\n";
            boardCase.type() = BoardCaseType::Wall;
        }
        if (keys[SDL_SCANCODE_T]) {
            std::cout << "Set (" << actualX << ", " << actualY << ") to BoardCaseType::GhostHome\n";
            boardCase.type() = BoardCaseType::GhostHome;
        }
        if (keys[SDL_SCANCODE_Y]) {
            std::cout << "Set (" << actualX << ", " << actualY << ") to BoardCaseType::GhostHomeDoorLeft\n";
            boardCase.type() = BoardCaseType::GhostHomeDoorLeft;
        }
        if (keys[SDL_SCANCODE_U]) {
            std::cout << "Set (" << actualX << ", " << actualY << ") to BoardCaseType::GhostHomeDoorRight\n";
            boardCase.type() = BoardCaseType::GhostHomeDoorRight;
        }
        if (keys[SDL_SCANCODE_I]) {
            std::cout << "Set (" << actualX << ", " << actualY << ") to BoardCaseType::GhostHomeDoor\n";
            boardCase.type() = BoardCaseType::GhostHomeDoor;
        }
        if (keys[SDL_SCANCODE_O]) {
            std::cout << "Set (" << actualX << ", " << actualY << ") to BoardCaseType::Nothing\n";
            boardCase.type() = BoardCaseType::Nothing;
        }

        if (keys[SDL_SCANCODE_S]) {
            std::cout << "Saving board...\n";
            board->save("./assets/board.xml");
        }

        // printf("(x: %d , y: %d)\n", ghost.x, ghost.y);

        // AFFICHAGE
        draw();
        SDL_UpdateWindowSurface(pWindow);
        // LIMITE A 60 FPS
        SDL_Delay(16); // utiliser SDL_GetTicks64() pour plus de precisions
    }


    delete board;
    SDL_DestroyTexture(plancheTexture);
    SDL_DestroyRenderer(m_window_renderer);
    SDL_Quit(); // ON SORT
    return 0;
}
