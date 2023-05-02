#pragma once

#include <functional>
#include "utils/position.h"
#include "entities/entity.h"
#include "entities/pacman.h"
#include "utils/random.h"

namespace pacman {

    /**
     * Ghosts can have 4 states (5 in reality)
     *  - Home : ghosts are in home idle mode
     *  - Scatter : ghosts are targetting a fixed point at a corner in map (each ghost has a custom corner)
     *  - Chase : ghosts are chasing pacman (each ghost has a custom target point)
     *  - Eaten : ghosts were frightened and have been eaten by pacman, they are in eaten mode until home
     *  The fifth mode is frightened mode, but since a ghost can be at home & in frightened mode, it is not a "state"
     */
    enum class GhostMode {
        Home, // At start of pacman, ghosts are at home
        Scatter,
        Chase,
        Eaten
    };

    /**
     * @brief Entity wrapper class for ghosts, including path finding and common ghost logic
     */
    template<EntityType T>
    class Ghost : public Entity {
        static_assert(std::is_enum<EntityType>::value, "EntityType must be an enum class");

        static_assert(T == EntityType::Inky || T == EntityType::Blinky ||
                      T == EntityType::Pinky || T == EntityType::Clyde,
                      "T must be Inky, Blinky, Pinky, or Clyde");
        GhostMode m_ghostMode;
        GhostMode m_lastGhostMode; // used when switching modes (eaten)
        Position m_target;
        GhostAnimations const &m_ghostAnimations;
        Pacman const &m_pacman;
        Position m_blinkyPosition;
        bool m_frightened;
        bool m_frightenedFlashing;
        int m_dotsCounter;
        int m_ticks;
        int m_frightenedTimeout;
        int m_frightenedFlashes;
        bool m_hasHomeExitPriority;
        int m_homeDotsNeededDots;
        int m_homeDotsEatCounter;
        int m_homeDotsEatTimeout;
    protected:
        /**
         * @return Reference to Pacman object, since the chase targeting system needs the position of pacman
         */
        [[nodiscard]] Pacman const &pacman() const { return m_pacman; }

        /**
         * @brief Handles chase target and logic (specific to blinky, clyde & pinky)
         * Executes m_targetHandlingFct function
         */
        void handleChaseTarget();

        /**
         * @brief Handles scatter mode target and logic
         */
        void handleScatterMode();

        /**
         * @brief Handles home mode target and logic
         */
        void handleHomeMode();

        /**
         * @brief Handles eaten mode target and logic
         */
        void handleEatenMode();

        /**
         * @brief Handles frightened mode (timeout and flashes)
         */
         void handleFrightenedMode();

        /**
         * @brief Moves the ghost according to direction & speed
         */
        void handleMovement();

        /**
         * @brief Changes animations according to direction, ghostMode
         * @override
         */
        void changeAnimation() override;

        /**
         * Changes the ghost direction to a practicable case (taking care of targets and other options)
         * @return The actual BoardCase the ghost is standing on
         */
        std::optional<BoardCase> handlePathFinding();

        /**
         * @brief Turns the ghost 180 degrees (opposite direction)
         */
        void turnAround();

        /**
         * @param withOpposite Add the opposite direction to the possible directions
         * @param noUp Avoid up direction in possible directions list
         * @param homeDoorPracticable Check if possible directions are practicable or not
         * @return A vector of DirectionBoardCasePair including direction and BoardCase that are possible to travel to
         */
        auto getPossibleDirections(bool withOpposite = false, bool noUp = true, bool homeDoorPracticable = false);

    public:
        Ghost(Board const &p_board, Pacman const &p_pacman, GhostAnimations const &p_ghostAnimations)
                : Entity({0, 0}, 4, Direction::LEFT, p_board)
                , m_ghostMode{GhostMode::Home}
                , m_target{}
                , m_ghostAnimations{p_ghostAnimations}
                , m_pacman{p_pacman}
                , m_blinkyPosition{}
                , m_dotsCounter{0}
                , m_ticks{0}
                , m_frightenedTimeout{0}
                , m_frightenedFlashes{0}
                , m_homeDotsEatTimeout{0}
                , m_hasHomeExitPriority{false}
                , m_homeDotsNeededDots{0}
                , m_homeDotsEatCounter{0}
                , m_frightened{false}
                , m_frightenedFlashing{false}
                , m_lastGhostMode{GhostMode::Scatter}
        {
            currentAnimation() = m_ghostAnimations.leftAnimation;
            position() = getPosition(10, 10);
        }

        ~Ghost() override = default;

        /**
         * @return Current ghost mode
         */
        [[nodiscard]] GhostMode ghostMode() const { return m_ghostMode; }
        /**
         * @return Reference to current ghost mode
         */
        GhostMode &ghostMode() { return m_ghostMode; }

        /**
         * @return Ghost target position
         */
        [[nodiscard]] Position const &target() const { return m_target; }
        /**
         * @brief Change ghost target position the path finding algorithm uses
         * @return Reference to the target position
         */
        Position &target() { return m_target; }

        [[nodiscard]] int dotsCounter() const { return m_dotsCounter; }
        int& dotsCounter() { return m_dotsCounter; }

        [[nodiscard]] int ticks() const { return m_dotsCounter; }
        int& ticks() { return m_dotsCounter; }

        /**
         * @brief Home exit priority handles dot counter & home exiting logic
         * @return Reference to homeExitPriority boolean
         */
        bool& homeExitPriority() { return m_hasHomeExitPriority; }

        /**
         * @brief Returns the position of the Blinky ghost.
         *
         * This function returns a reference to the position of the Blinky ghost.
         * If the ghost type is not EntityType::Inky, this function is disabled
         * using std::enable_if and will not be compiled.
         *
         * @return A reference to the position of the Blinky ghost.
         */
        template <EntityType U = T, typename std::enable_if<U == EntityType::Inky>::type* = nullptr>
        Position& blinkyPosition() { return m_blinkyPosition; };

        /**
         * @return Ghost is in frightened sub-mode
         */
        [[nodiscard]] bool frightened() const { return m_frightened; }
        /**
         * @brief Change ghost sub-mode to frightened
         * @return Reference to frightened bool
         */
        bool& frightened() { return m_frightened; }

        /**
         * @brief Used for setting ghost mode when switching from eaten to scatter/chase
         * @return Reference to last ghost mode
         */
        GhostMode& lastGhostMode() { return m_lastGhostMode; }

        /**
         * @brief Starts the scatter mode, changing target to a corner
         */
        void startScatterMode();

        /**
         * @brief Starts the chase mode, changing target to pacman
         */
        void startChaseMode();

        /**
         * Start the ghost mode according to m_lastGhostMode
         */
        void startLastGhostMode();

        /**
         * @brief Starts the home mode, going up and down in the home until mode changes
         */
        void startHomeMode(int p_level, bool p_dead);

        /**
         * @brief Start frightened mode, disabling path finding algorithm and using random decisions to travel trough the board
         * @param p_level Current player level to know timeouts
         */
        void startFrightenedMode(int p_level);

        /**
         * @brief Start eaten mode, changing target to home and animations to eyes
         */
        void startEatenMode();

        /**
         * Cycles changes, scatter => chase or chase => scatter
         * @param p_newMode New cycle ghost mode
         */
        void handleCycleChange(GhostMode p_newMode);

        /**
         * @brief Reset all variables to default
         * @override
         */
        void reset() override;

        /**
         * @brief Tick logic, handles intern entities logic
         * @override
         */
        void tick() override;

        /**
         * @brief Handles pacman eating a dot, to increase ghost counter
         */
        void pacmanDotEaten();

        [[nodiscard]] EntityType entityType() const override;

    };

    template<EntityType T>
    void Ghost<T>::startLastGhostMode()
    {
        if(m_lastGhostMode == GhostMode::Scatter)
        {
            startScatterMode();
        } else {
            startChaseMode();
        }
    }

    template<EntityType T>
    void Ghost<T>::pacmanDotEaten()
    {
        m_homeDotsEatCounter = 0;

        if (ghostMode() != GhostMode::Home || !m_hasHomeExitPriority) return;
        m_dotsCounter++;

        if(m_dotsCounter >= m_homeDotsNeededDots) {
            startLastGhostMode();
            return;
        }

    }

    template <EntityType T>
    void Ghost<T>::startEatenMode()
    {
        if(m_ghostMode == GhostMode::Eaten) return;
        m_lastGhostMode = m_ghostMode;
        m_ghostMode = GhostMode::Eaten;
        m_frightened = false;
        turnAround(); // turn 180 degrees
        target() = board().grid()[board().homeDoorIndex()].position();
    }

    template <EntityType T>
    void Ghost<T>::startFrightenedMode(int p_level)
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
    void Ghost<T>::startChaseMode()
    {
        if (ghostMode() == GhostMode::Chase) return;
        ghostMode() = GhostMode::Chase;
        turnAround();
    }

    template <EntityType T>
    void Ghost<T>::startHomeMode(int p_level, bool p_dead)
    {
        reset();

        m_homeDotsEatTimeout = FRAMERATE * (4 - (p_level >= 5));

        if(p_dead) return;

        if constexpr (T == EntityType::Clyde)
        {
            if (p_level == 1)
            {
                m_homeDotsNeededDots = 60;
            } else if (p_level == 2)
            {
                m_homeDotsNeededDots = 50;
            } else
            {
                m_homeDotsNeededDots = 0;
            }
        } else if constexpr (T == EntityType::Pinky)
        {
            m_homeDotsNeededDots = 0;
        } else if constexpr (T == EntityType::Inky)
        {
            if (p_level == 1)
            {
                m_homeDotsNeededDots = 30;
            } else
            {
                m_homeDotsNeededDots = 0;
            }
        }

    }

    template <EntityType T>
    void Ghost<T>::handleEatenMode()
    {
        if(ghostMode() != GhostMode::Eaten) return;
        auto const& currCase = currentCase();

        if(Board::isCase(position()) && currCase && currCase->type() == BoardCaseType::GhostHome)
        {
            startLastGhostMode();
        }

    }

    template <EntityType T>
    void Ghost<T>::handleHomeMode()
    {
        m_homeDotsEatCounter++;

        if(m_homeDotsEatCounter >= m_homeDotsEatTimeout) {
            // has prio ?
            if(m_hasHomeExitPriority) {
                startLastGhostMode();
                return;
            }
        }

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
    void Ghost<T>::handleScatterMode() {}

    template<EntityType T>
    void Ghost<T>::handleChaseTarget() {

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
    void Ghost<T>::handleFrightenedMode() {
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
    auto Ghost<T>::getPossibleDirections(bool withOpposite, bool noUp, bool homeDoorPracticable)
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
    std::optional<BoardCase> Ghost<T>::handlePathFinding()
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
    void Ghost<T>::handleMovement()
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
    void Ghost<T>::changeAnimation()
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
    void Ghost<T>::turnAround()
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
    void Ghost<T>::tick() {

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
    void Ghost<T>::reset() {
        m_frightened = false;
        m_frightenedFlashing = false;
        m_frightenedTimeout = 0;
        m_frightenedFlashes = 0;
        m_ticks = 0;
        m_dotsCounter = 0;
        m_hasHomeExitPriority = false;
        m_homeDotsNeededDots = 0;
        m_homeDotsEatTimeout = 0;
        m_homeDotsEatCounter = 0;

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
    void Ghost<T>::startScatterMode() {
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
    EntityType Ghost<T>::entityType() const {
        return T;
    }


}

