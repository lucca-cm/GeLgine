#pragma once

#include "Game.h"
#include "Physics/Physics.h"
#include "Rendering/Rendering.h"
#include "WindowManager.h"

namespace GeLgine {
    struct GeLgineContext {
        Physics::PhysicsWorld& physics;
        Graphics::Renderer& renderer;
        WindowManager& window;
    };
    class Engine {
        private:
            Physics::PhysicsWorld world;
            Graphics::Renderer renderer;
            WindowManager wm;
            
        public:
            Engine() : wm(0, 0) {}
            GeLgineContext getContext() {
                auto c = GeLgineContext{
                    .physics = world,
                    .renderer = renderer,
                    .window = wm,
                };

                return c;
            }
            void run(Game& game);
    };   
}