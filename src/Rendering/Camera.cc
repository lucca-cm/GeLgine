#include "Camera.h"

namespace Graphics {
    Camera::Camera(const glm::vec3& position, const glm::quat& rotation, float fov, float aspectRatio, float closestZ, float farthestZ)
        : position(position), rotation(rotation), fov(fov), aspectRatio(aspectRatio), closestZ(closestZ), farthestZ(farthestZ) {
            outdatedView = true;
            outdatedProjection = true;
            updateCamera();
    }

    void Camera::updateCamera()
    {
        updateViewMatrix();
        updateProjectionMatrix();
    }

    void Camera::updateViewMatrix() {
        if (!outdatedView)
            return;

        viewMatrix = glm::mat4_cast(glm::conjugate(rotation)) * glm::translate(glm::mat4(1.0f), -position);

        outdatedView = false;
    }

    void Camera::updateProjectionMatrix() {
        if (!outdatedProjection)
            return;
        projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, closestZ, farthestZ);

        outdatedProjection = false;
    }

    void Camera::moveBy(const glm::vec3& deltaPos) {
        position += deltaPos;
        outdatedView = true;
    }

    void Camera::moveTo(const glm::vec3& pos) {
        position = pos;
        outdatedView = true;
    }

    void Camera::rotateBy(const glm::quat& deltaRot) {
        rotation = glm::normalize(deltaRot * rotation);
        outdatedView = true;
    }

    void Camera::setRotation(const glm::quat& rotation) {
        this->rotation = rotation;
        outdatedView = true;
    }
}