#pragma once

#include <vector>
#include <utility>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Graphics {
    template<typename T>
    using Uniform = std::pair<const char *, T>;
    
    class Renderer {
        private:
            Shader *currentShader = nullptr;
            bool isWireframeEnabled = false;
        public:
            void clear(glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) {
                glClearColor(color.r, color.g, color.b, color.a);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
            void toggleWireFrame() {
                if (!isWireframeEnabled) {
                    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
                    isWireframeEnabled = true;
                }
                else {
                    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
                    isWireframeEnabled = false;
                }
            }

            void begin(Camera& camera, Shader *shader) {
                currentShader = shader;
                currentShader->use();
                camera.uploadToShader(currentShader);
            }

            template<typename... Uniforms>
            void draw(Mesh& mesh, Uniforms&&... uniforms) {
                (currentShader->setUniform(uniforms.first, uniforms.second), ...);

                mesh.draw();
            }
    };
}