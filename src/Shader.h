#include <glad/glad.h>

class Shader {
    private:
        GLuint program;

    public:
        Shader(const char *vsSource, const char *fsSource) {
            GLuint vertex, fragment;
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
        ~Shader() {
            glDeleteProgram(program);
        }
        void use() {
            glUseProgram(program);
        }

        GLuint& getProgram() {
            return program;
        }
};