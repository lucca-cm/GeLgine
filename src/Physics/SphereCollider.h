#pragma once

#include <glm/gtc/quaternion.hpp>

#include "Collider.h"

namespace Physics {
    class SphereCollider : public Collider {
        private:
            float radius;
        public:
            SphereCollider(float radius);
            glm::vec3 support(const glm::vec3& d, const Transform& transform) const override;
            AABB computeAABB(const Transform& transform) const override;
    };
}