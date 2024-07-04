#pragma once
#include <engine/settings.h>
#include <filesystem>

class SettingsReader
{
public:
    static bool Read (std::filesystem::path iniPath);
};

