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

            void setCurrentCamera(Graphics::Camera *camera) {
                ren->setCurrentCamera(camera);
            }

            void addCurrentCamera(Graphics::Camera *camera) {
                ren->addCurrentCamera(camera);
            }

            template<typename... Uniforms>
            void draw(Graphics::Mesh& mesh, Graphics::Material& material, Uniforms&&... uniforms) {
                ren->draw(mesh, material, std::forward<Uniforms>(uniforms)...);
            }
            
            Graphics::Geometry::MeshData createBox(glm::vec3 halfExtents) {
                return Graphics::Geometry::createBox(halfExtents);
            }
    };
}