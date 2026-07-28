#include "SphereCollider.h"

namespace Physics {
    SphereCollider::SphereCollider(float radius) : radius(radius) {}

    glm::vec3 SphereCollider::support(const glm::vec3& d, const Transform& transform) const {
        if (glm::dot(d, d) == 0.0f)
            return transform.posistion;
        return transform.posistion + glm::normalize(d) * radius;
    }

    AABB SphereCollider::computeAABB(const Transform &transform) const {
        AABB ab;
        ab.center = transform.posistion;
        ab.halfExtent = glm::vec3(radius);
        return ab;
    }
}