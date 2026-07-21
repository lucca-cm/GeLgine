#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Physics {
    class Collider {
        public:
            virtual glm::vec3 getFurthestPoint(const glm::vec3& d, const Transform& transform) const = 0;
    };
    struct CollisionPoint {
        float penetrationDepth;
        glm::vec3 point;
    };

    struct CollisionManifold {
        Collider *first, *second;

        glm::vec3 normal;
        std::vector<CollisionPoint> points;

    };

    struct Transform {
        glm::vec3 posistion;
        glm::quat orientation;
    };
}