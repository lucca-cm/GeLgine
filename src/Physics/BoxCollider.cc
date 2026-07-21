#include "BoxCollider.h"

namespace Physics {
    BoxCollider::BoxCollider(glm::vec3 halfSize) :halfSize(halfSize) {}

    glm::vec3 BoxCollider::getFurthestPoint(const glm::vec3& d, const Transform& transform) const {
        glm::vec3 dir = glm::conjugate(transform.orientation) * d;
        glm::vec3 p = glm::vec3(
            dir.x >= 0 ? halfSize.x : -halfSize.x,
            dir.y >= 0 ? halfSize.y : -halfSize.y,
            dir.z >= 0 ? halfSize.z : -halfSize.z
        ); 
        
        return transform.posistion + transform.orientation * p;
    }
}