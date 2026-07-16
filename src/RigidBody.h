#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Collider.h"

class RigidBody {
    private:
        glm::vec3 position;
        glm::quat rotation;
        Collider *collider = nullptr;

    public:
        
};