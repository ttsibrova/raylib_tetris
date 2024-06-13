#pragma once
#include <graphics/drawable_object.h>
#include <memory>
#include <string>

class SpriteGraphicGenerator
{
public:
    static DrawableObject* GetXBoxButton (GamepadButton button, float height);

    static DrawableObject* GetXBoxButtonX (float radius);
    static DrawableObject* GetXBoxButtonY (float radius);
    static DrawableObject* GetXBoxButtonA (float radius);
    static DrawableObject* GetXBoxButtonB (float radius);
    static DrawableObject* GetXBoxUP (float radius);
    static DrawableObject* GetXBoxDOWN (float radius);
    static DrawableObject* GetXBoxLEFT (float radius);
    static DrawableObject* GetXBoxRIGHT (float radius);
    static DrawableObject* GetXBoxLB (float width);
    static DrawableObject* GetXBoxRB (float width);
    static DrawableObject* GetXBoxLT (float height);
    static DrawableObject* GetXBoxRT (float height);

    static DrawableObject* GetKeybordKey (KeyboardKey key, float size);

    static DrawableObject* GetBlockLetterT (int cellSize, const Color& mainColor, const Color& shadeColor);
    static DrawableObject* GetBlockLetterE (int cellSize, const Color& mainColor, const Color& shadeColor);
    static DrawableObject* GetBlockLetterR (int cellSize, const Color& mainColor, const Color& shadeColor);
    static DrawableObject* GetBlockLetterI (int cellSize, const Color& mainColor, const Color& shadeColor);
    static DrawableObject* GetBlockLetterS (int cellSize, const Color& mainColor, const Color& shadeColor);

    static DrawableObject* GetButton (const std::string& text, float width);
    static DrawableObject* GetButtonHover (const std::string& text, float width);
    static DrawableObject* GetButtonPressed (const std::string& text, float width);

    static DrawableObject* GetMenuDecorativeBlock (int cellSize);
    static DrawableObject* GetMenuDecorativeBlockInversed (int cellSize);
};