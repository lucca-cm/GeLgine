#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::quat rotation, float fov, float aspectRatio, float closeZ, float farthestZ)
    : position(position), rotation(rotation), fov(fov), aspectRatio(aspectRatio), closestZ(closestZ), farthestZ(farthestZ) {
        outdatedView = true;
        outdatedProjection = true;
        updateCamera();
}

void Camera::updateCamera() {
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

