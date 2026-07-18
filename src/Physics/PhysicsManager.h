#pragma once

#include <vector>

#include "RigidBody.h"
#include "Collider.h"
#include "CollisionHandler.h"

namespace Physics {
    class PhysicsManager {
        private:
            std::vector<RigidBody> bodies;
            std::vector<std::unique_ptr<Collider>> colliders;
        public:
            RigidBody& addBody(const RigidBody& b) {
                bodies.push_back(b);

                return bodies.back();
            }

            Collider& addCollider(std::unique_ptr<Collider> c) {
                colliders.push_back(std::move(c));

                return *colliders.back();
            }
            void update(float dt) {
                for (auto& body : bodies) {
                    body.integrate(dt);
                }
            }
    };
}