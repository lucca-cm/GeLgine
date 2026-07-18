#include "Shader.h"

namespace Graphics {
    Shader::Shader(const std::string &vertexFile, const std::string &fragFile) {
        GLuint vertex, fragment;

        std::string vertexShader = readFile(vertexFile);
        std::string fragShader = readFile(fragFile);
        
        const char *vsSource = vertexShader.c_str();
        const char *fsSource = fragShader.c_str();

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vsSource, NULL);
        glCompileShader(vertex);

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fsSource, NULL);
        glCompileShader(fragment);

        program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);
        
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    Shader::~Shader() {
        glDeleteProgram(program);
    }

    bool Shader::setUniform(const std::string& uniformName, const glm::vec4& vector) const {
        GLint location = glGetUniformLocation(program, uniformName.c_str());
        if (location == -1)
            return false;
        use();
        glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
        return true;
    }

    bool Shader::setUniform(const std::string& uniformName, const glm::mat4& matrix) const {
        GLint location = glGetUniformLocation(program, uniformName.c_str());
        if (location == -1)
            return false;
        use();
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
        return true;
    }

    void Shader::use() const {
        glUseProgram(program);
    }
}