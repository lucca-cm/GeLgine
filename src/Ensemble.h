#pragma once

#include <vector>
#include <memory>

#include "./Engine/GameObject.h"

namespace Gelgine {
    class Ensemble {
        private:
            GelgineContext *ctx = nullptr;
            bool active;
        protected:
            std::vector<std::unique_ptr<GameObject>> gameObjects;
        public:
            virtual ~Ensemble() = default;

            void draw(Graphics::Renderer &ren) {
                for (auto& obj : gameObjects) {
                    obj->draw(ren);
                }
            }

            template<typename T, typename... Args>
            T &createObject(Args &&...args) {
                auto obj = std::make_unique<T>(this, std::forward<Args>(args)...);

                T& ref = *obj;
                gameObjects.push_back(std::move(obj));

                return ref;
            }

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

            GelgineContext *getContext() {
                return ctx;
            }
            
            virtual void onStart() = 0;
            virtual void onUpdate() = 0;
            virtual void onFixedUpdate() = 0;
            virtual void onRender() = 0;
    };
}