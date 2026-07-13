#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

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
        Shader(const std::string& vertexFile, const std::string& fragFile);
        ~Shader();

        bool setUniform(std::string& uniformName, glm::vec4& vector);

        void use(); 
        GLuint& getProgram() {
            return program;
        }
};