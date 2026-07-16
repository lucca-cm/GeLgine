#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera {
    private:
        float fov, aspectRatio, closestZ, farthestZ;
        bool outdatedView = false, outdatedProjection = false;
        glm::vec3 position;
        glm::quat rotation;
        glm::mat4 projectionMatrix, viewMatrix;
        
    public:
        Camera(glm::vec3 position, glm::quat rotation, float fov, float aspectRatio, float closeZ, float farthestZ);

        void updateCamera();
        void updateViewMatrix();
        void updateProjectionMatrix();
};