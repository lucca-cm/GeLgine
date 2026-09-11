#pragma once

#include "Components.h"

namespace Gelgine {
    class CameraComponent : public Component {
        private:
            Graphics::Camera camera;   
        public:

            CameraComponent(GameObject *owner, glm::vec3 position, glm::quat& rotation, float fov, float aspectRatio, float closestZ, float farthestZ)
             : Component(owner),
             camera(position, rotation, fov, aspectRatio, closestZ, farthestZ) {}

            CameraComponent(GameObject *owner, float fov, float aspectRatio, float closestZ, float farthestZ)
            : Component(owner), camera(fov, aspectRatio, closestZ, farthestZ) {}

            CameraComponent(GameObject *owner, float fov, float aspectRatio) : Component(owner), camera(fov, aspectRatio) {}

            CameraComponent(GameObject *owner) : Component(owner), camera(75.0f, 16.0f/9.0f) {}

    };
}