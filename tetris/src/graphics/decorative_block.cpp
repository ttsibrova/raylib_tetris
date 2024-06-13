#include <graphics/decorative_block.h>

Cell::Cell (float cellSize, const Color& mainColor, const Color& shadeColor)
{
    float shadeSize = cellSize / 7;
    m_graphics.AddRectangle (m_pos, DrawPosition::TopLeft, cellSize, cellSize, shadeColor);
    m_graphics.AddRectangle ({m_pos.x + shadeSize, m_pos.y + shadeSize},
                              DrawPosition::TopLeft,
                              cellSize - shadeSize * 2, cellSize - shadeSize * 2,
                              mainColor);
}

void DecorativeBlock::AddCell (const GridPosition& pos, const Color& mainColor, const Color& shadeColor)
{
    float posX = m_pos.x + pos.m_col * (m_cellSize + 1);
    float posY = m_pos.y + pos.m_row * (m_cellSize + 1);

    m_positions.push_back (pos);

    auto cell = new Cell (m_cellSize, mainColor, shadeColor);

    m_graphics.AddDrawableObject ({posX, posY}, DrawPosition::TopLeft, cell);
}

void DecorativeBlock::SetOutline (const Color& outlineColor, int outlineSize)
{
    m_outlineColor = outlineColor;
    m_outlineSize = outlineSize;
}

void DecorativeBlock::SetExternalShade (const Color& extShadeColor, int extShadeOffset)
{
    m_externalShadeColor = extShadeColor;
    m_extShadeOffset = extShadeOffset;
}

void DecorativeBlock::Draw() const
{
    const float roundness = 0.2;
    const int segments = 10;

    if (m_externalShadeColor.has_value()) {
        if (m_outlineColor.has_value()) {
            for (auto& pos : m_positions) {
                float posX = m_pos.x + pos.m_col * (m_cellSize + 1) + m_extShadeOffset;
                float posY = m_pos.y + pos.m_row * (m_cellSize + 1) + m_extShadeOffset;

                DrawRectangleRounded ({posX, posY, (float) m_cellSize, (float) m_cellSize}, roundness, segments, m_externalShadeColor.value());
            }
        } else {
            for (auto& pos : m_positions) {
                int posX = m_pos.x + pos.m_col * (m_cellSize + 1) + m_extShadeOffset;
                int posY = m_pos.y + pos.m_row * (m_cellSize + 1) + m_extShadeOffset;

                DrawRectangle (posX, posY, m_cellSize, m_cellSize, m_externalShadeColor.value());
            }
        }
    }
    if (m_outlineColor.has_value()) {
        float outlineCellSize = m_cellSize + 2 * m_outlineSize;
        for (auto& pos: m_positions) {
            float posX = m_pos.x + pos.m_col * (m_cellSize + 1) - m_outlineSize;
            float posY = m_pos.y + pos.m_row * (m_cellSize + 1) - m_outlineSize;
            DrawRectangleRounded ({posX, posY, outlineCellSize, outlineCellSize}, roundness, segments, m_outlineColor.value());
        }
    }

    m_graphics.Draw();
}

void DecorativeBlock::Translate (const Vector2& translation)
{
    m_pos.x += translation.x;
    m_pos.y += translation.y;
    m_graphics.Translate (translation);
}
