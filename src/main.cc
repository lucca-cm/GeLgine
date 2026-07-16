#include "windowManager.h"
#include "renderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"


std::vector<GLfloat> vertices = {
    // front face
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

    // back face
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
};

std::vector<GLuint> indices = {
    // front
    0, 1, 2,
    2, 3, 0,
    // right
    1, 5, 6,
    6, 2, 1,
    // back
    5, 4, 7,
    7, 6, 5,
    // left
    4, 0, 3,
    3, 7, 4,
    // top
    3, 2, 6,
    6, 7, 3,
    // bottom
    4, 5, 1,
    1, 0, 4,
};

int main() {
    WindowManager wm(800, 600);
    Renderer renderer;
    Shader basicShader("./shaders/basic.vert", "./shaders/basic.frag");
    Mesh cube(vertices, indices);
    glm::vec3 cameraPosition(0.0f, 0.0f, 3.0f);
    glm::quat cameraRotation(1.0f, 0.0f, 0.0f, 0.0f);
    Camera camera(cameraPosition, cameraRotation, 60.0f, 800.0f / 600.0f, 0.1f, 100.0f);


    glEnable(GL_DEPTH_TEST);
    while (!wm.shouldExit()) {
        wm.pollEvents();

        float time = static_cast<float>(glfwGetTime());
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), time * glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));

        renderer.clear();

        basicShader.use();
        camera.uploadToShader(basicShader);
        basicShader.setUniform("model", model);
        basicShader.setUniform(
            "fragColor",
            glm::vec4(
                sin(time) * 0.5f + 0.5f,
                cos(time) * 0.5f + 0.5f,
                sin(time + glm::pi<float>()) * 0.5f + 0.5f,
                1.0f
            )
        );
        cube.draw();
        wm.swapBuffers();
    }
    return 0;
}