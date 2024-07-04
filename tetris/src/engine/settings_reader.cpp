#include <engine/settings_reader.h>

#include <fstream>
#include <regex>
#include <string>

namespace fs = std::filesystem;

namespace {
struct src
{
    std::string_view str;
    size_t pos;

    bool IsValid() { return pos < str.size(); }
};

enum class EntryType
{
    UNDEFINED,
    COMMENTARY,
    SECTION,
    VARIABLE
};

enum class SectionType {
    UNDEFINED,
    GENERAL,
    KEYBOARD_MAPPINGS,
    GAMEPAD_MAPPINGS
};

struct Section
{
    SectionType type;
    src         source;
};

SectionType ParseSectionType (const std::string& sectionName)
{
    if (sectionName == "General") {
        return SectionType::GENERAL;
    }
    if (sectionName == "KeyboardMappings") {
        return SectionType::KEYBOARD_MAPPINGS;
    }
    if (sectionName == "GamepadMappings") {
        return SectionType::GAMEPAD_MAPPINGS;
    }
    return SectionType::UNDEFINED;
}


std::pair <EntryType, std::cmatch> RecognizeLine (std::string_view& src)
{
    std::regex section_rgx ("\\[(\\w+)\\]");
    std::regex comment_rgx ("#.+");
    std::regex variable_rgx ("(\\w+)\\s*=\\s*(.+)");
    std::cmatch match;
    if (std::regex_match (src.data(), src.data() + src.size(), match, section_rgx)) {
        return {EntryType::SECTION, match};
    } else if (std::regex_match (src.data(), src.data() + src.size(), match, variable_rgx)) {
        return {EntryType::VARIABLE, match};
    } else if (std::regex_match (src.data(), src.data() + src.size(), match, comment_rgx)) {
        return {EntryType::COMMENTARY, match};
    }
    return {EntryType::UNDEFINED, match};
}

std::string_view GetLine (src& ssrc)
{
    size_t pos = ssrc.pos;
    auto nextDelim = ssrc.str.find ('\n', pos);
    if (nextDelim == std::string::npos) {
        ssrc.pos = ssrc.str.size();
        return std::string_view();
    } else {
        ssrc.pos = nextDelim + 1;
        return ssrc.str.substr (pos, nextDelim - pos);
    }
}

void ParseGeneralSectionVariable (const std::string& name, const std::string& value)
{
    Settings& target = Settings::GetInstance();
    if (name == "Scale") {
        float scale = std::stof (value);
        if (scale <= 1.5f && scale >= 0.25f) {
            target.SetScale (scale);
        }
    } else if (name == "EnableSound") {
        if (value == "true")
            target.SetIsAudioEnabled (true);
        else if (value == "false")
            target.SetIsAudioEnabled (false);
    }
}

void ParseKMapVariable (const std::string& name, const std::string& value)
{
    auto ParseKey = [] (const std::string& keyName) -> KeyboardKey {
        if (keyName.size() == 1 && std::isalnum (keyName[0])) { // single symbol case
            return static_cast <KeyboardKey> (keyName[0]);
        }

        if (keyName == "ARROW_UP") {
            return KeyboardKey::KEY_UP;
        } else if (keyName == "ARROW_DOWN") {
            return KeyboardKey::KEY_DOWN;
        } else if (keyName == "ARROW_LEFT") {
            return KeyboardKey::KEY_LEFT;
        } else if (keyName == "ARROW_RIGHT") {
            return KeyboardKey::KEY_RIGHT;
        } else if (keyName == "CTRL") {
            return KeyboardKey::KEY_LEFT_CONTROL;
        } else if (keyName == "ALT") {
            return KeyboardKey::KEY_LEFT_ALT;
        } else if (keyName == "SPACE") {
            return KeyboardKey::KEY_SPACE;
        } else 
            return KeyboardKey::KEY_NULL;

    };

    settings::KeyboardMappings& kmap = Settings::GetInstance().GetKeyboardMappings();

    if (name == "Hold") {
        auto key = ParseKey (value);
        if (key != KeyboardKey::KEY_NULL) {
            kmap.m_HoldKey = key;
        }
    } else if (name == "HardDrop") {
        auto key = ParseKey (value);
        if (key != KeyboardKey::KEY_NULL) {
            kmap.m_HardDropKey = key;
        }
    } else if (name == "Rotate") {
        auto key = ParseKey (value);
        if (key != KeyboardKey::KEY_NULL) {
            kmap.m_RotateKey = key;
        }
    } else if (name == "MoveRight") {
        auto key = ParseKey (value);
        if (key != KeyboardKey::KEY_NULL) {
            kmap.m_MoveRightKey = key;
        }
    } else if (name == "MoveLeft") {
        auto key = ParseKey (value);
        if (key != KeyboardKey::KEY_NULL) {
            kmap.m_MoveLeftKey = key;
        }
    } else if (name == "MoveDown") {
        auto key = ParseKey (value);
        if (key != KeyboardKey::KEY_NULL) {
            kmap.m_MoveDown = key;
        }
    }
}


void ParseGMapVariable (const std::string& name, const std::string& value)
{
    auto ParseButton = [] (const std::string& keyName) -> GamepadButton {
        if (keyName == "A") {
            return GAMEPAD_BUTTON_RIGHT_FACE_DOWN;
        } else if (keyName == "B") {
            return GAMEPAD_BUTTON_RIGHT_FACE_RIGHT;
        } else if (keyName == "X") {
            return GAMEPAD_BUTTON_RIGHT_FACE_LEFT;
        } else if (keyName == "Y") {
            return GAMEPAD_BUTTON_RIGHT_FACE_UP;
        } else if (keyName == "LB") {
            return GAMEPAD_BUTTON_LEFT_TRIGGER_1;
        } else if (keyName == "LT") {
            return GAMEPAD_BUTTON_LEFT_TRIGGER_2;
        } else if (keyName == "RB") {
            return GAMEPAD_BUTTON_RIGHT_TRIGGER_1;
        } else if (keyName == "RT") {
            return GAMEPAD_BUTTON_RIGHT_TRIGGER_2;
        } else if (keyName == "DPAD_UP") {
            return GAMEPAD_BUTTON_LEFT_FACE_UP;
        } else
            return GAMEPAD_BUTTON_UNKNOWN;
    };

    settings::GamepadMappings& gmap = Settings::GetInstance().GetGamepadMappings();

    if (name == "Hold") {
        auto button = ParseButton (value);
        if (button != GAMEPAD_BUTTON_UNKNOWN) {
            gmap.m_HoldButton = button;
        }
    } else if (name == "HardDrop") {
        auto button = ParseButton (value);
        if (button != GAMEPAD_BUTTON_UNKNOWN) {
            gmap.m_HardDropButton = button;
        }
    } else if (name == "Rotate") {
        auto button = ParseButton (value);
        if (button != GAMEPAD_BUTTON_UNKNOWN) {
            gmap.m_RotateButton = button;
        }
    }
}

}

bool SettingsReader::Read (std::filesystem::path iniPath)
{
    if (!fs::exists (iniPath)) {
        return false;
    }

    std::ifstream fileStream;
    fileStream.open (iniPath.native());
    if (!fileStream.is_open()) {
        return false;
    }

    std::string source {std::istreambuf_iterator<char> (fileStream), std::istreambuf_iterator<char>()};
    src fullSrc {std::string_view (source.data(), source.size()), 0};

    std::vector<std::pair <EntryType, std::cmatch>> preParsedLines;
    while (fullSrc.IsValid())
    {
        auto line = GetLine (fullSrc);
        if (!line.empty()) {
            auto recognizedLine = RecognizeLine (line);
            if (recognizedLine.first == EntryType::UNDEFINED) {
                continue;
            }
            preParsedLines.push_back (std::move (recognizedLine));
        }
    }

    SectionType currentSection = SectionType::UNDEFINED;

    for (auto& line : preParsedLines) {
        if (line.first == EntryType::SECTION) {
            currentSection = ParseSectionType (line.second[1]);
            continue;
        }
        if (currentSection == SectionType::UNDEFINED) {
            continue;
        }
        if (line.first != EntryType::VARIABLE) {
            continue;
        }

        switch (currentSection)
        {
        case SectionType::GENERAL:
            ParseGeneralSectionVariable (line.second[1], line.second[2]);
            break;
        case SectionType::KEYBOARD_MAPPINGS:
            ParseKMapVariable (line.second[1], line.second[2]);
            break;
        case SectionType::GAMEPAD_MAPPINGS:
            ParseGMapVariable (line.second[1], line.second[2]);
            break;
        default:
            break;
        }

    }
    return true;
}
