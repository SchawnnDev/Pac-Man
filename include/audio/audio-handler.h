#pragma once

#include <memory>

#include "SDL_mixer.h"

namespace pacman {

    using MixChunkPtr = std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)>;

    enum class Audio {
        Credit,
        Death,
        Death2,
        EatFruit,
        EatGhost,
        Extend,
        GameStart,
        Intermission,
        Munch1,
        Munch2,
        PowerPellet,
        Retreating,
        Siren1,
        Siren2,
        Siren3,
        Siren4,
        Siren5
    };
    /**
     * @class AudioHandler
     *
     * Actually, there are 2 audio channels
     * Therefore, when more than two sounds are played at the same time,
     * one channel will be overwritten.
     *
     * - Channel 0 : misc sounds
     * - Channel 1 : ghost sounds
     *
     */
    class AudioHandler {

        /**
         * Chunks are lazy loaded
         * When a sound is played and not loaded
         * it will be, and then saved into MixChunkPtr
         */
        MixChunkPtr m_credit{nullptr, Mix_FreeChunk};
        MixChunkPtr m_death{nullptr, Mix_FreeChunk};
        MixChunkPtr m_death_2{nullptr, Mix_FreeChunk};
        MixChunkPtr m_eat_fruit{nullptr, Mix_FreeChunk};
        MixChunkPtr m_eat_ghost{nullptr, Mix_FreeChunk};
        MixChunkPtr m_extend{nullptr, Mix_FreeChunk};
        MixChunkPtr m_game_start{nullptr, Mix_FreeChunk};
        MixChunkPtr m_intermission{nullptr, Mix_FreeChunk};
        MixChunkPtr m_munch_1{nullptr, Mix_FreeChunk};
        MixChunkPtr m_munch_2{nullptr, Mix_FreeChunk};
        MixChunkPtr m_power_pellet{nullptr, Mix_FreeChunk};
        MixChunkPtr m_retreating{nullptr, Mix_FreeChunk};
        MixChunkPtr m_siren_1{nullptr, Mix_FreeChunk};
        MixChunkPtr m_siren_2{nullptr, Mix_FreeChunk};
        MixChunkPtr m_siren_3{nullptr, Mix_FreeChunk};
        MixChunkPtr m_siren_4{nullptr, Mix_FreeChunk};
        MixChunkPtr m_siren_5{nullptr, Mix_FreeChunk};

    public:
        AudioHandler();

        void playAudio(Audio p_audio, int p_channel = 0, int p_delay = -1, int p_loops = 0) noexcept;

        void pauseAudio(int p_channel = 0) noexcept;

        void resumeAudio(int p_channel = 0) noexcept;

        MixChunkPtr& find(Audio p_audio) noexcept;

        static std::string getFilePath(Audio p_audio) noexcept;
    };

}