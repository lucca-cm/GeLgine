#pragma once

namespace GeLgine {
    class Game {
        public:
            int width = 800, height = 600;
            float fixedDt = 1.0f / 60.0f;
            virtual void onStart() = 0;
            virtual void onUpdate(float dt) = 0;
            virtual void onFixedUpdate() = 0;
            virtual void onRender() = 0;

    };
}