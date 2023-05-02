#pragma once

#include <memory>
#include <string>

#include "SDL_mixer.h"
#include "utils/constants.h"

namespace pacman {

    using MixChunkPtr = std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)>;

    /**
     * @enum Audio
     * @brief Represents the available audio clips that can be played by the AudioHandler
     */
    enum class Audio {
        None,
        Credit,
        Death,
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
     * @brief Manages audio clips and provides methods to play and pause them
     *
     * Actually, there are 3 audio channels
     * Therefore, when more than two sounds are played at the same time,
     * one channel will be overwritten.
     *
     * - Channel 0 : misc sounds
     * - Channel 1 : ghost sounds
     * - Channel 2 : ghost sirens
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

        std::array<Audio, AUDIO_CHANNELS> m_lastKnownAudio;

    public:
      /**
       * @brief Constructs an AudioHandler object.
       */
        AudioHandler();

        /**
         * @brief Plays the specified audio on the specified channel.
         *
         * @param p_audio The audio to play.
         * @param p_channel The channel to play the audio on. Defaults to 0.
         * @param p_duration The duration of the audio in milliseconds. Defaults to -1 (play indefinitely).
         * @param p_loops The number of times to loop the audio. Defaults to 0 (play once).
         */
        void playAudio(Audio p_audio, int p_channel = 0, int p_duration = -1, int p_loops = 0);

        /**
         * @brief Pauses the audio on the specified channel.
         *
         * @param p_channel The channel to pause the audio on. Defaults to 0.
         */
        void pauseAudio(int p_channel = 0);

        /**
         * @brief Resumes playing the audio on the specified channel.
         *
         * @param p_channel The channel to resume playing the audio on. Defaults to 0.
         */
        void resumeAudio(int p_channel = 0);

        /**
         * @brief Pauses all audio on all channels.
         */
        void pauseAll();

        /**
         * @brief Returns a reference to the MixChunkPtr associated with the specified audio.
         *
         * @param p_audio The audio to find.
         * @return A reference to the MixChunkPtr associated with the specified audio.
         */
        MixChunkPtr& find(Audio p_audio);

        /**
        * @brief Returns the file path for a given audio effect.
        *
        * @param p_audio The audio effect to get the file path for.
        * @return The file path for the given audio effect.
        */
        static std::string getFilePath(Audio p_audio);

        /**
        * @brief Returns the last known audio played on a given channel.
        *
        * @param p_channel The channel to get the last known audio for.
        * @return The last known audio played on the given channel.
        */
        [[nodiscard]] inline Audio getLastKnownAudioPlayed(int p_channel) const
        {
            return m_lastKnownAudio[p_channel];
        }

        /**
        * @brief Returns the siren sound effect for a given siren number.
        *
        * @param p_sirenNb The siren number to get the sound effect for.
        * @return The sound effect for the given siren number.
        */
        inline Audio getSiren(int p_sirenNb) {
            if(p_sirenNb < 1 || p_sirenNb > 5) return Audio::Siren1;
            return (Audio) (static_cast<int>(Audio::Siren1) + (p_sirenNb - 1));
        }
    };

}