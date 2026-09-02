#pragma once

#include "Game.h"
#include "Physics/PhysicsEngine.h"
#include "Rendering/Rendering.h"
#include "WindowManager.h"
#include "Engine/Context.h"

namespace GeLgine {
    struct GeLgineContext {
        PhysicsContext physics;
        InputContext input;
        GraphicsContext graphics;
        WindowContext window;
        
        GeLgineContext(Physics::PhysicsWorld *world, Graphics::Renderer *ren, WindowManager *window)
        : physics(world), input(window), graphics(ren), window(window) {}
    };
    class Engine {
        private:
            Physics::PhysicsWorld world;
            Graphics::Renderer renderer;
            WindowManager wm;
            
        public:
            Engine() : wm(0, 0) {}
            GeLgineContext getContext() {
                GeLgineContext c(&world, &renderer, &wm);
                return c;
            }
            void run(Game& game);
    };   
}