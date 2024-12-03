#pragma once
#include <graphics/drawable_container.h>
#include <graphics/drawable_object_with_container.h>
#include <engine/observer.h>

template <typename ObserverType>
class UIElement: public DrawableObjectWithContainer, public ObserverType
{
public:
    using Element = UIElement <ObserverType>;

};
