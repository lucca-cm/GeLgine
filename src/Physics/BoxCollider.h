#pragma once

#include <glm/gtc/quaternion.hpp>

#include "Collider.h"

namespace Physics {
    class BoxCollider : public Collider {
        private:
            glm::vec3 halfSize;
        public:
            BoxCollider(glm::vec3 halfSize);
            glm::vec3 support(const glm::vec3& d, const Transform& transform) const override;
            AABB computeAABB(const Transform& transform) const override;
            std::vector<glm::vec3> getIncidentFace(const glm::vec3& d, const Transform& transform) const;
            ColliderType getType() const override {
                return ColliderType::Box;
            }

    };
}