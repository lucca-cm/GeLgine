#pragma once

#include "Shader.h"

namespace Graphics {
    class Material {
        private:
            Shader *shader;
        public:
            void setShader(Shader *shader) {
                this->shader = shader;
            }
            Shader *getShader() {
                return shader;
            }
    };
}