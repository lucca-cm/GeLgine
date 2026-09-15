#include "../Gelgine.h"

#include "MyGame.h"

int main() {
    Gelgine::Engine engine;

    MyGame game;
    engine.run(game);
}