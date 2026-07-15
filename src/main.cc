#include "windowManager.h"
#include "renderer.h"
#include "Shader.h"
#include "Mesh.h"

std::vector<GLfloat> vertices = {
    0.5f, 0.5f, 0.0f, 
    0.5f, -0.5f, 0.0f, 
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f 
};

std::vector<GLuint> indices = {
    0, 1, 3,
    1, 2, 3,
};

int main() {
    WindowManager wm(800, 600);
    Renderer renderer;
    Shader basicShader("./shaders/basic.vert", "./shaders/basic.frag");
    Mesh rectangle(vertices, indices);

    renderer.toggleWireFrame();
    while (!wm.shouldExit()) {
        wm.pollEvents();
        
        renderer.clear();

        basicShader.use();
        rectangle.draw();
        wm.swapBuffers();
    }
    return 0;
}