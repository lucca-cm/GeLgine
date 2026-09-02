#pragma once

#include "../Rendering/Rendering.h"

namespace GeLgine {
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
    };
}