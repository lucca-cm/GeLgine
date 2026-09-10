#pragma once

#include "Component.h"
#include "../../Rendering/Renderer.h"

namespace Gelgine {
    class GraphicsComponent : public Component {
        private:
            bool shouldDraw = false;

            virtual void drawObject(Graphics::Renderer &ren) = 0;
        public:
            GraphicsComponent(GameObject *owner) : Component(owner) {}
            void attach() override {
                shouldDraw = true;
            }

            void dettach() override {
                shouldDraw = false;
            }

            void draw(Graphics::Renderer &ren) {
                if (shouldDraw)
                    drawObject(ren);
            }
    };
}