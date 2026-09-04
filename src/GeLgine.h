#pragma once

#include "Game.h"
#include "Physics/PhysicsEngine.h"
#include "Rendering/Rendering.h"
#include "WindowManager.h"
#include "Engine/Context.h"

namespace Gelgine {
    class Engine {
        private:
            Physics::PhysicsWorld world;
            Graphics::Renderer renderer;
            WindowManager wm;
            GelgineContext context;

        public:
            Engine() : wm(800, 800), context(&world, &renderer, &wm) {}

            GelgineContext *getContext() {
                return &context;
            }
            void run(Game& game);
    };   
}