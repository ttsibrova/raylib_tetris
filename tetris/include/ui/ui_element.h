#pragma once
#include <graphics/drawable_container.h>
#include <graphics/containered_drawable_object.h>
#include <engine/observer.h>

template <typename ObserverType>
class UIElement: public ContaineredDrawableObject, public ObserverType
{
public:
    using Element = UIElement <ObserverType>;

};
