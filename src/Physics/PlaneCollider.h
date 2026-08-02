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

            ColliderType getType() const {
                return ColliderType::Plane;
            }
    };
}