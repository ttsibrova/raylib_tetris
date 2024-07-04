#pragma once
#include <graphics/drawable_object.h>
#include <memory>
#include <string>

class DecorativeBlock;
class DrawableContainer;

class SpriteGraphicGenerator
{
public:
    static DrawableContainer* GetXBoxButton (GamepadButton button, float height);

    static DrawableContainer* GetXBoxButtonX (float radius);
    static DrawableContainer* GetXBoxButtonY (float radius);
    static DrawableContainer* GetXBoxButtonA (float radius);
    static DrawableContainer* GetXBoxButtonB (float radius);
    static DrawableContainer* GetXBoxUP (float radius);
    static DrawableContainer* GetXBoxDOWN (float radius);
    static DrawableContainer* GetXBoxLEFT (float radius);
    static DrawableContainer* GetXBoxRIGHT (float radius);
    static DrawableContainer* GetXBoxLB (float width);
    static DrawableContainer* GetXBoxRB (float width);
    static DrawableContainer* GetXBoxLT (float height);
    static DrawableContainer* GetXBoxRT (float height);

    static DrawableContainer* GetKeybordKey (KeyboardKey key, float size);

    static DecorativeBlock* GetBlockLetterT (int cellSize, const Color& mainColor, const Color& shadeColor);
    static DecorativeBlock* GetBlockLetterE (int cellSize, const Color& mainColor, const Color& shadeColor);
    static DecorativeBlock* GetBlockLetterR (int cellSize, const Color& mainColor, const Color& shadeColor);
    static DecorativeBlock* GetBlockLetterI (int cellSize, const Color& mainColor, const Color& shadeColor);
    static DecorativeBlock* GetBlockLetterS (int cellSize, const Color& mainColor, const Color& shadeColor);

    static DrawableContainer* GetButton (const std::string& text, float width);
    static DrawableContainer* GetButtonHover (const std::string& text, float width);
    static DrawableContainer* GetButtonPressed (const std::string& text, float width);

    static DecorativeBlock* GetMenuDecorativeBlock (int cellSize);
    static DecorativeBlock* GetMenuDecorativeBlockInversed (int cellSize);
};