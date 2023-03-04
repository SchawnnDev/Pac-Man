#include "board/board-case.h"

using namespace pacman;

DirectionBoardCasePair pacman::getClosestBoardCase(Position p_target, std::span<const DirectionBoardCasePair> p_boardCases) noexcept {
    DirectionBoardCasePair result{Direction::DOWN, std::nullopt};
    int distanceTo = -1;

    for (const DirectionBoardCasePair &pair: p_boardCases) {
        auto& boardCase = pair.second;
        if (!boardCase || !BoardCase::isPracticable(boardCase.value())) continue;

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
