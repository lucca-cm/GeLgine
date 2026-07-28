#include "SphereCollider.h"

namespace Physics {
    SphereCollider::SphereCollider(float radius) : radius(radius) {}

    glm::vec3 SphereCollider::support(const glm::vec3& d, const Transform& transform) const {
        if (glm::dot(d, d) == 0.0f)
            return transform.posistion;
        return transform.posistion + glm::normalize(d) * radius;
    }
}