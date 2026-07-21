#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Collider.h"

namespace Physics {
    class RigidBody {
        private:
            glm::vec3 position;
            glm::vec3 velocity;
            glm::vec3 force = glm::vec3(0.0f);

            const float rotationalDamping;
            glm::quat rotation;
            glm::vec3 angularVelocity;
            glm::vec3 torque = glm::vec3(0.0f);

            float inverseMass;
            glm::mat3 inverseInertia;
            glm::mat3 inverseWorldInertia;
            Collider *collider = nullptr;
            
        public:
            RigidBody(glm::vec3 position, glm::quat rotation, float invMass, glm::mat3 inertia,
                    float rotationalDamping, glm::vec3 velocity = glm::vec3(0.0f),
                    glm::vec3 angularVelocity = glm::vec3(0.0f))
                    : position(position), velocity(velocity), rotationalDamping(rotationalDamping),
                        rotation(rotation), angularVelocity(angularVelocity),
                        inverseMass(invMass), inverseInertia(glm::inverse(inertia))
            {
                glm::mat3 R = glm::mat3_cast(rotation);
                inverseWorldInertia = R * inverseInertia * glm::transpose(R);
            }

            void setVelocity(glm::vec3 v) {
                velocity = v;
            }
            void setCollider(Collider *c) {
                collider = c;
            }
            void addForce(glm::vec3 f) {
                force += f;
            }
            void addTorque(glm::vec3 t) {
                torque += t;
            }
            void addVelocity(glm::vec3 v) {
                velocity += v;
            }

            void integrate(float dt) {
                integrateLinear(dt);
                integrateAngular(dt);
            }

            void integrateLinear(float dt) {
                velocity += inverseMass * force * dt;
                position += velocity * dt;
                force = glm::vec3(0.0f);
            }

            void integrateAngular(float dt) {
                angularVelocity += inverseWorldInertia * torque * dt;
                angularVelocity *= powf(rotationalDamping, dt);

                rotation += glm::quat(0.0f, angularVelocity) * rotation * 0.5f * dt;
                rotation = glm::normalize(rotation);

                glm::mat3 R = glm::mat3_cast(rotation);
                inverseWorldInertia = R * inverseInertia * glm::transpose(R);
                torque = glm::vec3(0.0f);
            }

            glm::quat getRotation() {
                return rotation;
            }

            glm::vec3 getPosition() {
                return position;
            }

            glm::vec3 getVelocity() {
                return velocity;
            }

            glm::vec3 getAngularVelocity() {
                return angularVelocity;
            }

            float getMass() {
                return 1.0f/inverseMass;
            }

            Collider* getCollider() {
                return collider;
            }

            Transform getTransform() {
                Transform t;
                t.orientation = rotation;
                t.posistion = position;
                return t;
            }
    };
}