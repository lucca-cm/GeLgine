#include "Ensemble.h"


namespace Gelgine {
    template <typename T, typename... Args>
    T &Gelgine::Ensemble::createObject(Args &&...args) {
        auto obj = std::make_unique<T>(this, std::forward<Args>(args)...);

        T& ref = *obj;
        gameObjects.push_back(std::move(obj));

        return ref;
    }
}