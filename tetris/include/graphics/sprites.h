#pragma once
#include <graphics/drawable_object.h>
#include <memory>
#include <string>

class SpriteGraphicGenerator
{
public:
    static std::unique_ptr <DrawableObject> GetXBoxButtonX (float radius);
    static std::unique_ptr <DrawableObject> GetXBoxButtonY (float radius);
    static std::unique_ptr <DrawableObject> GetXBoxButtonA (float radius);
    static std::unique_ptr <DrawableObject> GetXBoxButtonB (float radius);
    static std::unique_ptr <DrawableObject> GetXBoxUP (float radius);
    static std::unique_ptr <DrawableObject> GetXBoxDOWN (float radius);
    static std::unique_ptr <DrawableObject> GetXBoxLEFT (float radius);
    static std::unique_ptr <DrawableObject> GetXBoxRIGHT (float radius);
    static std::unique_ptr <DrawableObject> GetXBoxLB (float width);
    static std::unique_ptr <DrawableObject> GetXBoxRB (float width);
    static std::unique_ptr <DrawableObject> GetXBoxLT (float height);
    static std::unique_ptr <DrawableObject> GetXBoxRT (float height);

    static std::unique_ptr <DrawableObject> GetKeybordKey (KeyboardKey key, float size);

    static std::unique_ptr <DrawableObject> GetBlockLetterT (int cellSize, const Color& mainColor, const Color& shadeColor);
    static std::unique_ptr <DrawableObject> GetBlockLetterE (int cellSize, const Color& mainColor, const Color& shadeColor);
    static std::unique_ptr <DrawableObject> GetBlockLetterR (int cellSize, const Color& mainColor, const Color& shadeColor);
    static std::unique_ptr <DrawableObject> GetBlockLetterI (int cellSize, const Color& mainColor, const Color& shadeColor);
    static std::unique_ptr <DrawableObject> GetBlockLetterS (int cellSize, const Color& mainColor, const Color& shadeColor);

    static std::unique_ptr <DrawableObject> GetButton (const std::string& text, float width);
    static std::unique_ptr <DrawableObject> GetButtonHover (const std::string& text, float width);
    static std::unique_ptr <DrawableObject> GetButtonPressed (const std::string& text, float width);
};