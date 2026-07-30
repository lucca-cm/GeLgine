#include "Geometry.h"

namespace Graphics::Geometry {
    MeshData createBox(glm::vec3 halfExtent) {
        std::vector<GLfloat> vertices = {
            -halfExtent.x, -halfExtent.y, -halfExtent.z,
             halfExtent.x, -halfExtent.y, -halfExtent.z,
             halfExtent.x,  halfExtent.y, -halfExtent.z,
            -halfExtent.x,  halfExtent.y, -halfExtent.z,
            -halfExtent.x, -halfExtent.y,  halfExtent.z,
             halfExtent.x, -halfExtent.y,  halfExtent.z,
             halfExtent.x,  halfExtent.y,  halfExtent.z,
            -halfExtent.x,  halfExtent.y,  halfExtent.z,
        };

        std::vector<GLuint> indices = {
            0, 1, 2,
            2, 3, 0,
            5, 4, 7,
            7, 6, 5,
            4, 0, 3,
            3, 7, 4,
            1, 5, 6,
            6, 2, 1,
            4, 5, 1,
            1, 0, 4,
            3, 2, 6,
            6, 7, 3
        };
        
        return {vertices, indices};
    }

    MeshData createSphere(float radius, size_t rings, size_t segments) {
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;

        for (size_t i = 0; i <= rings; i++) {
            float phi = glm::pi<float>() * i / rings;

            for (size_t j = 0; j <= segments; j++) {
                float theta = 2.0f * glm::pi<float>() * j / segments;

                vertices.push_back(radius * sin(phi) * cos(theta));
                vertices.push_back(radius * cos(phi));
                vertices.push_back(radius* sin(phi) * sin(theta));
            
                if (i < rings && j < segments) {
                    int current = i * (segments + 1) + j;
                    int next = current + segments + 1;

                    indices.push_back(current);
                    indices.push_back(next);
                    indices.push_back(current + 1);
                    indices.push_back(current + 1);
                    indices.push_back(next);
                    indices.push_back(next + 1);
                }
            }
        }

        return {vertices, indices};
    }
}