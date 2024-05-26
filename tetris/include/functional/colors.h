#pragma once
#include <raylib/raylib.h>
#include <array>

namespace Colors {
    constexpr static Color darkBlue = {19, 19, 36, 255};
    constexpr static Color darkGrey = {39, 47, 52, 255};
    constexpr static Color lightBlue = {112, 146, 190, 255};

    constexpr static Color green    = {34, 177, 76, 255};
    constexpr static Color red      = {209, 71, 92, 255};
    constexpr static Color orange   = {255, 140, 64, 255};
    constexpr static Color yellow   = {253, 240, 0, 255};
    constexpr static Color purple   = {186, 103, 186, 255};
    constexpr static Color cyan     = {83, 225, 251, 255};
    constexpr static Color blue     = {85, 126, 202, 255};

    constexpr static Color green_shade  = {30, 138, 54, 255};
    constexpr static Color red_shade    = {164, 40, 58, 255};
    constexpr static Color orange_shade = {191, 102, 12, 255};
    constexpr static Color yellow_shade = {213, 177, 36, 255};
    constexpr static Color purple_shade = {149, 66, 149, 255};
    constexpr static Color cyan_shade   = {5, 189, 209, 255};
    constexpr static Color blue_shade   = {49, 85, 153, 255};


    constexpr static std::array <Color,8> _colors = {darkBlue, green, red, orange, yellow, purple, cyan, blue};
    constexpr static std::array <Color,8> _colors_shade = {darkBlue, green_shade,
                                                                     red_shade,
                                                                     orange_shade,
                                                                     yellow_shade,
                                                                     purple_shade,
                                                                     cyan_shade,
                                                                     blue_shade};
}