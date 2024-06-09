#include <graphics/sprites.h>

#include <graphics/colors.h>
#include <graphics/decorative_block.h>

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetXBoxButtonX (float radius)
{
    auto cont = std::make_unique <DrawableContainer>();
    cont->AddCircle ({0, 0}, DrawPosition::Center, radius, Colors::blue);
    cont->AddCircle ({0, 0}, DrawPosition::Center, radius * 0.9 , BLACK);
    cont->AddText ({0, 0}, DrawPosition::Center, "X", (int) radius * 1.5 , Colors::blue);
    return cont;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetXBoxButtonY (float radius)
{
    auto cont = std::make_unique <DrawableContainer>();
    cont->AddCircle ({0, 0}, DrawPosition::Center, radius, Colors::yellow);
    cont->AddCircle ({0, 0}, DrawPosition::Center, radius * 0.9 , BLACK);
    cont->AddText ({0, 0}, DrawPosition::Center, "Y", (int) radius * 1.5 , Colors::yellow);
    return cont;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetXBoxButtonA (float radius)
{
    auto cont = std::make_unique <DrawableContainer>();
    cont->AddCircle ({0, 0}, DrawPosition::Center, radius, Colors::green);
    cont->AddCircle ({0, 0}, DrawPosition::Center, radius * 0.9 , BLACK);
    cont->AddText ({0, 0}, DrawPosition::Center, "A", (int) radius * 1.5 , Colors::green);
    return cont;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetXBoxButtonB (float radius)
{
    auto cont = std::make_unique <DrawableContainer>();
    cont->AddCircle ({0, 0}, DrawPosition::Center, radius, Colors::red);
    cont->AddCircle ({0, 0}, DrawPosition::Center, radius * 0.9 , BLACK);
    cont->AddText ({0, 0}, DrawPosition::Center, "B", (int) radius * 1.5 , Colors::red);
    return cont;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetXBoxUP (float radius)
{
    auto cont = std::make_unique <DrawableContainer>();
    cont->AddCircle ({0, 0}, DrawPosition::Center, radius, RAYWHITE);
    cont->AddCircle ({0, 0}, DrawPosition::Center, radius * 0.9 , BLACK);
    cont->AddRectangle ({0, 0}, DrawPosition::Center, radius * 1.5, radius * 0.6, RAYWHITE);
    cont->AddRectangle ({0, 0}, DrawPosition::Center, radius * 0.6, radius * 1.5, RAYWHITE);
    auto rectangleVert = cont->AddRectangle ({0, 0}, DrawPosition::Center, radius * 1.4, radius * 0.5, BLACK);
    cont->AddRectangle ({0, 0}, DrawPosition::Center, radius * 0.5, radius * 1.4, BLACK);

    auto bbox = rectangleVert->GetBoundingBox();
    cont->AddRectangle (bbox.Min(), DrawPosition::TopLeft, radius * 0.45, radius * 0.5, RAYWHITE);

    return cont;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetXBoxDOWN (float radius)
{
    auto cont = std::make_unique <DrawableContainer>();
    cont->AddCircle ({0, 0}, DrawPosition::Center, radius, RAYWHITE);
    cont->AddCircle ({0, 0}, DrawPosition::Center, radius * 0.9 , BLACK);
    cont->AddRectangle ({0, 0}, DrawPosition::Center, radius * 1.5, radius * 0.6, RAYWHITE);
    cont->AddRectangle ({0, 0}, DrawPosition::Center, radius * 0.6, radius * 1.5, RAYWHITE);
    auto rectangleVert = cont->AddRectangle ({0, 0}, DrawPosition::Center, radius * 1.4, radius * 0.5, BLACK);
    cont->AddRectangle ({0, 0}, DrawPosition::Center, radius * 0.5, radius * 1.4, BLACK);

    auto bbox = rectangleVert->GetBoundingBox();
    cont->AddRectangle (bbox.Max(), DrawPosition::BottomRight, radius * 0.45, radius * 0.5, RAYWHITE);

    return cont;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetXBoxLEFT (float radius)
{
    auto cont = std::make_unique <DrawableContainer>();
    cont->AddCircle ({0, 0}, DrawPosition::Center, radius, RAYWHITE);
    cont->AddCircle ({0, 0}, DrawPosition::Center, radius * 0.9, BLACK);
    cont->AddRectangle ({0, 0}, DrawPosition::Center, radius * 1.5, radius * 0.6, RAYWHITE);
    cont->AddRectangle ({0, 0}, DrawPosition::Center, radius * 0.6, radius * 1.5, RAYWHITE);
    cont->AddRectangle ({0, 0}, DrawPosition::Center, radius * 1.4, radius * 0.5, BLACK);
    auto rectangleHor = cont->AddRectangle ({0, 0}, DrawPosition::Center, radius * 0.5, radius * 1.4, BLACK);

    auto bbox = rectangleHor->GetBoundingBox();
    cont->AddRectangle (bbox.Min(), DrawPosition::TopLeft, radius * 0.5, radius * 0.45, RAYWHITE);

    return cont;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetXBoxRIGHT (float radius)
{
    auto cont = std::make_unique <DrawableContainer>();
    cont->AddCircle ({0, 0}, DrawPosition::Center, radius, RAYWHITE);
    cont->AddCircle ({0, 0}, DrawPosition::Center, radius * 0.9, BLACK);
    cont->AddRectangle ({0, 0}, DrawPosition::Center, radius * 1.5, radius * 0.6, RAYWHITE);
    cont->AddRectangle ({0, 0}, DrawPosition::Center, radius * 0.6, radius * 1.5, RAYWHITE);
    cont->AddRectangle ({0, 0}, DrawPosition::Center, radius * 1.4, radius * 0.5, BLACK);
    auto rectangleHor = cont->AddRectangle ({0, 0}, DrawPosition::Center, radius * 0.5, radius * 1.4, BLACK);

    auto bbox = rectangleHor->GetBoundingBox();
    cont->AddRectangle (bbox.Max(), DrawPosition::BottomRight, radius * 0.5, radius * 0.45, RAYWHITE);

    return cont;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetXBoxLB (float width)
{
    auto cont = std::make_unique <DrawableContainer>();
    cont->AddRectangleRounded ({0, 0}, DrawPosition::Center, width * 0.5, width, 0.6, RAYWHITE);
    auto rInt = cont->AddRectangleRounded ({0, 0}, DrawPosition::Center, width * 0.4, width * 0.9, 0.6, BLACK);
    auto bbox = rInt->GetBoundingBox();
    cont->AddText ({bbox.Max().x - bbox.Width() * 0.1f, bbox.Max().y - bbox.Height() / 2}, DrawPosition::Right, "LB", bbox.Height() * 0.85, RAYWHITE);

    return cont;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetXBoxRB (float width)
{
    auto cont = std::make_unique <DrawableContainer>();
    cont->AddRectangleRounded ({0, 0}, DrawPosition::Center, width * 0.5, width, 0.6, RAYWHITE);
    auto rInt = cont->AddRectangleRounded ({0, 0}, DrawPosition::Center, width * 0.4, width * 0.9, 0.6, BLACK);
    auto bbox = rInt->GetBoundingBox();
    cont->AddText ({bbox.Min().x + bbox.Width() * 0.1f, bbox.Max().y - bbox.Height() / 2}, DrawPosition::Left, "RB", bbox.Height() * 0.85, RAYWHITE);

    return cont;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetXBoxLT (float height)
{
    auto cont = std::make_unique <DrawableContainer>();
    cont->AddRectangleRounded ({0, 0}, DrawPosition::Center, height , height * 0.5, 0.6, RAYWHITE);
    auto rInt = cont->AddRectangleRounded ({0, 0}, DrawPosition::Center, height * 0.9, height * 0.4, 0.6, BLACK);
    auto bbox = rInt->GetBoundingBox();
    cont->AddText ({bbox.Min().x + bbox.Width() / 2, bbox.Max().y - bbox.Height() * 0.1f}, DrawPosition::Bottom, "LT", bbox.Width() * 0.65, RAYWHITE);

    return cont;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetXBoxRT (float height)
{
    auto cont = std::make_unique <DrawableContainer>();
    cont->AddRectangleRounded ({0, 0}, DrawPosition::Center, height , height * 0.5, 0.6, RAYWHITE);
    auto rInt = cont->AddRectangleRounded ({0, 0}, DrawPosition::Center, height * 0.9, height * 0.4, 0.6, BLACK);
    auto bbox = rInt->GetBoundingBox();
    cont->AddText ({bbox.Min().x + bbox.Width() / 2, bbox.Max().y - bbox.Height() * 0.1f}, DrawPosition::Bottom, "RT", bbox.Width() * 0.65, RAYWHITE);

    return cont;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetKeybordKey (KeyboardKey key, float size)
{
    auto cont = std::make_unique <DrawableContainer>();
    if (key > 38 && key < 91) {
        cont->AddRectangleRounded ({0., 0.}, DrawPosition::Top, size, size, 0.4, RAYWHITE);
        auto rInt = cont->AddRectangleRounded ({0., size * 0.08f}, DrawPosition::Top, size * 0.75, size * 0.9, 0.4, BLACK);
        auto bbox = rInt->GetBoundingBox();

        std::string ch (1, (char)key);
        cont->AddText ({bbox.Min().x + bbox.Width() * 0.2f, bbox.Min().y + bbox.Height() * 0.1f}, DrawPosition::TopLeft, ch, bbox.Height() * 0.6f, RAYWHITE);
    }

    std::string keyName;
    switch (key)
    {
    case KEY_ESCAPE:
    {
        cont->AddRectangleRounded ({0., 0.}, DrawPosition::Top, size, size, 0.4, RAYWHITE);
        auto rInt = cont->AddRectangleRounded ({0., size * 0.08f}, DrawPosition::Top, size * 0.75, size * 0.9, 0.4, BLACK);
        auto bbox = rInt->GetBoundingBox();

        cont->AddText ({bbox.Min().x + bbox.Width() * 0.1f, bbox.Min().y + bbox.Height() * 0.1f}, DrawPosition::TopLeft, "ESC", bbox.Height() * 0.45f, RAYWHITE);
        break;
    }
    case KEY_SPACE:
    {
        cont->AddRectangleRounded ({0., 0.}, DrawPosition::Top, size, size * 2, 0.4, RAYWHITE);
        auto rInt = cont->AddRectangleRounded ({0., size * 0.08f}, DrawPosition::Top, size * 0.75, size * 1.9, 0.4, BLACK);
        auto bbox = rInt->GetBoundingBox();

        cont->AddText ({bbox.Min().x + bbox.Width() * 0.5f, bbox.Min().y + bbox.Height() * 0.1f}, DrawPosition::Top, "SPACE", bbox.Height() * 0.45f, RAYWHITE);
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
        cont->AddRectangleRounded ({0., 0.}, DrawPosition::Top, size, size * 1.6, 0.4, RAYWHITE);
        auto rInt = cont->AddRectangleRounded ({0., size * 0.08f}, DrawPosition::Top, size * 0.75, size * 1.5, 0.4, BLACK);
        auto bbox = rInt->GetBoundingBox();

        cont->AddText ({bbox.Min().x + bbox.Width() * 0.5f, bbox.Min().y + bbox.Height() * 0.1f}, DrawPosition::Top, keyName, bbox.Height() * 0.45f, RAYWHITE);
    }

    auto AddArrow = [] (float angle, float size, DrawableContainer* cont)
    {
        cont->AddRectangleRounded ({0., 0.}, DrawPosition::Top, size, size, 0.4, RAYWHITE);
        auto rInt = cont->AddRectangleRounded ({0., size * 0.08f}, DrawPosition::Top, size * 0.75, size * 0.9, 0.4, BLACK);
        auto bbox = rInt->GetBoundingBox();
        Vector2 pos {bbox.Min().x + bbox.Width() * 0.5f, bbox.Min().y + bbox.Height() * 0.5f};

        cont->AddTriangle (pos, DrawPosition::Center, bbox.Height() * 0.5f, angle, RAYWHITE);
    };

    switch (key)
    {
    case KEY_UP:
        AddArrow (-90.f, size, cont.get());
        break;
    case KEY_DOWN:
        AddArrow (90.f, size, cont.get());
        break;
    case KEY_RIGHT:
        AddArrow (0.f, size, cont.get());
        break;
    case KEY_LEFT:
        AddArrow (180.f, size, cont.get());
        break;
    default:
        break;
    }

    return cont;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetBlockLetterT (int cellSize, const Color& mainColor, const Color& shadeColor)
{
    auto block = std::make_unique <DecorativeBlock> (cellSize);
    block->AddCell ({0, 0}, mainColor, shadeColor);
    block->AddCell ({0, 1}, mainColor, shadeColor);
    block->AddCell ({0, 2}, mainColor, shadeColor);
    block->AddCell ({1, 1}, mainColor, shadeColor);
    block->AddCell ({2, 1}, mainColor, shadeColor);
    block->AddCell ({3, 1}, mainColor, shadeColor);
    block->AddCell ({4, 1}, mainColor, shadeColor);

    block->SetOutline (RAYWHITE, cellSize/10);
    return block;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetBlockLetterE (int cellSize, const Color& mainColor, const Color& shadeColor)
{
    auto block = std::make_unique <DecorativeBlock> (cellSize);
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

    block->SetOutline (RAYWHITE, cellSize / 10);
    return block;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetBlockLetterR (int cellSize, const Color& mainColor, const Color& shadeColor)
{
    auto block = std::make_unique <DecorativeBlock> (cellSize);
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

    block->SetOutline (RAYWHITE, cellSize / 10);
    return block;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetBlockLetterI (int cellSize, const Color& mainColor, const Color& shadeColor)
{
    auto block = std::make_unique <DecorativeBlock> (cellSize);
    block->AddCell ({0, 0}, mainColor, shadeColor);
    block->AddCell ({1, 0}, mainColor, shadeColor);
    block->AddCell ({2, 0}, mainColor, shadeColor);
    block->AddCell ({3, 0}, mainColor, shadeColor);
    block->AddCell ({4, 0}, mainColor, shadeColor);

    block->SetOutline (RAYWHITE, cellSize / 10);
    return block;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetBlockLetterS (int cellSize, const Color& mainColor, const Color& shadeColor)
{
    auto block = std::make_unique <DecorativeBlock> (cellSize);
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

    block->SetOutline (RAYWHITE, cellSize / 10);
    return block;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetButton (const std::string& text, float width)
{
    auto cont = std::make_unique <DrawableContainer> ();

    cont->AddRectangle ({0., 0.}, DrawPosition::Center, width * 0.25, width, {72, 88, 130, 255});
    cont->AddText ({0., 0.}, DrawPosition::Center, text, width * 0.15, RAYWHITE);

    return cont;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetButtonHover (const std::string& text, float width)
{
    auto cont = std::make_unique <DrawableContainer> ();

    cont->AddRectangle ({0., 0.}, DrawPosition::Center, width * 0.3, width * 1.05, RAYWHITE);
    cont->AddRectangle ({0., 0.}, DrawPosition::Center, width * 0.25, width, {72, 88, 130, 255});
    cont->AddText ({0., 0.}, DrawPosition::Center, text, width * 0.15, RAYWHITE);

    return cont;
}

std::unique_ptr<DrawableObject> SpriteGraphicGenerator::GetButtonPressed (const std::string& text, float width)
{
    auto cont = std::make_unique <DrawableContainer> ();
    Color shadedPressed {53, 74, 115,  255};
    Color shade {33, 40, 58, 255};

    cont->AddRectangle ({0., 0.}, DrawPosition::Center, width * 0.3, width * 1.05, RAYWHITE);
    cont->AddRectangle ({0., 0.}, DrawPosition::Center, width * 0.25, width, shade);
    cont->AddRectangle ({0., width * 0.02f}, DrawPosition::Center, width * 0.21, width * 0.97, shadedPressed);
    cont->AddText ({0., 0.}, DrawPosition::Center, text, width * 0.15, RAYWHITE);

    return cont;
}


