#pragma once

#include "../Rendering/Rendering.h"

namespace Gelgine {
    class GraphicsContext {
        private:
            Graphics::Renderer *ren;
        public:
            GraphicsContext(Graphics::Renderer* renderer) : ren(renderer) {}
            void toggleWireFrame() {
                ren->toggleWireFrame();
            }

            void begin(Graphics::Camera& camera, Graphics::Shader* shader) {
                ren->begin(camera, shader);
            }

            template<typename... Uniforms>
            void draw(Graphics::Mesh& mesh, Uniforms&&... uniforms) {
                ren->draw(mesh, std::forward<Uniforms>(uniforms)...);
            }
            
            Graphics::Geometry::MeshData createBox(glm::vec3 halfExtents) {
                return Graphics::Geometry::createBox(halfExtents);
            }
    };
}