#pragma once
#include <core/drawable_object.h>
#include <memory>

class SpriteGraphicGenerator
{
public:
    static std::unique_ptr <IDrawableObject> GetXBoxButtonX();
    static std::unique_ptr <IDrawableObject> GetXBoxButtonY();

    static std::unique_ptr <IDrawableObject> GetLetterT (const Color& mainColor, const Color& shadeColor);
    static std::unique_ptr <IDrawableObject> GetLetterE (const Color& mainColor, const Color& shadeColor);
    static std::unique_ptr <IDrawableObject> GetLetterR (const Color& mainColor, const Color& shadeColor);
    static std::unique_ptr <IDrawableObject> GetLetterI (const Color& mainColor, const Color& shadeColor);
    static std::unique_ptr <IDrawableObject> GetLetterS (const Color& mainColor, const Color& shadeColor);

};