#pragma once

#include <vector>
#include <memory>

#include "./Engine/GameObject.h"

namespace Gelgine {
    class Ensemble {
        private:
            GelgineContext *ctx;
            bool active;
        protected:
            std::vector<std::unique_ptr<GameObject>> gameObjects;
        public:
            ~Ensemble() = default;

            void draw(Graphics::Renderer &ren) {
                for (auto& obj : gameObjects) {
                    obj->draw(ren);
                }
            }

            template<typename T, typename... Args>
            T &createObject(Args&&... args);

            void activate() {
                active = true;
            }

            void deactivate() {
                active = false;
            }

            bool isActive() {
                return active;
            }

            void setContext(GelgineContext *c) {
                ctx = c;
            }
            
            virtual void onUpdate() = 0;
            virtual void onFixedUpdate() = 0;
            virtual void onRender() = 0;
    };
}