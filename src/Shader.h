#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>

class Shader {
    private:
        GLuint program;
        std::string readFile(const std::string& filePath) {
            std::ifstream file(filePath);
            std::stringstream buff;
            buff << file.rdbuf();

            return buff.str();
        }
    public:
        Shader(const std::string& vertexFile, const std::string& fragFile) {
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