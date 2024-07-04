#include <engine/audio_manager.h>

namespace {

}

AudioManager& AudioManager::GetInstance()
{
    static AudioManager manager;
    return manager;
}

void AudioManager::Init (bool bIsSoundEnabled)
{
    m_bIsSoundEnabled = bIsSoundEnabled;
    if (m_bIsSoundEnabled) {
        InitSound ("block_move", "resources/hi_hat.wav");
        InitSound ("block_drop", "resources/snare.wav");
        InitSound ("tetris", "resources/ta_da.wav");
        InitSound ("block_hold", "resources/808_click.wav");
        InitSound ("button_pressed", "resources/square_click_louder.wav");
        InitSound ("flash", "resources/flash_7.wav");
    }
}

void AudioManager::InitSound (std::string name_id, std::string path)
{
    auto sound = LoadSound (path.c_str());
    m_sounds.emplace (std::move (name_id), std::move (sound));
}

void AudioManager::Play (std::string name_id)
{
    if (m_bIsSoundEnabled && m_sounds.contains (name_id)) {
        PlaySound (m_sounds[name_id]);
    }
}

AudioManager::AudioManager():
    m_bIsSoundEnabled (true)
{
    InitAudioDevice();
}

AudioManager::~AudioManager()
{
    for (auto& [id, sound] : m_sounds) {
        UnloadSound (sound);
    }
    CloseAudioDevice();
}
