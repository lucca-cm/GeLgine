#pragma once

#include <vector>

#include "RigidBody.h"
#include "Collider.h"
#include "CollisionHandler.h"

namespace Physics {
    class PhysicsWorld {
        private:
            std::vector<RigidBody> bodies;
            std::vector<Collider *> colliders;
            std::vector<CollisionPoint> collisions;
            std::vector<AABB> aabbCache;
            std::vector<float> impulses;

            size_t velocityIterations = 5;
        public:
            size_t addBody(const RigidBody& b);
            size_t addCollider(Collider *c);
            
            RigidBody& getRigidBody(size_t id);

            void cacheCurrentAABB();

            void step(float dt);
    };
}