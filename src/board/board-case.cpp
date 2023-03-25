#include "board/board-case.h"

using namespace pacman;

void BoardCase::draw(SDL_Renderer *p_window_renderer, SDL_Texture *p_texture) noexcept
{
    if(!activated()) return;
    if (m_currentAnimation) {
        auto centered = getRectCenteredPosition(m_x, m_y);
        auto &spriteAnimation = m_currentAnimation.value();
        auto found = spriteAnimation.display();
        if (found) {
            auto sprite = found.value();
            centered.x -= sprite.rect().w * 2;
            centered.y -= sprite.rect().h * 2;
            centered.w = sprite.rect().w * 4;
            centered.h = sprite.rect().h * 4;
            SDL_RenderCopy(p_window_renderer, p_texture,
                           &sprite.rect(), &centered);
        }
    }
}

DirectionBoardCasePair
pacman::getClosestBoardCase(Position p_target, std::span<const DirectionBoardCasePair> p_boardCases,
                            bool p_acceptHomeDoor) noexcept {
    DirectionBoardCasePair result{Direction::DOWN, std::nullopt};
    int distanceTo = -1;

    for (const DirectionBoardCasePair &pair: p_boardCases) {
        auto& boardCase = pair.second;
        if (!boardCase) continue;

        auto isHomeDoorPracticable = boardCase->type() == BoardCaseType::GhostHomeDoor && p_acceptHomeDoor;

        if (!BoardCase::isPracticable(boardCase.value(), false) && !isHomeDoorPracticable) {
            continue;
        }

        auto distance = boardCase.value().position().distanceTo(p_target);

        if (result.second) {
            if (distance < distanceTo) {
                distanceTo = distance;
                result = pair;
            } else if (distance == distanceTo &&
                       getDirectionPriority(pair.first) > getDirectionPriority(result.first)) {
                // check priority of directions
                result = pair;
            }
        } else {
            result = pair;
            distanceTo = distance;
        }

    }

    return result;
}
