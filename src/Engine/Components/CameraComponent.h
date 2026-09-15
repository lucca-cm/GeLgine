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

            void setCameraAsCurrent() {
                owner->getContext()->graphics.setCurrentCamera(&camera);
            }

            void addCameraToCurrent() {
                owner->getContext()->graphics.addCurrentCamera(&camera);
            }

            void moveBy(const glm::vec3& deltaPos) {
                camera.moveBy(deltaPos);
            }
            void moveTo(const glm::vec3& pos) {
                camera.moveTo(pos);
            }

            void rotateBy(const glm::quat& deltaRot) {
                camera.rotateBy(deltaRot);
            }
            void setRotation(const glm::quat& rotation) {
                camera.setRotation(rotation);
            }

            void setAspectRatio(float aspectRatio) {
                camera.setAspectRatio(aspectRatio);
            }
            void setFOV(float fov) {
                camera.setFOV(fov);
            }
            void setClipZone(float near, float far) {
                camera.setClipZone(near, far);
            }

 
    };
}