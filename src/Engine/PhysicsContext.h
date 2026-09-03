#pragma once

#include "../Physics/PhysicsEngine.h" 

namespace GeLgine {
    class PhysicsContext {
        private:
            Physics::PhysicsWorld *world;
        public:
            PhysicsContext(Physics::PhysicsWorld *world) : world(world) {}
            size_t addBody(const Physics::RigidBody &b) {
                return world->addBody(b);
            }

            Physics::RigidBody &getRigidBody(const size_t id) {
                return world->getRigidBody(id);
            }

            void addCollider(Physics::Collider *c) {
                world->addCollider(c);
            }

            void createPlane(glm::vec3 normal, float distance) {
                Physics::RigidBody plane(glm::vec3(0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 0, glm::mat3(1.0f), 0);
                auto *planeCollider = new Physics::PlaneCollider(normal, distance);
                plane.setCollider(planeCollider);
                addBody(plane);
                addCollider(planeCollider);
            }
    };
}