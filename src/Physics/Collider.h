#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Physics {
    struct Transform;
    class RigidBody;
    struct AABB;

    class Collider {
        public:
            virtual glm::vec3 support(const glm::vec3& d, const Transform& transform) const = 0;
            virtual AABB computeAABB(const Transform& transform) const = 0;
    };

    struct CollisionPoint {
        RigidBody *first, *second;
        float penetrationDepth;
        glm::vec3 normal;
        glm::vec3 point;
    };

    struct Transform {
        glm::vec3 posistion;
        glm::quat orientation;
    };

    struct AABB {
        glm::vec3 center;
        glm::vec3 halfExtent;
    };
}