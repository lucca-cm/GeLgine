#pragma once

#include "../Physics/PhysicsEngine.h" 

namespace GeLgine {
    class PhysicsContext {
        private:
            Physics::PhysicsWorld *world;
        public:
            PhysicsContext(Physics::PhysicsWorld *world) : world(world) {}
            void addBody(const Physics::RigidBody &b) {
                world->addBody(b);
            }

            void addCollider(Physics::Collider *c) {
                world->addCollider(c);
            }
    };
}