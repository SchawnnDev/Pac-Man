#include "entities/ghosts/ghost.h"
#include "utils/random.h"

using namespace pacman;

Ghost::~Ghost() = default;

void Ghost::startEatenMode() noexcept {
    if(m_ghostMode == GhostMode::Eaten) return;
    m_ghostMode = GhostMode::Eaten;
    m_frightened = false;
    turnAround(); // turn 180 degrees
    target() = board().grid()[board().homeDoorIndex()].position().subtract({0, 1});
}

void Ghost::startFrightenedMode() noexcept {
    if(m_frightened || m_ghostMode == GhostMode::Eaten) return;
    m_frightened = true;
    turnAround(); // turn 180 degrees
}

void Ghost::startChaseMode() noexcept
{
    if (ghostMode() == GhostMode::Chase) return;
    ghostMode() = GhostMode::Chase;
    turnAround();
}

void Ghost::startHomeMode() noexcept {
    if(ghostMode() == GhostMode::Home) return;
    reset();
}


void Ghost::handleEatenMode() noexcept
{
    if(ghostMode() != GhostMode::Eaten) return;
    auto const& currCase = currentCase();

    if(Board::isCase(position()) && currCase && currCase->type() == BoardCaseType::GhostHome)
    {
        startScatterMode();
    }

}

void Ghost::handleHomeMode() noexcept {
    // Home mode: ghost going up & down
    if(Board::isCase(position())) {

        auto const &nextCase = board().getBoardCaseAtPixels(position(), direction());

        if (!nextCase) return; // should not be null

        if (!BoardCase::isPracticable(nextCase.value())) {
            if (direction() == Direction::DOWN) {
                direction() = Direction::UP;
            } else if (direction() == Direction::UP) {
                direction() = Direction::DOWN;
            }

            Ghost::changeAnimation();
        }
    }

    position().moveAt(direction(), speed() / 2); //TODO: MAYBE HANDLE SPEED IN ONE FCT
}


void Ghost::handleScatterMode() noexcept {}

auto Ghost::getPossibleDirections(bool withOpposite, bool noUp, bool checkPracticable) noexcept {
    // Ghost is on a tile, and he must choose a direction
    auto pairs = std::vector<DirectionBoardCasePair>{};
    auto const& actualCase = currentCase();
    auto frontDirection = direction();
    auto const& frontCase = board().getBoardCaseAtPixels(position(), frontDirection);
    auto leftDirection = getDirectionByAngle(direction(), 90);
    auto const& leftCase = board().getBoardCaseAtPixels(position(), leftDirection);
    auto rightDirection = getDirectionByAngle(direction(), -90);
    auto const& rightCase = board().getBoardCaseAtPixels(position(), rightDirection);
    auto oppositeDirection = getOpposite(direction());
    auto const& oppositeCase = board().getBoardCaseAtPixels(position(), oppositeDirection);

    if(withOpposite) {
        pairs.emplace_back(oppositeDirection, oppositeCase);
    }
    pairs.emplace_back(frontDirection, frontCase);
    pairs.emplace_back(leftDirection, leftCase);
    pairs.emplace_back(rightDirection, rightCase);

    bool const flagNoUp = actualCase->flags() & CASE_FLAG_NO_UP;

    pairs.erase(
            std::remove_if(pairs.begin(), pairs.end(), [&noUp, &flagNoUp, &checkPracticable](auto const &p) {
                return (noUp && p.first == Direction::UP && flagNoUp)
                       || !p.second || (checkPracticable && !BoardCase::isPracticable(p.second.value()));
            }), pairs.end()
    );

    return pairs;
}

std::optional<BoardCase> Ghost::handlePathFinding() noexcept {
    if(!currentCase()) return std::nullopt;
    auto const& actualCase = currentCase();
    auto caseIsHome = actualCase->type() == BoardCaseType::GhostHome;
    auto pairs = getPossibleDirections(caseIsHome, !m_frightened, !caseIsHome && m_frightened);

    if(ghostMode() != GhostMode::Home && !caseIsHome && m_frightened) {
        if(pairs.empty()) return std::nullopt;
        auto r = *select_randomly(pairs.begin(), pairs.end());

        // foundCase should not be null
        if (r.second)
        {
            direction() = r.first;
            changeAnimation();
        }

        return r.second;
    }

    auto destination = target();
    auto homeDoorPracticable = false;

    if (ghostMode() != GhostMode::Home && caseIsHome) {
        homeDoorPracticable = true;
        // Change target to get out of the home
        destination = board().grid()[board().homeDoorIndex()].position().subtract({0, 1});
    } else if (ghostMode() == GhostMode::Eaten) {
        homeDoorPracticable = true;
    }

    auto const &foundCase = getClosestBoardCase(destination, pairs, homeDoorPracticable);

    // foundCase should not be null
    if (foundCase.second)
    {
        direction() = foundCase.first;
        changeAnimation();
    }
    return foundCase.second;

}

void Ghost::handleMovement() noexcept {
    if(!currentCase()) return;
    auto const& actualCase = currentCase();
    auto currentSpeed = speed();

    if (Board::isCase(position())) { // actualCase cannot be null

        if (direction() == Direction::RIGHT && actualCase->type() == BoardCaseType::DoorRight) {
            auto const& boardCase = board().grid()[board().leftDoorIndex()];
            position() = getPosition(boardCase.x(), boardCase.y());
            return;
        }

        if (direction() == Direction::LEFT && actualCase->type() == BoardCaseType::DoorLeft) {
            auto const& boardCase = board().grid()[board().rightDoorIndex()];
            position() = getPosition(boardCase.x(), boardCase.y());
            return;
        }


        auto const& newCase = handlePathFinding();

        // TODO: convert to fct
        // TODO: review this (should be 40%)

        if(newCase->type() == BoardCaseType::GhostHome || newCase->type() == BoardCaseType::GhostHomeDoor)
        {
            currentSpeed /= 2;
        } else if (newCase->flags() & CASE_FLAG_TUNNEL_SLOW_DOWN) {
            currentSpeed /= 2;
        }

    } else {

        if(actualCase->type() == BoardCaseType::GhostHome || actualCase->type() == BoardCaseType::GhostHomeDoor)
        {
            currentSpeed /= 2;
        } else if (actualCase->flags() & CASE_FLAG_TUNNEL_SLOW_DOWN) {
            currentSpeed /= 2;
        }

    }

    position().moveAt(direction(), currentSpeed);

}

void Ghost::changeAnimation() noexcept {
    currentAnimation()->freeze() = false;

    if(m_frightened)
    {
        currentAnimation() = m_ghostAnimations.frightenedAnimation;
        // TODO: impl end frightened animation
        return;
    }

    auto const eaten = m_ghostMode == GhostMode::Eaten;

    switch (direction()) {
        case Direction::UP:
            currentAnimation() = eaten ? m_ghostAnimations.eyesUpAnimation : m_ghostAnimations.upAnimation;
            break;
        case Direction::DOWN:
            currentAnimation() = eaten ? m_ghostAnimations.eyesDownAnimation : m_ghostAnimations.downAnimation;
            break;
        case Direction::LEFT:
            currentAnimation() = eaten ? m_ghostAnimations.eyesLeftAnimation : m_ghostAnimations.leftAnimation;
            break;
        case Direction::RIGHT:
            currentAnimation() = eaten ? m_ghostAnimations.eyesRightAnimation : m_ghostAnimations.rightAnimation;
            break;
    }

}

void Ghost::turnAround() noexcept
{
    auto const opposite = getOpposite(direction());

    if(Board::isCase(position())) {

        auto const &nextCase = board().getBoardCaseAtPixels(position(), opposite);

        if (!nextCase) return; // should not be null

        if (!BoardCase::isPracticable(nextCase.value())) {
            // todo:
        }

        changeAnimation();
    } else {
        direction() = opposite;
        changeAnimation();
    }

}