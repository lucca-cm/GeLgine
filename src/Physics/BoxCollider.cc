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

    std::vector<glm::vec3> BoxCollider::getIncidentFace(const glm::vec3 &d, const Transform &transform) const {
        glm::vec3 localDir = glm::conjugate(transform.orientation) * d;

        glm::vec3 absDir = glm::abs(localDir);
        int axis = 0;
        if (absDir.y > absDir.x && absDir.y > absDir.z) axis = 1;
        else if (absDir.z > absDir.x && absDir.z > absDir.y) axis = 2;

        float sign = localDir[axis] >= 0 ? 1.0f : -1.0f;

        glm::vec3 base = halfSize;
        base[axis] *= sign;

        int u = (axis + 1) % 3;
        int v = (axis + 2) % 3;

        std::vector<glm::vec3> face(4);
        glm::vec3 p = base;
        p[u] =  halfSize[u]; p[v] =  halfSize[v]; face[0] = p;
        p[u] =  halfSize[u]; p[v] = -halfSize[v]; face[1] = p;
        p[u] = -halfSize[u]; p[v] = -halfSize[v]; face[2] = p;
        p[u] = -halfSize[u]; p[v] =  halfSize[v]; face[3] = p;

        for (auto& vtx : face)
            vtx = transform.posistion + transform.orientation * vtx;

        return face;
    }
}