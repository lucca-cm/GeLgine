#pragma once

#include <vector>

#include "RigidBody.h"
#include "Collider.h"
#include "CollisionHandler.h"

namespace Physics {
    class PhysicsManager {
        private:
            std::vector<RigidBody> bodies;
            std::vector<Collider *> colliders;
            std::vector<CollisionPoint> collisions;
            std::vector<float> impulses;

            size_t velocityIterations = 5;
        public:
            size_t addBody(const RigidBody& b) {
                bodies.push_back(b);

                return bodies.size() - 1;
            }

            size_t addCollider(Collider *c) {
                colliders.push_back(c);

                return colliders.size() - 1;
            }
            
            RigidBody& getRigidBody(size_t id) {
                return bodies[id];
            }

            void step(float dt) {
                for (size_t i = 0; i < bodies.size(); ++i) {
                    for (size_t j = i + 1; j < bodies.size(); ++j) {
                        auto& a = bodies[i];
                        auto& b = bodies[j];
                        
                        auto v = CollisionHandler::checkCollision(a, b);

                        collisions.insert(collisions.end(), v.begin(), v.end());
                    }
                }
                
                for (int i = 0; i < velocityIterations; i++) {
                    for (int j = 0; j < collisions.size(); j++) {
                        auto& c = collisions[j];
                        
                        RigidBody& a = *c.first;
                        RigidBody& b = *c.second;

                        glm::vec3 rA = c.point - a.getPosition(); 
                        glm::vec3 rB = c.point - b.getPosition();

                        float J = CollisionHandler::solveImpulse(c, a, b);

                        float oldJ = impulses[j];
                        impulses[j] = std::max(0.0f, impulses[j] + J);
                        float deltaJ = impulses[j] - oldJ;

                        a.addVelocity((deltaJ * a.getInverseMass() * c.normal));
                        a.addAngularVelocity((a.getInverseWorldInertia() * glm::cross(rA, deltaJ*c.normal)));
                        b.addVelocity(-(deltaJ * b.getInverseMass() * c.normal));
                        b.addAngularVelocity(-(b.getInverseWorldInertia() * glm::cross(rB, deltaJ*c.normal)));
                    }
                }

                for (auto& body : bodies) {
                    body.integrate(dt);
                }
                
                collisions.clear();
                impulses.clear();
            }
    };
}