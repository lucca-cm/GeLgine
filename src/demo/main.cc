#include "../Gelgine.h"

#include "MyGame.h"

int main() {
    Gelgine::Engine engine;

    MyGame game;
    game.setContext(engine.getContext());

    engine.run(game);
}