#pragma once

#include <glm/gtc/quaternion.hpp>

#include "Collider.h"

namespace Physics {
    class PlaneCollider : public Collider {
        private:
            glm::vec3 normal;
            float distance;
        public:
            PlaneCollider(glm::vec3 normal, float distance);
            glm::vec3 support(const glm::vec3& d, const Transform& transform) const override;
            AABB computeAABB(const Transform& transform) const override;

            ColliderType getType() const override {
                return ColliderType::Plane;
            }

            glm::vec3 getNormal() const {
                return normal;
            }

            float getDistance() const {
                return distance;
            }
    };
}