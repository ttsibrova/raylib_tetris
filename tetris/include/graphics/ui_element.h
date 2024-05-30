#pragma once
#include <core/drawable_object.h>
#include <functional/observer.h>
#include <graphics/drawable_container.h>

template <typename ObserverType>
class UIElement: public IDrawableObject , public ObserverType
{
public:
    using Element = UIElement <ObserverType>;

    UIElement ():
        m_graphics (std::make_unique <DrawableContainer>()),
        m_pos {0., 0.},
        m_aligment (DrawPosition::TopLeft)
    {
    }

    void Init() { // Should be called AFTER SetPosition();
        FillGraphics();
        UpdateLocation();
    }

    void UpdateLocation()
    {
        auto currentAdjPos = DrawableContainer::ComputePosition (m_aligment, GetBoundingBox());
        m_graphics->Translate (DrawableContainer::ComputeTranslation (currentAdjPos, m_pos));
    }

    void SetPosition (const Vector2& pos, DrawPosition align)
    {
        m_pos = pos; m_aligment = align;
    }

    // Should be implemented in exact UI Element
    virtual void FillGraphics() = 0;

    // DrawableObject interface
    virtual void Draw() const override
    {
        m_graphics->Draw();
    }

    virtual BoundingBox2d GetBoundingBox() const override
    {
        return m_graphics->GetBoundingBox();
    }

    virtual void Translate (const Vector2& translation) override
    {
        m_graphics->Translate (translation);
    }

    virtual void Scale (float scale) override {
        m_graphics->Scale (scale);
    }

protected:
    std::unique_ptr <DrawableContainer> m_graphics;

private:
    Vector2            m_pos;
    DrawPosition       m_aligment;
};

