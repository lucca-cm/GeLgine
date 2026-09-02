#pragma once

namespace GeLgine {
    struct GeLgineContext;
    class Game {
        protected:
            GeLgineContext* ctx;
        public:
            int width = 800, height = 600;
            float fixedDt = 1.0f / 60.0f;

            void setContext(GeLgineContext *c) {
                ctx = c;
            }
            virtual void onStart() = 0;
            virtual void onUpdate(float dt) = 0;
            virtual void onFixedUpdate() = 0;
            virtual void onRender() = 0;

    };
}