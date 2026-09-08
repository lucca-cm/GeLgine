#pragma once

#include "Component.h"
#include "../../Rendering/Renderer.h"

namespace Gelgine {
    class GraphicsComponent : public Component {
        public:
            GraphicsComponent(GameObject *owner) : Component(owner) {}
            virtual void draw(Graphics::Renderer &ren) = 0;
    };
}