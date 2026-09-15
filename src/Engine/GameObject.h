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
    class Ensemble;
    class GameObject {
        private:
            Ensemble *ensemble;
            std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

            std::vector<GraphicsComponent *> renderablePieces;
        public:
            GameObject() = default;
            explicit GameObject(Ensemble *ensemble) : ensemble(ensemble) {}
            void draw(Graphics::Renderer &ren) {
                for (auto c : renderablePieces) {
                    c->draw(ren);
                }
            }

            template <typename T, typename... Args>
            void addComponent(Args&&... args) {
                auto component = std::make_unique<T>(this, std::forward<Args>(args)...);

                if constexpr (std::is_base_of_v<GraphicsComponent, T>) {
                    renderablePieces.push_back(component.get());
                }
                components[typeid(T)] = std::move(component);
            }
    
            template <typename T>
            void removeComponent() {
                components.erase(components.find(typeid(T)));
            }

            template <typename T>
            T& getComponent() {
                auto it = components.find(typeid(T));
                
                if (it == components.end()) {
                    throw std::runtime_error("Component not found!");
                }

                return *dynamic_cast<T*>(it->second.get());
            }
        
            void setEnsemble(Ensemble *e) {
                ensemble = e;
            }

            GelgineContext *getContext();
    };
}