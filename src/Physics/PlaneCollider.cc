#include "PlaneCollider.h"

namespace Physics {
    PlaneCollider::PlaneCollider(glm::vec3 normal, float distance) : normal(normal), distance(distance) {}

    glm::vec3 PlaneCollider::support(const glm::vec3& d, const Transform& transform) const {
        return glm::vec3(-1, -1, -1);
    }

    AABB PlaneCollider::computeAABB(const Transform &transform) const {
        return AABB();
    }
}