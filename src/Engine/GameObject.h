#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <stdexcept>
#include <type_traits>

#include "./Components/Component.h"
#include "./Components/GraphicsComponent.h"
#include "./Context.h"

namespace Gelgine {
    class GameObject {
        private:
            GelgineContext *ctx;
            std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

            std::vector<GraphicsComponent *> renderablePieces;
        public:
            GameObject(GelgineContext *ctx) : ctx(ctx) {}
            
            void draw(Graphics::Renderer &ren) {
                for (auto c : renderablePieces) {
                    c->draw(ren);
                }
            }

            template <typename T, typename... Args>
            void addComponent(Args&&... args);

            template <typename T>
            void removeComponent();

            template <typename T>
            T& getComponent();

            GelgineContext *getContext() {
                return ctx;
            } 
    };
}