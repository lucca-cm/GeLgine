#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <stdexcept>

#include "./Components/Component.h"
#include "./Context.h"

namespace Gelgine {
    class GameObject {
        private:
            GelgineContext *ctx;
            std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
        public:
            GameObject(GelgineContext *ctx) : ctx(ctx) {}
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