#pragma once

#include <glm/glm.hpp>

namespace Physics {
    struct CollisionPoint {
        float penetrationDepth;
        glm::vec3 point;
    };

    struct CollisionManifold {
        Collider *first, *second;

        glm::vec3 normal;
        std::vector<CollisionPoint> points;

    };

    class Collider {
        public:
            virtual ~Collider() = default;
            virtual glm::vec3 getFurthestPoint(const glm::vec3 d) const = 0;
    };
}