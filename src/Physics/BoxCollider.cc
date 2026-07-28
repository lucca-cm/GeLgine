#include "BoxCollider.h"

namespace Physics {
    BoxCollider::BoxCollider(glm::vec3 halfSize) :halfSize(halfSize) {}

    glm::vec3 BoxCollider::support(const glm::vec3& d, const Transform& transform) const {
        glm::vec3 dir = glm::conjugate(transform.orientation) * d;
        glm::vec3 p = glm::vec3(
            dir.x >= 0 ? halfSize.x : -halfSize.x,
            dir.y >= 0 ? halfSize.y : -halfSize.y,
            dir.z >= 0 ? halfSize.z : -halfSize.z
        ); 
        
        return transform.posistion + transform.orientation * p;
    }
    AABB BoxCollider::computeAABB(const Transform &transform) const {
        AABB ab;
        auto rotMatrix = glm::mat3_cast(transform.orientation);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                rotMatrix[i][j] = abs(rotMatrix[i][j]);
            }
        }

        ab.halfExtent = rotMatrix * this->halfSize;
        ab.center = transform.posistion;
        return ab;
    }
}