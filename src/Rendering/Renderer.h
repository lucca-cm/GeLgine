#pragma once

#include <vector>
#include <utility>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Material.h"

namespace Graphics {
    template<typename T>
    using Uniform = std::pair<const char *, T>;
    
    class Renderer {
        private:
            std::vector<Camera *> cameras;
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

            void setCurrentCamera(Camera *camera) {
                cameras.clear();
                cameras.push_back(camera);
            }
            
            void addCurrentCamera(Camera *camera) {
                cameras.push_back(camera);
            }

            template<typename... Uniforms>
            void draw(Mesh& mesh, Material& material, Uniforms&&... uniforms) {
                for (auto& camera : cameras) {
                    auto shader = material.getShader();
                    shader->use();
                    camera->updateCamera();
                    camera->uploadToShader(*shader);
                    shader->setUniform("model", mesh.getModelMatrix());
                    (shader->setUniform(uniforms.first, uniforms.second), ...);

                    mesh.draw();
                }
            }
    };
}