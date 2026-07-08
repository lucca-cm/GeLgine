#include <vector>

#include <glad/glad.h>

class VertexBuffer {
    private:
        GLuint VBO;
    public:
        VertexBuffer(std::vector<GLfloat> vertices) {
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        ~VertexBuffer() {
            glDeleteBuffers(1, &VBO);
        }

        void bind() const {
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
        }

        void unbind() const {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        class Binding {
            private:
                const VertexBuffer& vertexBuf;
            public:
                explicit Binding(const VertexBuffer& vbo) : vertexBuf(vbo) {
                    vertexBuf.bind(); 
                }

                ~Binding() {
                    vertexBuf.unbind();
                }
        };
};