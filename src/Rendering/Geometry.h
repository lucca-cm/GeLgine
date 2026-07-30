#pragma once

#include <vector>
#include <utility>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace Graphics::Geometry {
                      // Vertices        ,  Indices
    typedef std::pair<std::vector<GLfloat>, std::vector<GLuint>> MeshData;

    MeshData createBox(glm::vec3 halfExtent);
    MeshData createSphere(float radius, size_t rings, size_t segments);
}