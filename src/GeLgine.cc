#include "GeLgine.h"

void GeLgine::Engine::run(Game& game) {
    WindowManager wm(game.width, game.height);
    Graphics::Renderer renderer;
    Physics::PhysicsWorld world;

    wm.initTime();
    float DtAccumulator = 0.0f;
    while (!wm.shouldExit()) {
        wm.pollEvents();

        wm.updateTime();
        DtAccumulator += wm.getDeltaTime();
        while (DtAccumulator >= game.fixedDt) {
            game.onUpdate(wm.getDeltaTime());
            world.step(wm.getDeltaTime());
            DtAccumulator -= game.fixedDt;
        }

        renderer.clear();

        wm.swapBuffers();
    }
}