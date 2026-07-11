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

        void bind() const {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        }

        void unbind() const {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        GLsizei count() const {
            return indexCount;
        }
};


class Mesh {
    private:
        IndexBuffer EBO;
        VertexBuffer VBO;
        VertexArray VAO;
    public:
        Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices) : EBO(indices), VBO(vertices) {
            {VertexArray::Binding arrayGuard(VAO);
                {VertexBuffer::Binding bufferGuard(VBO);
                    EBO.bind();
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
                    glEnableVertexAttribArray(0);
                }
            }  
        }

        void draw() {
            {VertexArray::Binding drawGuard(VAO);
                glDrawElements(GL_TRIANGLES, EBO.count(), GL_UNSIGNED_INT, 0); 
            }
        }
};