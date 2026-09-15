#pragma once

#include <memory>

#include "Component.h"
#include "GraphicsComponent.h"
#include "../../Rendering/Mesh.h"

namespace Gelgine {
    template<typename T>
    using Uniform = std::pair<const char *, T>;
 
    class MeshComponent : public GraphicsComponent {
        private:
            Graphics::Mesh mesh;
            Graphics::Material material;

            void drawObject(Graphics::Renderer &ren) override {
                ren.draw(mesh, material, Graphics::Uniform<glm::vec4>{"fragColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)});
            }
        public:
            MeshComponent(GameObject *owner, std::vector<GLfloat> vertices, std::vector<GLuint> indices, Graphics::Material material) 
            : GraphicsComponent(owner), mesh(vertices, indices), material(material) {}
            
            void updateMeshTransform(glm::vec3 position, glm::quat rotation) {
                mesh.transformModelMatrix(position, rotation);
            }
    };
}