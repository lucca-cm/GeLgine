#include "PhysicsWorld.h"

namespace Physics {
    float PhysicsWorld::computeBias(float penetrationDepth, float dt) {
        return  (beta / dt) * std::max(0.0f, penetrationDepth - slop);
    }

    size_t Physics::PhysicsWorld::addBody(const RigidBody& b) {
        bodies.push_back(b);

        return bodies.size() - 1;
    }

    size_t Physics::PhysicsWorld::addCollider(Collider *c) {
        colliders.push_back(c);

        return colliders.size() - 1;
    }
    
    RigidBody& Physics::PhysicsWorld::getRigidBody(size_t id) {
        return bodies[id];
    }

    void Physics::PhysicsWorld::cacheCurrentAABB() {
        for (auto& rb : bodies) {
            aabbCache.push_back(rb.getBodyAABB());
        }
    }

    void Physics::PhysicsWorld::step(float dt) {
        cacheCurrentAABB();
        for (size_t i = 0; i < bodies.size(); ++i) {
            for (size_t j = i + 1; j < bodies.size(); ++j) {
                auto& a = bodies[i];
                auto& b = bodies[j];
                
                if (a.getColliderType() == ColliderType::Plane && b.getColliderType() == ColliderType::Plane)
                    continue;
                if (a.getColliderType() == ColliderType::Plane) {
                    auto v = CollisionHandler::planeCollision(static_cast<PlaneCollider *>(a.getCollider()), b);
                    if (v.has_value()) {
                        auto f = *v;
                        f.second = &a;
                        collisions.push_back(f);
                        impulses.push_back(0.0f);
                    }
                } 
                else if (b.getColliderType() == ColliderType::Plane) {
                    auto v = CollisionHandler::planeCollision(static_cast<PlaneCollider *>(b.getCollider()), a);
                    if (v.has_value()) {
                        auto f = *v;
                        f.second = &b;
                        collisions.push_back(f);
                        impulses.push_back(0.0f);
                    }
                }
                else if (CollisionHandler::checkBroadPhase(aabbCache[i], aabbCache[j])) {
                    auto v = CollisionHandler::checkCollision(a, b);
                    collisions.insert(collisions.end(), v.begin(), v.end());
                    for (auto&& _ : v) {
                        impulses.push_back(0.0f);
                    }
                }
            }
        }
        
        for (size_t i = 0; i < velocityIterations; i++) {
            for (size_t j = 0; j < collisions.size(); j++) {
                auto& c = collisions[j];
                
                RigidBody& a = *c.first;
                RigidBody& b = *c.second;


                float J = CollisionHandler::solveImpulse(c, computeBias(c.penetrationDepth, dt), a, b);

                float oldJ = impulses[j];
                impulses[j] = std::max(0.0f, impulses[j] + J);
                float deltaJ = impulses[j] - oldJ;

                a.applyImpulse(c, deltaJ);
                b.applyImpulse(c, -deltaJ);
            }
        }

        for (auto& body : bodies) {
            body.integrate(dt);
        }
        
        collisions.clear();
        impulses.clear();
        aabbCache.clear();
    }
}