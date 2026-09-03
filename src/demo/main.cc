#include "../GeLgine.h"

#include "MyGame.h"

int main() {
    GeLgine::Engine engine;

    MyGame game;
    game.setContext(engine.getContext());

    engine.run(game);
}