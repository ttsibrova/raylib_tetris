#pragma once

#include <raylib/raylib.h>
#include <memory>
#include <unordered_map>
#include <string>

class AudioManager
{
public:
    static AudioManager& GetInstance();
    void Init (bool bIsSoundEnabled);

    void Play (std::string name_id);

    ~AudioManager();

    AudioManager (AudioManager const&) = delete;
    void operator= (AudioManager const&) = delete;

private:
    AudioManager();

    void InitSound (std::string name_id, std::string path);

private:
    std::unordered_map <std::string, Sound> m_sounds;
    bool                                    m_bIsSoundEnabled;

};

