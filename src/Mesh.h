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

class VertexArray {
    private:
        GLuint VAO;
    public:
        VertexArray() {
            glGenVertexArrays(1, &VAO);
        }

        ~VertexArray() {
            glDeleteVertexArrays(1, &VAO);
        }

        void bind() const {
            glBindVertexArray(VAO);
        }

        void unbind() const {
            glBindVertexArray(0);
        }

        class Binding {
            private:
                const VertexArray& vertexArr;
            public:
                explicit Binding(const VertexArray& vao) : vertexArr(vao) {
                    vertexArr.bind(); 
                }

                ~Binding() {
                    vertexArr.unbind();
                }
        };
};

class IndexBuffer {
    private:
        GLuint EBO;
        GLsizei indexCount;
    public:
        IndexBuffer(std::vector<GLuint> indices) : indexCount(static_cast<GLsizei>(indices.size())) {
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        ~IndexBuffer() {
            glDeleteBuffers(1, &EBO);
        }

        void bind() {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        }

        void unbind() {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
};

