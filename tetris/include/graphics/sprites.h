#pragma once
#include <graphics/drawable_object.h>
#include <memory>

class SpriteGraphicGenerator
{
public:
    static std::unique_ptr <DrawableObject> GetXBoxButtonX();
    static std::unique_ptr <DrawableObject> GetXBoxButtonY();

    static std::unique_ptr <DrawableObject> GetLetterT (const Color& mainColor, const Color& shadeColor);
    static std::unique_ptr <DrawableObject> GetLetterE (const Color& mainColor, const Color& shadeColor);
    static std::unique_ptr <DrawableObject> GetLetterR (const Color& mainColor, const Color& shadeColor);
    static std::unique_ptr <DrawableObject> GetLetterI (const Color& mainColor, const Color& shadeColor);
    static std::unique_ptr <DrawableObject> GetLetterS (const Color& mainColor, const Color& shadeColor);

};