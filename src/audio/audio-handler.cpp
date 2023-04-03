#include "audio/audio-handler.h"
#include "utils/constants.h"

using namespace pacman;

AudioHandler::AudioHandler() = default;

MixChunkPtr& AudioHandler::find(Audio p_audio) noexcept {
    switch (p_audio) {
        case Audio::Credit:
            return m_credit;
        case Audio::Death:
            return m_death;
        case Audio::EatFruit:
            return m_eat_fruit;
        case Audio::EatGhost:
            return m_eat_ghost;
        case Audio::Extend:
            return m_extend;
        case Audio::GameStart:
            return m_game_start;
        case Audio::Intermission:
            return m_intermission;
        case Audio::Munch1:
            return m_munch_1;
        case Audio::Munch2:
            return m_munch_2;
        case Audio::PowerPellet:
            return m_power_pellet;
        case Audio::Retreating:
            return m_retreating;
        case Audio::Siren1:
            return m_siren_1;
        case Audio::Siren2:
            return m_siren_2;
        case Audio::Siren3:
            return m_siren_3;
        case Audio::Siren4:
            return m_siren_4;
        default:
            return m_siren_5;
    }
}

void AudioHandler::playAudio(Audio p_audio, int p_channel, int p_duration, int p_loops) noexcept
{
    auto& found = find(p_audio);

    // handle channels
    p_channel = p_channel < AUDIO_CHANNELS ? p_channel : 0;

    // lazy loading
    if(found.get() == nullptr) {
        found.reset(Mix_LoadWAV(getFilePath(p_audio).c_str()));
    }

    Mix_PlayChannelTimed(p_channel, found.get(), p_loops, p_duration);
}

void AudioHandler::pauseAudio(int p_channel) noexcept
{
    Mix_Pause(p_channel);
}

void AudioHandler::resumeAudio(int p_channel) noexcept
{
    Mix_Resume(p_channel);
}

std::string AudioHandler::getFilePath(Audio p_audio) noexcept {
    return AUDIO_FOLDER_PATH + std::string{AUDIO_FILES[static_cast<int>(p_audio)]} + AUDIO_EXTENSION;
}