#pragma once

#include "utils/position.h"
#include "entities/entity.h"
#include "entities/pacman.h"

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
    class Ghost : public Entity {
        GhostMode m_ghostMode;
        GhostMode m_lastGhostMode; // used when switching modes (eaten)
        Position m_target;
        GhostAnimations const &m_ghostAnimations;
        Pacman const &m_pacman;
        bool m_frightened;
        bool m_frightenedFlashing;
        int m_dotsCounter;
        int m_ticks;
        int m_frightenedTimeout;
        int m_frightenedFlashes;
    protected:
        /**
         * @return Reference to Pacman object, since the chase targeting system needs the position of pacman
         */
        [[nodiscard]] Pacman const &pacman() const { return m_pacman; }

        /**
         * @brief Handles chase target and logic (specific to each ghost)
         */
        virtual void handleChaseTarget() noexcept = 0;

        /**
         * @brief Handles scatter mode target and logic
         */
        void handleScatterMode() noexcept;

        /**
         * @brief Handles home mode target and logic
         */
        void handleHomeMode() noexcept;

        /**
         * @brief Handles eaten mode target and logic
         */
        void handleEatenMode() noexcept;

        /**
         * @brief Handles frightened mode (timeout and flashes)
         */
         void handleFrightenedMode() noexcept;

        /**
         * @brief Moves the ghost according to direction & speed
         */
        void handleMovement() noexcept;

        /**
         * @brief Changes animations according to direction, ghostMode
         * @override
         */
        void changeAnimation() noexcept override;

        /**
         * Changes the ghost direction to a practicable case (taking care of targets and other options)
         * @return The actual BoardCase the ghost is standing on
         */
        std::optional<BoardCase> handlePathFinding() noexcept;

        /**
         * @brief Turns the ghost 180 degrees (opposite direction)
         */
        void turnAround() noexcept;

        /**
         * @param withOpposite Add the opposite direction to the possible directions
         * @param noUp Avoid up direction in possible directions list
         * @param homeDoorPracticable Check if possible directions are practicable or not
         * @return A vector of DirectionBoardCasePair including direction and BoardCase that are possible to travel to
         */
        auto getPossibleDirections(bool withOpposite = false, bool noUp = true, bool homeDoorPracticable = false) noexcept;

        /**
         * @brief Tick logic, handles intern entities logic
         * @override
         */
        void tick() noexcept override;

    public:
        Ghost(Board const &p_board, Pacman const &p_pacman, GhostMode p_ghostMode, GhostAnimations const &p_ghostAnimations)
                : Entity({0, 0}, 4, Direction::LEFT, p_board)
                , m_ghostMode(p_ghostMode)
                , m_target{}
                , m_ghostAnimations{p_ghostAnimations}
                , m_pacman{p_pacman}
                , m_dotsCounter{0}
                , m_ticks{0}
                , m_frightenedTimeout{0}
                , m_frightenedFlashes{0}
                , m_frightened{false}
                , m_frightenedFlashing{false}
                , m_lastGhostMode{GhostMode::Scatter}
        {
            currentAnimation() = m_ghostAnimations.leftAnimation;
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
        virtual void startScatterMode() noexcept = 0;

        /**
         * @brief Starts the chase mode, changing target to pacman
         */
        void startChaseMode() noexcept;

        /**
         * @brief Starts the home mode, going up and down in the home until mode changes
         */
        void startHomeMode() noexcept;

        /**
         * @brief Start frightened mode, disabling path finding algorithm and using random decisions to travel trough the board
         * @param p_level Current player level to know timeouts
         */
        void startFrightenedMode(int p_level) noexcept;

        /**
         * @brief Start eaten mode, changing target to home and animations to eyes
         */
        void startEatenMode() noexcept;

        /**
         * Cycles changes, scatter => chase or chase => scatter
         * @param p_newMode New cycle ghost mode
         */
        void handleCycleChange(GhostMode p_newMode);

        void reset() noexcept override;

    };

}