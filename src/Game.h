#pragma once

namespace GeLgine {
    struct GeLgineContext;
    class Game {
        protected:
            GeLgineContext* ctx;
        public:
            const int width = 800, height = 600;
            const float fixedDt = 1.0f / 60.0f;

            Game(int width = 800, int height = 600, float fixedDt = 1.0f / 60.0f)
                : width(width), height(height), fixedDt(fixedDt) {}

            void setContext(GeLgineContext *c) {
                ctx = c;
            }
            virtual void onStart() = 0;
            virtual void onUpdate(float dt) = 0;
            virtual void onFixedUpdate() = 0;
            virtual void onRender() = 0;

    };
}