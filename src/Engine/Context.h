#pragma once

#include "GraphicsContext.h"
#include "InputContext.h"
#include "PhysicsContext.h"
#include "WindowContext.h"

namespace Gelgine {
    struct GelgineContext {
        PhysicsContext physics;
        InputContext input;
        GraphicsContext graphics;
        WindowContext window;
        
        GelgineContext(Physics::PhysicsWorld *world, Graphics::Renderer *ren, WindowManager *window)
        : physics(world), input(window), graphics(ren), window(window) {}
    };
}