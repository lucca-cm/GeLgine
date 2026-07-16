#pragma once

#include <vector>

#include <glad/glad.h>

class VertexBuffer {
    private:
        GLuint VBO;
    public:
        VertexBuffer(std::vector<GLfloat> vertices); 
        ~VertexBuffer(); 

        void bind() const;
        void unbind() const; 

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
        VertexArray(); 
        ~VertexArray();

        void bind() const; 
        void unbind() const;

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
        IndexBuffer(std::vector<GLuint> indices);
        ~IndexBuffer();

        void bind() const; 
        void unbind() const;
        GLsizei getCount() const {
            return indexCount;
        }
};

class Mesh {
    private:
        IndexBuffer EBO;
        VertexBuffer VBO;
        VertexArray VAO;
    public:
        Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices);
        void draw();
};