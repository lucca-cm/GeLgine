#pragma once

#include <glm/glm.hpp>

#include "Collider.h"


namespace CollisionHandler {
    
    struct Simplex {
        std::array<glm::vec3, 4> points;
        uint8_t size = 0;

        Simplex& operator=(std::initializer_list<glm::vec3> list) {
            size = 0;

            for (glm::vec3 point : list)
                points[size++] = point;

            return *this;
        }

        void push(glm::vec3& point) {
            points = {point, points[0], points[1], points[2]};
            size = std::min(size + 1, 4);
        }

        glm::vec3 operator[](int i) const {
            return points[i];
        }
   };

    glm::vec3 support(const Collider& a, const Collider& b, const glm::vec3 r) {
        return a.getFurthestPoint(r) - b.getFurthestPoint(-r);
    }

    bool GJK(const Collider& a, const Collider& b) {
        glm::vec3 currentSupport = support(a, b, {1, 0, 0});

        Simplex simplex;
        simplex.push(currentSupport);
        
        glm::vec3 dir = -currentSupport;

        while (true) {
            currentSupport = support(a, b, dir);

            if (glm::dot(currentSupport, dir) <= 0)
                return false;
            
            simplex.push(currentSupport);

            if (simplexInOrigin(simplex, dir)) {
                return true;
            }
        };
    }

    bool simplexInOrigin(Simplex& s, glm::vec3& dir) {
        
        switch (s.size) {
            case 2: return lineInOrigin(s, dir);
            //case 3: return triangleInOrigin(s, dir);
            //case 4: return tetahedronInOrigin(s, dir);
        }

        return false;
    }

    bool lineInOrigin(Simplex& s, glm::vec3& dir) {
        glm::vec3 ab = s[1] - s[0];

        if (glm::dot(ab, -s[0]) > 0) {
            dir = glm::cross(glm::cross(ab, -s[0]), ab);
        }
        else {
            s = { s[0] };
            dir = -s[0];
        }
    }
};