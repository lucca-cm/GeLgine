#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Collider.h"

class RigidBody {
    private:
        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec3 force;

        glm::quat rotation;
        glm::vec3 angularVeloity;
        glm::vec3 torque;

        float inverseMass;
        glm::mat3 inverseInertia;
        Collider *collider = nullptr;
        
    public:
        void addForce(glm::vec3 f) {
            force += f;
        }
        void addTorque(glm::vec3 t) {
            torque += t;
        }

        void integrateLinear(float dt) {
            velocity += inverseMass * force * dt;
            position += velocity;
        }
};