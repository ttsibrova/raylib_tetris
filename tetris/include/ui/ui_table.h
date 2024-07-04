#pragma once
#include <graphics/drawable_object.h>
#include <graphics/graphics_helper.h>
#include <vector>
#include <numeric>

template <size_t Col>
class Table: public DrawableObject
{
public:

    Table (float cellHeight):
        m_cellHeight (cellHeight),
        m_rowNum (0)
    {
        m_cellWidths.fill (0);
    }

    ~Table() {
        for (auto& elem : m_data) {
            if (elem) {
                delete elem;
            }
        }
    }
    void SetWidths (std::array <float, Col>&& widths)
    {
        m_cellWidths = std::move (widths);
    }

    template <size_t Id>
    constexpr float GetColWidth() const
    {
        static_assert (Id < Col);
        return m_cellWidths[Id];
    }

    void AddRow (std::array <DrawableObject*, Col>&& vals)
    {
        size_t widthOffset = 0;
        for (size_t i = 0; i < Col; i++) {
            float posX = m_cellWidths[i] / 2 + widthOffset;
            widthOffset += m_cellWidths[i];
            float posY = GetRowsNum() * m_cellHeight + m_cellHeight / 2;

            auto bbox = vals[i]->GetBoundingBox();
            auto currentAdjustedPos = GraphicsHelper::ComputePosition (DrawPosition::Center, bbox);
            vals[i]->SetAlign (DrawPosition::Center);
            vals[i]->Translate (GraphicsHelper::ComputeTranslation (currentAdjustedPos, {posX, posY}));

            m_data.push_back (std::move (vals[i]));
        }
        m_rowNum++;
    }
    size_t GetRowsNum() const { return m_rowNum; }

    virtual void Draw() const override {
        for (auto& elem : m_data) {
            elem->Draw();
        }
    }

    virtual BoundingBox2d GetBoundingBox() const override
    {
        float tableWidth = std::accumulate (m_cellWidths.begin(), m_cellWidths.end(), 0.f);
        Vector2 max {m_pos.x + tableWidth, m_pos.y + (float)GetRowsNum() * m_cellHeight};
        return {m_pos, max};
    }

    virtual void Translate (const Vector2& translation) override
    {
        m_pos.x += translation.x;
        m_pos.y += translation.y;
        for (auto& elem : m_data) {
            elem->Translate (translation);
        }
    }

    virtual void Scale (float scale) override {}

private:
    std::array <float, Col>     m_cellWidths;
    float                       m_cellHeight;
    size_t                       m_rowNum;
    std::vector<DrawableObject*> m_data;
};
