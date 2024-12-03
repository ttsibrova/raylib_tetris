#include <graphics/sprites.h>

#include <graphics/colors.h>
#include <graphics/decorative_block.h>
#include <graphics/graphics_helper.h>

namespace dct = DrawableContainerTools;

DrawableContainer* SpriteGraphicGenerator::GetXBoxButton (GamepadButton button, float height)
{
    switch (button)
    {
    //case GAMEPAD_BUTTON_UNKNOWN:
    case GAMEPAD_BUTTON_LEFT_FACE_UP:
        return GetXBoxUP (height/2);
    case GAMEPAD_BUTTON_LEFT_FACE_RIGHT: 
        return GetXBoxRIGHT (height/2);
    case GAMEPAD_BUTTON_LEFT_FACE_DOWN:  
        return GetXBoxDOWN (height/2);
    case GAMEPAD_BUTTON_LEFT_FACE_LEFT:  
        return GetXBoxLEFT (height/2);
    case GAMEPAD_BUTTON_RIGHT_FACE_UP:
        return GetXBoxButtonY (height / 2);
    case GAMEPAD_BUTTON_RIGHT_FACE_RIGHT:
        return GetXBoxButtonB (height / 2);
    case GAMEPAD_BUTTON_RIGHT_FACE_DOWN: 
        return GetXBoxButtonA (height / 2);
    case GAMEPAD_BUTTON_RIGHT_FACE_LEFT: 
        return GetXBoxButtonX (height / 2);
    case GAMEPAD_BUTTON_LEFT_TRIGGER_1:
        return GetXBoxLB (height * 1.3);
    case GAMEPAD_BUTTON_LEFT_TRIGGER_2:  
        return GetXBoxLT (height * 1.3);
    case GAMEPAD_BUTTON_RIGHT_TRIGGER_1: 
        return GetXBoxRB (height * 1.3);
    case GAMEPAD_BUTTON_RIGHT_TRIGGER_2: 
        return GetXBoxRT (height * 1.3);
    case GAMEPAD_BUTTON_MIDDLE_LEFT:     
    case GAMEPAD_BUTTON_MIDDLE:          
    case GAMEPAD_BUTTON_MIDDLE_RIGHT:    
    case GAMEPAD_BUTTON_LEFT_THUMB:      
    case GAMEPAD_BUTTON_RIGHT_THUMB:
    default:
        break;
    }
    auto empty = new DrawableContainer();
    return empty;
}

DrawableContainer* SpriteGraphicGenerator::GetXBoxButtonX (float radius)
{
    auto cont = new DrawableContainer();
    auto r = dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, radius * 2, radius * 2, {0, 0, 0, 0});
    r->SetInvisible();
    dct::AddCircle (*cont, {0, 0}, DrawPosition::Center, radius, Colors::blue);
    dct::AddCircle (*cont, {0, 0}, DrawPosition::Center, radius * 0.9 , BLACK);
    dct::AddText (*cont, {0, 0}, DrawPosition::Center, "X", (int) radius * 1.5 , Colors::blue);
    return cont;
}

DrawableContainer* SpriteGraphicGenerator::GetXBoxButtonY (float radius)
{
    auto cont = new DrawableContainer();
    auto r = dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, radius * 2, radius * 2, {0, 0, 0, 0});
    r->SetInvisible();
    dct::AddCircle (*cont, {0, 0}, DrawPosition::Center, radius, Colors::yellow);
    dct::AddCircle (*cont, {0, 0}, DrawPosition::Center, radius * 0.9 , BLACK);
    dct::AddText (*cont, {0, 0}, DrawPosition::Center, "Y", (int) radius * 1.5 , Colors::yellow);
    return cont;
}

DrawableContainer* SpriteGraphicGenerator::GetXBoxButtonA (float radius)
{
    auto cont = new DrawableContainer();
    auto r = dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, radius * 2, radius * 2, {0, 0, 0, 0});
    r->SetInvisible();
    dct::AddCircle (*cont, {0, 0}, DrawPosition::Center, radius, Colors::green);
    dct::AddCircle (*cont, {0, 0}, DrawPosition::Center, radius * 0.9 , BLACK);
    dct::AddText (*cont, {0, 0}, DrawPosition::Center, "A", (int) radius * 1.5 , Colors::green);
    return cont;
}

DrawableContainer* SpriteGraphicGenerator::GetXBoxButtonB (float radius)
{
    auto cont = new DrawableContainer();
    auto r = dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, radius * 2, radius * 2, {0, 0, 0, 0});
    r->SetInvisible();
    dct::AddCircle (*cont, {0, 0}, DrawPosition::Center, radius, Colors::red);
    dct::AddCircle (*cont, {0, 0}, DrawPosition::Center, radius * 0.9 , BLACK);
    dct::AddText (*cont, {0, 0}, DrawPosition::Center, "B", (int) radius * 1.5 , Colors::red);
    return cont;
}

DrawableContainer* SpriteGraphicGenerator::GetXBoxUP (float radius)
{
    auto cont = new DrawableContainer();
    auto r = dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, radius * 2, radius * 2, {0, 0, 0, 0});
    r->SetInvisible();
    dct::AddCircle (*cont, {0, 0}, DrawPosition::Center, radius, RAYWHITE);
    dct::AddCircle (*cont, {0, 0}, DrawPosition::Center, radius * 0.9 , BLACK);
    dct::AddRectangle (*cont, {0, 0}, DrawPosition::Center, radius * 1.5, radius * 0.6, RAYWHITE);
    dct::AddRectangle (*cont, {0, 0}, DrawPosition::Center, radius * 0.6, radius * 1.5, RAYWHITE);
    auto rectangleVert = dct::AddRectangle (*cont, {0, 0}, DrawPosition::Center, radius * 1.4, radius * 0.5, BLACK);
    dct::AddRectangle (*cont, {0, 0}, DrawPosition::Center, radius * 0.5, radius * 1.4, BLACK);

    auto bbox = rectangleVert->GetBoundingBox();
    dct::AddRectangle (*cont, bbox.Min(), DrawPosition::TopLeft, radius * 0.45, radius * 0.5, RAYWHITE);

    return cont;
}

DrawableContainer* SpriteGraphicGenerator::GetXBoxDOWN (float radius)
{
    auto cont = new DrawableContainer();
    auto r = dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, radius * 2, radius * 2, {0, 0, 0, 0});
    r->SetInvisible();
    dct::AddCircle (*cont, {0, 0}, DrawPosition::Center, radius, RAYWHITE);
    dct::AddCircle (*cont, {0, 0}, DrawPosition::Center, radius * 0.9 , BLACK);
    dct::AddRectangle (*cont, {0, 0}, DrawPosition::Center, radius * 1.5, radius * 0.6, RAYWHITE);
    dct::AddRectangle (*cont, {0, 0}, DrawPosition::Center, radius * 0.6, radius * 1.5, RAYWHITE);
    auto rectangleVert = dct::AddRectangle (*cont, {0, 0}, DrawPosition::Center, radius * 1.4, radius * 0.5, BLACK);
    dct::AddRectangle (*cont, {0, 0}, DrawPosition::Center, radius * 0.5, radius * 1.4, BLACK);

    auto bbox = rectangleVert->GetBoundingBox();
    dct::AddRectangle (*cont, bbox.Max(), DrawPosition::BottomRight, radius * 0.45, radius * 0.5, RAYWHITE);

    return cont;
}

DrawableContainer* SpriteGraphicGenerator::GetXBoxLEFT (float radius)
{
    auto cont = new DrawableContainer();
    auto r = dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, radius * 2, radius * 2, {0, 0, 0, 0});
    r->SetInvisible();
    dct::AddCircle (*cont, {0, 0}, DrawPosition::Center, radius, RAYWHITE);
    dct::AddCircle (*cont, {0, 0}, DrawPosition::Center, radius * 0.9, BLACK);
    dct::AddRectangle (*cont, {0, 0}, DrawPosition::Center, radius * 1.5, radius * 0.6, RAYWHITE);
    dct::AddRectangle (*cont, {0, 0}, DrawPosition::Center, radius * 0.6, radius * 1.5, RAYWHITE);
    dct::AddRectangle (*cont, {0, 0}, DrawPosition::Center, radius * 1.4, radius * 0.5, BLACK);
    auto rectangleHor = dct::AddRectangle (*cont, {0, 0}, DrawPosition::Center, radius * 0.5, radius * 1.4, BLACK);

    auto bbox = rectangleHor->GetBoundingBox();
    dct::AddRectangle (*cont, bbox.Min(), DrawPosition::TopLeft, radius * 0.5, radius * 0.45, RAYWHITE);

    return cont;
}

DrawableContainer* SpriteGraphicGenerator::GetXBoxRIGHT (float radius)
{
    auto cont = new DrawableContainer();
    auto r = dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, radius * 2, radius * 2, {0, 0, 0, 0});
    r->SetInvisible();
    dct::AddCircle (*cont, {0, 0}, DrawPosition::Center, radius, RAYWHITE);
    dct::AddCircle (*cont, {0, 0}, DrawPosition::Center, radius * 0.9, BLACK);
    dct::AddRectangle (*cont, {0, 0}, DrawPosition::Center, radius * 1.5, radius * 0.6, RAYWHITE);
    dct::AddRectangle (*cont, {0, 0}, DrawPosition::Center, radius * 0.6, radius * 1.5, RAYWHITE);
    dct::AddRectangle (*cont, {0, 0}, DrawPosition::Center, radius * 1.4, radius * 0.5, BLACK);
    auto rectangleHor = dct::AddRectangle (*cont, {0, 0}, DrawPosition::Center, radius * 0.5, radius * 1.4, BLACK);

    auto bbox = rectangleHor->GetBoundingBox();
    dct::AddRectangle (*cont, bbox.Max(), DrawPosition::BottomRight, radius * 0.5, radius * 0.45, RAYWHITE);

    return cont;
}

DrawableContainer* SpriteGraphicGenerator::GetXBoxLB (float width)
{
    auto cont = new DrawableContainer();
    auto r = dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, width, width, {0, 0, 0, 0});
    r->SetInvisible();
    dct::AddRectangleRounded (*cont, {0, 0}, DrawPosition::Center, width * 0.5, width, 0.6, RAYWHITE);
    auto rInt = dct::AddRectangleRounded (*cont, {0, 0}, DrawPosition::Center, width * 0.4, width * 0.9, 0.6, BLACK);
    auto bbox = rInt->GetBoundingBox();
    dct::AddText (*cont, {bbox.Max().x - bbox.Width() * 0.1f, bbox.Max().y - bbox.Height() / 2}, DrawPosition::Right, "LB", bbox.Height() * 0.85, RAYWHITE);

    return cont;
}

DrawableContainer* SpriteGraphicGenerator::GetXBoxRB (float width)
{
    auto cont = new DrawableContainer();
    auto r = dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, width, width, {0, 0, 0, 0});
    r->SetInvisible();
    dct::AddRectangleRounded (*cont, {0, 0}, DrawPosition::Center, width * 0.5, width, 0.6, RAYWHITE);
    auto rInt = dct::AddRectangleRounded (*cont, {0, 0}, DrawPosition::Center, width * 0.4, width * 0.9, 0.6, BLACK);
    auto bbox = rInt->GetBoundingBox();
    dct::AddText (*cont, {bbox.Min().x + bbox.Width() * 0.1f, bbox.Max().y - bbox.Height() / 2}, DrawPosition::Left, "RB", bbox.Height() * 0.85, RAYWHITE);

    return cont;
}

DrawableContainer* SpriteGraphicGenerator::GetXBoxLT (float height)
{
    auto cont = new DrawableContainer();
    auto r = dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, height, height, {0, 0, 0, 0});
    r->SetInvisible();
    dct::AddRectangleRounded (*cont, {0, 0}, DrawPosition::Center, height , height * 0.5, 0.6, RAYWHITE);
    auto rInt = dct::AddRectangleRounded (*cont, {0, 0}, DrawPosition::Center, height * 0.9, height * 0.4, 0.6, BLACK);
    auto bbox = rInt->GetBoundingBox();
    dct::AddText (*cont, {bbox.Min().x + bbox.Width() / 2, bbox.Max().y - bbox.Height() * 0.1f}, DrawPosition::Bottom, "LT", bbox.Width() * 0.65, RAYWHITE);

    return cont;
}

DrawableContainer* SpriteGraphicGenerator::GetXBoxRT (float height)
{
    auto cont = new DrawableContainer();
    auto r = dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, height, height, {0, 0, 0, 0});
    r->SetInvisible();
    dct::AddRectangleRounded (*cont, {0, 0}, DrawPosition::Center, height , height * 0.5, 0.6, RAYWHITE);
    auto rInt = dct::AddRectangleRounded (*cont, {0, 0}, DrawPosition::Center, height * 0.9, height * 0.4, 0.6, BLACK);
    auto bbox = rInt->GetBoundingBox();
    dct::AddText (*cont, {bbox.Min().x + bbox.Width() / 2, bbox.Max().y - bbox.Height() * 0.1f}, DrawPosition::Bottom, "RT", bbox.Width() * 0.65, RAYWHITE);

    return cont;
}

DrawableContainer* SpriteGraphicGenerator::GetKeybordKey (KeyboardKey key, float size)
{
    auto cont = new DrawableContainer();
    if (key > 38 && key < 91) {
        dct::AddRectangleRounded (*cont, {0., 0.}, DrawPosition::Top, size, size, 0.4, RAYWHITE);
        auto rInt = dct::AddRectangleRounded (*cont, {0., size * 0.08f}, DrawPosition::Top, size * 0.75, size * 0.9, 0.4, BLACK);
        auto bbox = rInt->GetBoundingBox();

        std::string ch (1, (char)key);
        dct::AddText (*cont, {bbox.Min().x + bbox.Width() * 0.2f, bbox.Min().y + bbox.Height() * 0.1f}, DrawPosition::TopLeft, ch, bbox.Height() * 0.6f, RAYWHITE);
    }

    std::string keyName;
    switch (key)
    {
    case KEY_ESCAPE:
    {
        dct::AddRectangleRounded (*cont, {0., 0.}, DrawPosition::Top, size, size, 0.4, RAYWHITE);
        auto rInt = dct::AddRectangleRounded (*cont, {0., size * 0.08f}, DrawPosition::Top, size * 0.75, size * 0.9, 0.4, BLACK);
        auto bbox = rInt->GetBoundingBox();

        dct::AddText (*cont, {bbox.Min().x + bbox.Width() * 0.1f, bbox.Min().y + bbox.Height() * 0.1f}, DrawPosition::TopLeft, "ESC", bbox.Height() * 0.45f, RAYWHITE);
        break;
    }
    case KEY_SPACE:
    {
        dct::AddRectangleRounded (*cont, {0., 0.}, DrawPosition::Top, size, size * 2, 0.4, RAYWHITE);
        auto rInt = dct::AddRectangleRounded (*cont, {0., size * 0.08f}, DrawPosition::Top, size * 0.75, size * 1.9, 0.4, BLACK);
        auto bbox = rInt->GetBoundingBox();

        dct::AddText (*cont, {bbox.Min().x + bbox.Width() * 0.5f, bbox.Min().y + bbox.Height() * 0.1f}, DrawPosition::Top, "SPACE", bbox.Height() * 0.45f, RAYWHITE);
        break;
    }
    case KEY_ENTER:
    {
        dct::AddRectangleRounded (*cont, {0., 0.}, DrawPosition::Top, size, size * 2, 0.4, RAYWHITE);
        auto rInt = dct::AddRectangleRounded (*cont, {0., size * 0.08f}, DrawPosition::Top, size * 0.75, size * 1.9, 0.4, BLACK);
        auto bbox = rInt->GetBoundingBox();

        dct::AddText (*cont, {bbox.Min().x + bbox.Width() * 0.5f, bbox.Min().y + bbox.Height() * 0.1f}, DrawPosition::Top, "ENTER", bbox.Height() * 0.45f, RAYWHITE);
        break;
    }
    case KEY_LEFT_ALT: case KEY_RIGHT_ALT:
        keyName = "ALT"; break;
    case KEY_TAB:
        keyName = "TAB"; break;
    case KEY_LEFT_SHIFT: case KEY_RIGHT_SHIFT:
        keyName = "SHIFT"; break;
    case KEY_CAPS_LOCK:
        keyName = "CAPS"; break;
    case KEY_LEFT_CONTROL: case KEY_RIGHT_CONTROL:
        keyName = "CTRL"; break;
    default:
        break;
    }

    if (!keyName.empty()) {
        dct::AddRectangleRounded (*cont, {0., 0.}, DrawPosition::Top, size, size * 1.6, 0.4, RAYWHITE);
        auto rInt = dct::AddRectangleRounded (*cont, {0., size * 0.08f}, DrawPosition::Top, size * 0.75, size * 1.5, 0.4, BLACK);
        auto bbox = rInt->GetBoundingBox();

        dct::AddText (*cont, {bbox.Min().x + bbox.Width() * 0.5f, bbox.Min().y + bbox.Height() * 0.1f}, DrawPosition::Top, keyName, bbox.Height() * 0.45f, RAYWHITE);
    }

    auto AddArrow = [] (float angle, float size, DrawableContainer* cont)
    {
        dct::AddRectangleRounded (*cont, {0., 0.}, DrawPosition::Top, size, size, 0.4, RAYWHITE);
        auto rInt = dct::AddRectangleRounded (*cont, {0., size * 0.08f}, DrawPosition::Top, size * 0.75, size * 0.9, 0.4, BLACK);
        auto bbox = rInt->GetBoundingBox();
        Vector2 pos {bbox.Min().x + bbox.Width() * 0.5f, bbox.Min().y + bbox.Height() * 0.5f};

        dct::AddTriangle (*cont, pos, DrawPosition::Center, bbox.Height() * 0.5f, angle, RAYWHITE);
    };

    switch (key)
    {
    case KEY_UP:
        AddArrow (-90.f, size, cont);
        break;
    case KEY_DOWN:
        AddArrow (90.f, size, cont);
        break;
    case KEY_RIGHT:
        AddArrow (0.f, size, cont);
        break;
    case KEY_LEFT:
        AddArrow (180.f, size, cont);
        break;
    default:
        break;
    }

    Vector2 currCenter = GraphicsHelper::ComputePosition (DrawPosition::Center, cont->GetBoundingBox());
    cont->Translate (GraphicsHelper::ComputeTranslation (currCenter, {0., 0.}));
    return cont;
}

DecorativeBlock* SpriteGraphicGenerator::GetBlockLetterT (int cellSize, const Color& mainColor, const Color& shadeColor)
{
    auto block = new DecorativeBlock (cellSize);
    block->AddCell ({0, 0}, mainColor, shadeColor);
    block->AddCell ({0, 1}, mainColor, shadeColor);
    block->AddCell ({0, 2}, mainColor, shadeColor);
    block->AddCell ({1, 1}, mainColor, shadeColor);
    block->AddCell ({2, 1}, mainColor, shadeColor);
    block->AddCell ({3, 1}, mainColor, shadeColor);
    block->AddCell ({4, 1}, mainColor, shadeColor);

    block->SetOutline (RAYWHITE, cellSize/7);
    return block;
}

DecorativeBlock* SpriteGraphicGenerator::GetBlockLetterE (int cellSize, const Color& mainColor, const Color& shadeColor)
{
    auto block = new DecorativeBlock (cellSize);
    block->AddCell ({0, 0}, mainColor, shadeColor);
    block->AddCell ({0, 1}, mainColor, shadeColor);
    block->AddCell ({0, 2}, mainColor, shadeColor);
    block->AddCell ({4, 0}, mainColor, shadeColor);
    block->AddCell ({4, 1}, mainColor, shadeColor);
    block->AddCell ({4, 2}, mainColor, shadeColor);
    block->AddCell ({1, 0}, mainColor, shadeColor);
    block->AddCell ({2, 0}, mainColor, shadeColor);
    block->AddCell ({3, 0}, mainColor, shadeColor);
    block->AddCell ({2, 1}, mainColor, shadeColor);

    block->SetOutline (RAYWHITE, cellSize / 7);
    return block;
}

DecorativeBlock* SpriteGraphicGenerator::GetBlockLetterR (int cellSize, const Color& mainColor, const Color& shadeColor)
{
    auto block = new DecorativeBlock (cellSize);
    block->AddCell ({0, 0}, mainColor, shadeColor);
    block->AddCell ({0, 1}, mainColor, shadeColor);
    block->AddCell ({0, 2}, mainColor, shadeColor);
    block->AddCell ({1, 0}, mainColor, shadeColor);
    block->AddCell ({2, 0}, mainColor, shadeColor);
    block->AddCell ({3, 0}, mainColor, shadeColor);
    block->AddCell ({4, 0}, mainColor, shadeColor);
    block->AddCell ({1, 2}, mainColor, shadeColor);
    block->AddCell ({2, 1}, mainColor, shadeColor);
    block->AddCell ({3, 2}, mainColor, shadeColor);
    block->AddCell ({4, 2}, mainColor, shadeColor);

    block->SetOutline (RAYWHITE, cellSize / 7);
    return block;
}

DecorativeBlock* SpriteGraphicGenerator::GetBlockLetterI (int cellSize, const Color& mainColor, const Color& shadeColor)
{
    auto block = new DecorativeBlock (cellSize);
    block->AddCell ({0, 0}, mainColor, shadeColor);
    block->AddCell ({1, 0}, mainColor, shadeColor);
    block->AddCell ({2, 0}, mainColor, shadeColor);
    block->AddCell ({3, 0}, mainColor, shadeColor);
    block->AddCell ({4, 0}, mainColor, shadeColor);

    block->SetOutline (RAYWHITE, cellSize / 7);
    return block;
}

DecorativeBlock* SpriteGraphicGenerator::GetBlockLetterS (int cellSize, const Color& mainColor, const Color& shadeColor)
{
    auto block = new DecorativeBlock (cellSize);
    block->AddCell ({0, 0}, mainColor, shadeColor);
    block->AddCell ({0, 1}, mainColor, shadeColor);
    block->AddCell ({0, 2}, mainColor, shadeColor);
    block->AddCell ({1, 0}, mainColor, shadeColor);
    block->AddCell ({2, 0}, mainColor, shadeColor);
    block->AddCell ({2, 1}, mainColor, shadeColor);
    block->AddCell ({2, 2}, mainColor, shadeColor);
    block->AddCell ({3, 2}, mainColor, shadeColor);
    block->AddCell ({4, 0}, mainColor, shadeColor);
    block->AddCell ({4, 1}, mainColor, shadeColor);
    block->AddCell ({4, 2}, mainColor, shadeColor);

    block->SetOutline (RAYWHITE, cellSize / 7);
    return block;
}

DrawableContainer* SpriteGraphicGenerator::GetButton (const std::string& text, float width)
{
    auto cont = new DrawableContainer();

    dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, width * 0.25, width, {72, 88, 130, 255});
    dct::AddText (*cont, {0., 0.}, DrawPosition::Center, text, width * 0.15, RAYWHITE);

    return cont;
}

DrawableContainer* SpriteGraphicGenerator::GetButtonHover (const std::string& text, float width)
{
    auto cont = new DrawableContainer();

    dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, width * 0.3, width * 1.05, RAYWHITE);
    dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, width * 0.25, width, {72, 88, 130, 255});
    dct::AddText (*cont, {0., 0.}, DrawPosition::Center, text, width * 0.15, RAYWHITE);

    return cont;
}

DrawableContainer* SpriteGraphicGenerator::GetButtonPressed (const std::string& text, float width)
{
    auto cont = new DrawableContainer();
    Color shadedPressed {53, 74, 115,  255};
    Color shade {33, 40, 58, 255};

    dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, width * 0.3, width * 1.05, RAYWHITE);
    dct::AddRectangle (*cont, {0., 0.}, DrawPosition::Center, width * 0.25, width, shade);
    dct::AddRectangle (*cont, {0., width * 0.02f}, DrawPosition::Center, width * 0.21, width * 0.97, shadedPressed);
    dct::AddText (*cont, {0., 0.}, DrawPosition::Center, text, width * 0.15, RAYWHITE);

    return cont;
}

DecorativeBlock* SpriteGraphicGenerator::GetMenuDecorativeBlock (int cellSize)
{
    auto block = new DecorativeBlock (cellSize);
    block->AddCell ({0, 1}, Colors::blue, Colors::blue_shade);
    block->AddCell ({0, 4}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({0, 5}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({1, 0}, Colors::blue, Colors::blue_shade);
    block->AddCell ({1, 1}, Colors::blue, Colors::blue_shade);
    block->AddCell ({1, 3}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({1, 4}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({1, 5}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({2, 0}, Colors::blue, Colors::blue_shade);
    block->AddCell ({2, 1}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({2, 2}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({2, 3}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({2, 4}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({2, 5}, Colors::green, Colors::green_shade);
    block->AddCell ({2, 6}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({2, 7}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({3, 0}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({3, 1}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({3, 2}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({3, 3}, Colors::green, Colors::green_shade);
    block->AddCell ({3, 4}, Colors::green, Colors::green_shade);
    block->AddCell ({3, 5}, Colors::green, Colors::green_shade);
    block->AddCell ({3, 6}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({3, 7}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({4, 0}, Colors::red, Colors::red_shade);
    block->AddCell ({4, 1}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({4, 2}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({4, 3}, Colors::purple, Colors::purple_shade);
    block->AddCell ({4, 4}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({4, 5}, Colors::orange, Colors::orange_shade);
    block->AddCell ({4, 6}, Colors::orange, Colors::orange_shade);
    block->AddCell ({4, 7}, Colors::red, Colors::red_shade);
    block->AddCell ({4, 8}, Colors::red, Colors::red_shade);
    block->AddCell ({5, 0}, Colors::orange, Colors::orange_shade);
    block->AddCell ({5, 1}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({5, 2}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({5, 3}, Colors::purple, Colors::purple_shade);
    block->AddCell ({5, 4}, Colors::purple, Colors::purple_shade);
    block->AddCell ({5, 5}, Colors::orange, Colors::orange_shade);
    block->AddCell ({5, 6}, Colors::orange, Colors::orange_shade);
    block->AddCell ({5, 7}, Colors::red, Colors::red_shade);
    block->AddCell ({5, 8}, Colors::red, Colors::red_shade);

    return block;
}

DecorativeBlock* SpriteGraphicGenerator::GetMenuDecorativeBlockInversed (int cellSize)
{
    auto block = new DecorativeBlock (cellSize);
    block->AddCell ({0, 7}, Colors::blue, Colors::blue_shade);
    block->AddCell ({0, 4}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({0, 3}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({1, 8}, Colors::blue, Colors::blue_shade);
    block->AddCell ({1, 7}, Colors::blue, Colors::blue_shade);
    block->AddCell ({1, 5}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({1, 4}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({1, 3}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({2, 9}, Colors::orange, Colors::orange_shade);
    block->AddCell ({2, 8}, Colors::blue, Colors::blue_shade);
    block->AddCell ({2, 7}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({2, 6}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({2, 5}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({2, 4}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({2, 3}, Colors::green, Colors::green_shade);
    block->AddCell ({2, 2}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({2, 1}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({3, 9}, Colors::orange, Colors::orange_shade);
    block->AddCell ({3, 8}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({3, 7}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({3, 6}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({3, 5}, Colors::green, Colors::green_shade);
    block->AddCell ({3, 4}, Colors::green, Colors::green_shade);
    block->AddCell ({3, 3}, Colors::green, Colors::green_shade);
    block->AddCell ({3, 2}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({3, 1}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({4, 9}, Colors::red, Colors::red_shade);
    block->AddCell ({4, 8}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({4, 7}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({4, 6}, Colors::purple, Colors::purple_shade);
    block->AddCell ({4, 5}, Colors::cyan, Colors::cyan_shade);
    block->AddCell ({4, 4}, Colors::orange, Colors::orange_shade);
    block->AddCell ({4, 3}, Colors::orange, Colors::orange_shade);
    block->AddCell ({4, 2}, Colors::red, Colors::red_shade);
    block->AddCell ({4, 1}, Colors::red, Colors::red_shade);
    block->AddCell ({4, 0}, Colors::purple, Colors::purple_shade);
    block->AddCell ({5, 9}, Colors::orange, Colors::orange_shade);
    block->AddCell ({5, 8}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({5, 7}, Colors::yellow, Colors::yellow_shade);
    block->AddCell ({5, 6}, Colors::purple, Colors::purple_shade);
    block->AddCell ({5, 5}, Colors::purple, Colors::purple_shade);
    block->AddCell ({5, 4}, Colors::orange, Colors::orange_shade);
    block->AddCell ({5, 3}, Colors::orange, Colors::orange_shade);
    block->AddCell ({5, 2}, Colors::red, Colors::red_shade);
    block->AddCell ({5, 1}, Colors::red, Colors::red_shade);
    block->AddCell ({5, 0}, Colors::purple, Colors::purple_shade);

    return block;
}


