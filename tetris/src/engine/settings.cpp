#include <engine/settings.h>
#include <engine/settings_reader.h>

Settings& Settings::GetInstance()
{
    static Settings instance;
    return instance;
}

void Settings::Init()
{
    SettingsReader::Read ("data/settings.ini");
}
