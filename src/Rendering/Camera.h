#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Shader.h"

namespace Graphics {
    class Camera {
        private:
            float fov, aspectRatio, closestZ, farthestZ;
            bool outdatedView = false, outdatedProjection = false;
            glm::vec3 position;
            glm::quat rotation;
            glm::mat4 projectionMatrix, viewMatrix;
            
        public:
            Camera(glm::vec3 position, glm::quat& rotation, float fov, float aspectRatio, float closestZ, float farthestZ);
            Camera(float fov, float aspectRatio, float closestZ, float farthestZ);
            Camera(float fov, float aspectRatio);

            void updateCamera();
            void updateViewMatrix();
            void updateProjectionMatrix();
            void forceUpdateCamera() {
                outdatedView = true;
                outdatedProjection = true;
                updateCamera();
            }

            void moveBy(const glm::vec3& deltaPos);
            void moveTo(const glm::vec3& pos);

            void rotateBy(const glm::quat& deltaRot);
            void setRotation(const glm::quat& rotation);

            void setAspectRatio(float aspectRatio) {
                this->aspectRatio = aspectRatio;
                outdatedProjection = true;
            }
            void setFOV(float fov) {
                this->fov = fov;
                outdatedProjection = true;
            }
            void setClipZone(float near, float far) {
                closestZ = near;
                farthestZ = far;
                outdatedProjection = true;
            }

            void uploadToShader(const Shader& s) {
                s.setUniform("view", viewMatrix);
                s.setUniform("projection", projectionMatrix);
            }
    };
}