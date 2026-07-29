#include "Mesh.h"

namespace Graphics {
    VertexBuffer::VertexBuffer(std::vector<GLfloat> vertices) {
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &VBO);
    }

    void VertexBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
    }

    void VertexBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    VertexArray::VertexArray() {
        glGenVertexArrays(1, &VAO);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &VAO);
    }

    void VertexArray::bind() const {
        glBindVertexArray(VAO);
    }

    void VertexArray::unbind() const {
        glBindVertexArray(0);
    }

    IndexBuffer::IndexBuffer(std::vector<GLuint> indices) : indexCount(static_cast<GLsizei>(indices.size())) {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &EBO);
    }

    void IndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }

    void IndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices) : EBO(indices), VBO(vertices), modelMatrix(glm::mat4(1.0f)) {
        {VertexArray::Binding arrayGuard(VAO);
            {VertexBuffer::Binding bufferGuard(VBO);
                EBO.bind();
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
                glEnableVertexAttribArray(0);
            }
        }  
    }


    void Mesh::draw() {
        {VertexArray::Binding drawGuard(VAO);
            glDrawElements(GL_TRIANGLES, EBO.getCount(), GL_UNSIGNED_INT, 0); 
        }
    }

    void Mesh::setModelMatrix(const glm::mat4& matrix) {
        modelMatrix = matrix;
    }

    glm::mat4 Mesh::getModelMatrix() {
        return modelMatrix;
    }

    void Mesh::transformModelMatrix(const glm::vec3 &position, const glm::quat &rotation) {
        modelMatrix = glm::translate(glm::mat4(1.0f), position) * glm::mat4_cast(rotation);
    }
}