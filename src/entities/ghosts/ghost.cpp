#include "entities/ghosts/ghost.h"
#include "utils/random.h"

using namespace pacman;

void Ghost::startEatenMode() noexcept
{
    if(m_ghostMode == GhostMode::Eaten) return;
    m_lastGhostMode = m_ghostMode;
    m_ghostMode = GhostMode::Eaten;
    m_frightened = false;
    turnAround(); // turn 180 degrees
    target() = board().grid()[board().homeDoorIndex()].position();
}

void Ghost::startFrightenedMode(int p_level) noexcept
{
    if(m_frightened || m_ghostMode == GhostMode::Eaten) return;

    // Handle timeouts
    if (p_level > GHOST_FRIGHTENED_TIMEOUTS_COUNT) {
        m_frightenedTimeout = 0;
        m_frightenedFlashes = 0;
    } else {
        m_frightenedTimeout = GHOST_FRIGHTENED_TIMEOUTS[p_level - 1];
        m_frightenedFlashes = GHOST_FRIGHTENED_FLASHES[p_level - 1];
    }

    // Don't start frightened mode when timeout is 0
    if(m_frightenedTimeout == 0) return;

    m_ticks = 0;
    m_frightened = true;
    turnAround(); // turn 180 degrees
}

void Ghost::startChaseMode() noexcept
{
    if (ghostMode() == GhostMode::Chase) return;
    ghostMode() = GhostMode::Chase;
    turnAround();
}

void Ghost::startHomeMode() noexcept
{
    if(ghostMode() == GhostMode::Home) return;
    reset();
}


void Ghost::handleEatenMode() noexcept
{
    if(ghostMode() != GhostMode::Eaten) return;
    auto const& currCase = currentCase();

    if(Board::isCase(position()) && currCase && currCase->type() == BoardCaseType::GhostHome)
    {
        if(m_lastGhostMode == GhostMode::Scatter)
        {
            startScatterMode();
        } else {
            startChaseMode();
        }
    }

}

void Ghost::handleHomeMode() noexcept
{
    // Home mode: ghost going up & down
    if(Board::isCase(position())) {

        auto const &nextCase = board().getBoardCaseAtPixels(position(), direction());

        if (!nextCase) return; // should not be null

        if (!BoardCase::isPracticable(nextCase.value(), false)) {
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

void Ghost::handleFrightenedMode() noexcept {
    if(!m_frightened) return;

    m_ticks++;

    if(m_ticks >= m_frightenedTimeout) {
        m_frightened = false;
        m_frightenedTimeout = 0;
        m_frightenedFlashing = false;
        changeAnimation();
        return;
    }

    auto const flashesTimout = m_frightenedFlashes * GHOST_FRIGHTENED_FLASH_DURATION * 2;
    auto remainingTime = m_frightenedTimeout - flashesTimout;

    if(m_ticks < remainingTime) {
        return;
    }

    if((m_frightenedTimeout - m_ticks) % GHOST_FRIGHTENED_FLASH_DURATION == 0)
    {
        m_frightenedFlashing = !m_frightenedFlashing;
    }

}

auto Ghost::getPossibleDirections(bool withOpposite, bool noUp, bool homeDoorPracticable) noexcept
{
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
            std::remove_if(pairs.begin(), pairs.end(), [&noUp, &flagNoUp, &homeDoorPracticable](auto const &p) {
                return (noUp && p.first == Direction::UP && flagNoUp)
                       || !p.second || !BoardCase::isPracticable(p.second.value(), homeDoorPracticable);
            }), pairs.end()
    );

    return pairs;
}

std::optional<BoardCase> Ghost::handlePathFinding() noexcept
{
    if(!currentCase()) return std::nullopt;
    auto const& actualCase = currentCase();
    auto caseIsHome = actualCase->type() == BoardCaseType::GhostHome;

    if(ghostMode() != GhostMode::Home && !caseIsHome && m_frightened) {
        auto pairs = getPossibleDirections(false, true, false);
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

    auto pairs = getPossibleDirections(caseIsHome, !m_frightened, homeDoorPracticable);
    auto const &foundCase = getClosestBoardCase(destination, pairs, homeDoorPracticable);

    // foundCase should not be null
    if (foundCase.second)
    {
        direction() = foundCase.first;
        changeAnimation();
    }
    return foundCase.second;

}

void Ghost::handleMovement() noexcept
{
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

void Ghost::changeAnimation() noexcept
{
    currentAnimation()->freeze() = false;

    if(m_frightened)
    {

        if(m_frightenedFlashing) {
            currentAnimation() = m_ghostAnimations.frightenedAnimation;
        } else {
            currentAnimation() = m_ghostAnimations.frightenedAnimation;
        }

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

        if (!BoardCase::isPracticable(nextCase.value(), false)) {
            // todo: handle other direction
        }

        changeAnimation();
    } else {
        direction() = opposite;
        changeAnimation();
    }

}

void Ghost::handleCycleChange(GhostMode p_newMode)
{
    if(m_ghostMode == GhostMode::Chase && p_newMode == GhostMode::Scatter) {
        startScatterMode();
    } else if(m_ghostMode == GhostMode::Scatter && p_newMode == GhostMode::Chase) {
        startChaseMode();
    } else {
        m_lastGhostMode = p_newMode;
    }
}

void Ghost::tick() noexcept {

    if(freezed() || !activated()) return;
    currentCase() = board().getBoardCaseAtPixels(position());

    if(frightened()) { handleFrightenedMode(); }

    switch(ghostMode())
    {
        case GhostMode::Home:
            handleHomeMode();
            return;
        case GhostMode::Scatter:
            handleScatterMode();
            break;
        case GhostMode::Chase:
            handleChaseTarget();
            break;
        case GhostMode::Eaten:
            handleEatenMode();
            break;
    }

    // handle path finding & movements
    handleMovement();
}

void Ghost::reset() noexcept {
    m_frightened = false;
    m_frightenedFlashing = false;
    m_frightenedTimeout = 0;
    m_frightenedFlashes = 0;
    m_ticks = 0;
}
