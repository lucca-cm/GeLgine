#pragma once

#include <memory>

#include "Component.h"
#include "GraphicsComponent.h"
#include "../../Rendering/Mesh.h"

namespace Gelgine {
    template<typename T>
    using Uniform = std::pair<const char *, T>;
 
    class MeshComponent : GraphicsComponent {
        private:
            Graphics::Mesh mesh;

            void drawObject(Graphics::Renderer &ren) override {
                ren.draw(mesh);
            }
        public:
            MeshComponent(GameObject *owner, std::vector<GLfloat> vertices, std::vector<GLuint> indices) 
            : GraphicsComponent(owner), mesh(vertices, indices) {}
    };
}