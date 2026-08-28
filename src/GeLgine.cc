#include "GeLgine.h"

void GeLgine::Engine::run(Game& game) {
    wm.setWindowSize(game.width, game.height);
    game.onStart();
    wm.initTime();
    float DtAccumulator = 0.0f;
    while (!wm.shouldExit()) {
        wm.pollEvents();

        wm.updateTime();
        DtAccumulator += wm.getDeltaTime();
        
        game.onUpdate(wm.getDeltaTime());

        while (DtAccumulator >= game.fixedDt) {
            game.onFixedUpdate();
            world.step(game.fixedDt);
            DtAccumulator -= game.fixedDt;
        }

        renderer.clear();
        game.onRender();

        wm.swapBuffers();
    }
}