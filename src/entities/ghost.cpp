#include "entities/ghost.h"
#include "utils/random.h"

using namespace pacman;

template <EntityType T>
void Ghost<T>::startEatenMode() noexcept
{
    if(m_ghostMode == GhostMode::Eaten) return;
    m_lastGhostMode = m_ghostMode;
    m_ghostMode = GhostMode::Eaten;
    m_frightened = false;
    turnAround(); // turn 180 degrees
    target() = board().grid()[board().homeDoorIndex()].position();
}

template <EntityType T>
void Ghost<T>::startFrightenedMode(int p_level) noexcept
{
    if(m_ghostMode == GhostMode::Eaten) return;

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
    m_frightenedFlashing = false;
    m_frightened = true;
    turnAround(); // turn 180 degrees
    Ghost<T>::changeAnimation();
}

template <EntityType T>
void Ghost<T>::startChaseMode() noexcept
{
    if (ghostMode() == GhostMode::Chase) return;
    ghostMode() = GhostMode::Chase;
    turnAround();
}

template <EntityType T>
void Ghost<T>::startHomeMode() noexcept
{
    if(ghostMode() == GhostMode::Home) return;
    reset();
}

template <EntityType T>
void Ghost<T>::handleEatenMode() noexcept
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

template <EntityType T>
void Ghost<T>::handleHomeMode() noexcept
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

            Ghost<T>::changeAnimation();
        }
    }

    position().moveAt(direction(), speed() / 2); //TODO: MAYBE HANDLE SPEED IN ONE FCT
}

template <EntityType T>
void Ghost<T>::handleScatterMode() noexcept {}

template<EntityType T>
void Ghost<T>::handleChaseTarget() noexcept {

    if constexpr (T == EntityType::Blinky) {
        target() = Board::findCase(pacman().position());
    } else if constexpr (T == EntityType::Clyde) {
        auto currentPosition = Board::findCase(position());
        auto position = Board::findCase(pacman().position());

        if(position.distanceTo(currentPosition) >= 64) // distance without sqrt => 8^2
        {
            target() = position;
        } else {
            // Clyde switches to scatter when pacman is located at 8 or more cases
            target() = {0, BOARD_SIZE_Y + 1};
        }
    } else if constexpr (T == EntityType::Inky) {
        auto position = Board::findCase(pacman().position());
        // move 2 cases in the front of pacman
        position.moveAt(pacman().direction(), 2);

        // move 2 cases to the left if pacman is going up (specific)
        if (pacman().direction() == Direction::UP) {
            position.moveAt(Direction::LEFT, 2);
        }

        // Calculate the vector between above point and blinky's position
        // Rotate vec2 by 180 degrees (just switch signs)
        target() = Board::findCase(m_blinkyPosition).rotateVec(position, 180);
    } else if constexpr (T == EntityType::Pinky) {
        auto position = Board::findCase(pacman().position());
        // move 4 cases in the front of pacman
        position.moveAt(pacman().direction(), 4);

        // move 4 cases to the left if pacman is going up (specific)
        if (pacman().direction() == Direction::UP) {
            position.moveAt(Direction::LEFT, 4);
        }

        target() = position;
    }

}

template <EntityType T>
void Ghost<T>::handleFrightenedMode() noexcept {
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
        changeAnimation();
    }

}

template <EntityType T>
auto Ghost<T>::getPossibleDirections(bool withOpposite, bool noUp, bool homeDoorPracticable) noexcept
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

template <EntityType T>
std::optional<BoardCase> Ghost<T>::handlePathFinding() noexcept
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

template <EntityType T>
void Ghost<T>::handleMovement() noexcept
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

template <EntityType T>
void Ghost<T>::changeAnimation() noexcept
{
    currentAnimation()->freeze() = false;

    if(m_frightened)
    {

        if(m_frightenedFlashing) {
            currentAnimation() = m_ghostAnimations.frightenedEndAnimation;
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

template<EntityType T>
void Ghost<T>::turnAround() noexcept
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

template<EntityType T>
void Ghost<T>::handleCycleChange(GhostMode p_newMode)
{
    if(m_ghostMode == GhostMode::Chase && p_newMode == GhostMode::Scatter) {
        startScatterMode();
    } else if(m_ghostMode == GhostMode::Scatter && p_newMode == GhostMode::Chase) {
        startChaseMode();
    } else {
        m_lastGhostMode = p_newMode;
    }
}

template<EntityType T>
void Ghost<T>::tick() noexcept {

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

template<EntityType T>
void Ghost<T>::reset() noexcept {
    m_frightened = false;
    m_frightenedFlashing = false;
    m_frightenedTimeout = 0;
    m_frightenedFlashes = 0;
    m_ticks = 0;

    if constexpr (T == EntityType::Blinky) {
        position() = getPosition(10, 10);
        direction() = Direction::LEFT;
        startScatterMode();
        Ghost::changeAnimation();
    } else if constexpr (T == EntityType::Clyde) {
        position() = getPosition(11, 13);
        ghostMode() = GhostMode::Home;
        direction() = Direction::UP;
        Ghost::changeAnimation();
    } else if constexpr (T == EntityType::Inky) {
        position() = getPosition(9, 13);
        ghostMode() = GhostMode::Home;
        direction() = Direction::UP;
        target() = {9, 11};
        Ghost::changeAnimation();
    } else if constexpr (T == EntityType::Pinky) {
        position() = getPosition(10, 12);
        ghostMode() = GhostMode::Home;
        direction() = Direction::DOWN;
        target() = {10, 14};
        Ghost::changeAnimation();
    }

}

template<EntityType T>
void Ghost<T>::startScatterMode() noexcept {
    if (ghostMode() == GhostMode::Scatter) return;
    ghostMode() = GhostMode::Scatter;

    if constexpr (T == EntityType::Blinky) {
        target() = {2, -3};
    } else if constexpr (T == EntityType::Clyde) {
        target() = {0, BOARD_SIZE_Y + 1};
    } else if constexpr (T == EntityType::Inky) {
        target() = {BOARD_SIZE_X - 1, BOARD_SIZE_Y + 1};
    } else if constexpr (T == EntityType::Pinky) {
        target() = {BOARD_SIZE_X - 3, -3};
    }

}

template<EntityType T>
EntityType Ghost<T>::entityType() const noexcept {
    return T;
}
