#include "GameObject.h"


namespace Gelgine {
    template <typename T, typename... Args>
    void GameObject::addComponent(Args &&...args) {
        auto component = std::make_unique<T>(this, std::forward<Args>(args)...);

        components[typeid(T)] = std::move(component);
    }

    template <typename T>
    void GameObject::removeComponent() {
        components.erase(components.find(typeid(T)));
    }

    template <typename T>
    T &GameObject::getComponent() {
        auto it = components.find(typeid(T));
        
        if (it == components.end()) {
            throw std::runtime_error("Component not found!");
        }

        return dynamic_cast<T&>(it->second.get());
    }
}