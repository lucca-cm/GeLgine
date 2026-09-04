#pragma once

#include <vector>
#include <memory>

#include "./Engine/GameObject.h"

namespace Gelgine {
    class Ensemble {
        protected:
            std::vector<std::unique_ptr<GameObject>> gameObjects;
            bool activated = false; 
        public:
            virtual void ~Scene() = default;

            void draw() {
                for (auto& obj : gameObjects) {
                    obj->draw();
                }
            }

            template<typename T, typename... Args>
            T &createObject(Args&&... args);

            void activate() {
                activated = true;
            }

            void deactivate() {
                activated = false;
            }

            bool isActive() {
                return activated;
            }
            
            virtual void onUpdate() = 0;
            virtual void onFixedUpdate() = 0;
            virtual void onRender() = 0;
    };
}