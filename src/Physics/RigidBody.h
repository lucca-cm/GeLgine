#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Collider.h"

class RigidBody {
    private:
        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec3 force;

        const float rotationalDamping;
        glm::quat rotation;
        glm::vec3 angularVelocity;
        glm::vec3 torque;

        float inverseMass;
        glm::mat3 inverseInertia;
        glm::mat3 inverseWorldInertia;
        Collider *collider = nullptr;
        
    public:
        void addForce(glm::vec3 f) {
            force += f;
        }
        void addTorque(glm::vec3 t) {
            torque += t;
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
};