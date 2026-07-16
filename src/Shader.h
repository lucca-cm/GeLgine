#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

        bool setUniform(const std::string& uniformName, const glm::vec4& vector) const;
        bool setUniform(const std::string& uniformName, const glm::mat4& matrix) const;

        void use(); 
        GLuint& getProgram() {
            return program;
        }
};