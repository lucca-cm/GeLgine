#pragma once

#include <vector>
#include <utility>
#include <algorithm>

#include <glm/glm.hpp>

#include "Collider.h"

namespace Physics::CollisionHandler {
    
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

   struct FaceNormal {
        glm::vec3 normal;
        float distance;
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

            if (nextSimplex(simplex, dir)) {
                return true;
            }
        };
    }

    bool nextSimplex(Simplex& s, glm::vec3& dir) {
        
        switch (s.size) {
            case 2: return lineCase(s, dir);
            case 3: return triangleCase(s, dir);
            case 4: return tetrahedronCase(s, dir);
        }

        return false;
    }

    bool lineCase(Simplex& s, glm::vec3& dir) {
        glm::vec3 AB = s[1] - s[0];
        glm::vec3 AO = -s[0];

        if (glm::dot(AB, AO) > 0) {
            dir = glm::cross(glm::cross(AB, AO), AB);
        }
        else {
            s = { s[0] };
            dir = AO;
        }
        
        return false;
    }

    bool triangleCase(Simplex& s, glm::vec3& dir) {

        glm::vec3 AB = s[1] - s[0];
        glm::vec3 AC = s[2] - s[0];
        glm::vec3 AO = -s[0];
        glm::vec3 ABC = glm::cross(AB, AC);

        if (glm::dot(glm::cross(ABC, AC), AO) > 0) {
            if (glm::dot(AC, AO) > 0) {
                s = {s[0], s[2]};
                dir = glm::cross(glm::cross(AC, AO), AC);
            } else {
                s = {s[0], s[1]};
                return lineCase(s, dir);
            }
        } else {
            if (glm::dot(glm::cross(AB, ABC), AO) > 0) {
                s = {s[0], s[1]};
                return lineCase(s, dir);
            } else {
                if (glm::dot(ABC, AO) > 0) {
                    dir = ABC;
                } else {
                    s = {s[0], s[2], s[1]}; 
                    dir = -ABC;
                }
            }
        }
        return false;
    }

    bool tetrahedronCase(Simplex& s, glm::vec3& dir) {

        glm::vec3 AB = s[1] - s[0];
        glm::vec3 AC = s[2] - s[0];
        glm::vec3 AD = s[3] - s[0];
        glm::vec3 AO = -s[0];

        glm::vec3 ABC = glm::cross(AB, AC);
        glm::vec3 ACD = glm::cross(AC, AD);
        glm::vec3 ADB = glm::cross(AD, AB);

        if (glm::dot(ABC, AO) > 0) {
            s = {s[0], s[1], s[2]};
            return triangleCase(s, dir);
        }
        if (glm::dot(ACD, AO) > 0) {
            s = {s[0], s[2], s[3]};
            return triangleCase(s, dir);
        }
        if (glm::dot(ADB, AO) > 0) {
            s = {s[0], s[3], s[1]};
            return triangleCase(s, dir);
        }

        return true;
    }

    std::pair<std::vector<FaceNormal>, size_t> getFaceNormals(const std::vector<glm::vec3>& polytope, const std::vector<size_t>& faces) {
        std::vector<FaceNormal> normals;
        size_t minTriangle = 0;
        float  minDistance = FLT_MAX;

        for (size_t i = 0; i < faces.size(); i += 3) {
            glm::vec3 a = polytope[faces[i]];
            glm::vec3 b = polytope[faces[i + 1]];
            glm::vec3 c = polytope[faces[i + 2]];

            FaceNormal face; 
            face.normal = glm::normalize(glm::cross(b - a, c - a));
            face.distance = glm::dot(face.normal, a);

            if (face.distance < 0) {
                face.normal *= -1;
                face.distance *= -1;
            }

            normals.emplace_back(face);

            if (face.distance < minDistance) {
                minTriangle = i / 3;
                minDistance = face.distance;
            }
        }

        return { normals, minTriangle };
    }

    void AddIfUniqueEdge(std::vector<std::pair<size_t, size_t>>& edges, const std::vector<size_t>& faces, size_t a, size_t b) {
        auto reverse = std::find(
            edges.begin(),
            edges.end(),
            std::make_pair(faces[b], faces[a])
        );
    
        if (reverse != edges.end())
            edges.erase(reverse);
        else 
            edges.emplace_back(faces[a], faces[b]);
    }

    CollisionManifold EPA(const Simplex& s, const Collider& a, const Collider& b) {
        std::vector<glm::vec3> polytope(s.points.begin(), s.points.end());
        std::vector<uint8_t> faces = {
            0, 1, 2,
            0, 3, 1,
            0, 2, 3,
            1, 3, 2
        };

    }
};