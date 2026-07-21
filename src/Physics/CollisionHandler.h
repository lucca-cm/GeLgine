#pragma once

#include <vector>
#include <utility>
#include <algorithm>

#include <glm/glm.hpp>

#include "Collider.h"

namespace Physics::CollisionHandler {
    
    typedef std::pair<Collider *, Transform> ColliderInstance;
    struct Simplex {
        std::array<glm::vec3, 4> points; 
        uint8_t size = 0;

        Simplex& operator=(std::initializer_list<glm::vec3> list);
        glm::vec3 operator[](int i) const;
        
        void push(glm::vec3& point);
   };

    bool nextSimplex(Simplex& s, glm::vec3& dir);
    bool lineCase(Simplex& s, glm::vec3& dir);
    bool triangleCase(Simplex& s, glm::vec3& dir);
    bool tetrahedronCase(Simplex& s, glm::vec3& dir);

    struct FaceNormal {
        glm::vec3 normal;
        float distance;
   };

    glm::vec3 support(const ColliderInstance& a, const ColliderInstance& b, const glm::vec3 r);

    bool GJK(const ColliderInstance& a, const ColliderInstance& b);

    bool nextSimplex(Simplex& s, glm::vec3& dir);

    bool lineCase(Simplex& s, glm::vec3& dir);
    bool triangleCase(Simplex& s, glm::vec3& dir);
    bool tetrahedronCase(Simplex& s, glm::vec3& dir);

    std::pair<std::vector<FaceNormal>, size_t> getFaceNormals(const std::vector<glm::vec3>& polytope, const std::vector<size_t>& faces);
    void AddIfUniqueEdge(std::vector<std::pair<size_t, size_t>>& edges, const std::vector<size_t>& faces, size_t a, size_t b);

    CollisionManifold EPA(const Simplex& s, const ColliderInstance& a, const ColliderInstance& b);
}