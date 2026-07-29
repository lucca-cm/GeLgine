#include <glm/gtc/matrix_transform.hpp>

#include "WindowManager.h"
#include "./Rendering/Renderer.h"
#include "./Rendering/Shader.h"
#include "./Rendering/Mesh.h"
#include "./Rendering/Camera.h"
#include "./Physics/RigidBody.h"
#include "./Physics/BoxCollider.h"
#include "./Physics/CollisionHandler.h"
#include "./Physics/PhysicsWorld.h"

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
    Graphics::Renderer renderer;
    Graphics::Shader basicShader("./shaders/basic.vert", "./shaders/basic.frag");
    Graphics::Mesh cube(vertices, indices);
    Physics::PhysicsWorld pm;

    Physics::BoxCollider boxCollider(glm::vec3(0.5f, 0.5f, 0.5f));

    glm::vec3 bodyPos(0.0f);
    glm::quat rotation(1.0f, 0.0f, 0.0f, 0.0f);
    glm::mat3 inertia(1.0f);
    Physics::RigidBody rb(bodyPos, rotation, 1, inertia, 1);

    glm::vec3 bPos(2.0f, 0.0f, 0.0f);
    Physics::RigidBody rigidb(bPos, rotation, 1, inertia, 1);
    rigidb.setCollider(&boxCollider);
    rb.setCollider(&boxCollider);

    auto aId = pm.addBody(rigidb);
    auto bId = pm.addBody(rb);
    pm.addCollider(&boxCollider);

    glm::vec3 cameraPosition(0.0f, 0.0f, 3.0f);
    glm::quat cameraRotation(1.0f, 0.0f, 0.0f, 0.0f);
    Graphics::Camera camera(cameraPosition, cameraRotation, 60.0f, 800.0f / 600.0f, 0.1f, 100.0f);

    //glm::vec3 gravity(0.0f, -9.81f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    
    wm.initTime();
    
    auto& a = pm.getRigidBody(aId);
    auto& b = pm.getRigidBody(bId);

    while (!wm.shouldExit()) {
        wm.pollEvents();

        wm.updateTime();

        std::cout << "FPS: " << 1/wm.getDeltaTime() << std::endl;

        glm::vec3 force(0.0f);
        
        if (wm.isKeyDown(GLFW_KEY_RIGHT)) {
            force.x += 1.0f;
        }
        if (wm.isKeyDown(GLFW_KEY_LEFT)) {
            force.x -= 1.0f;
        }
        if (wm.isKeyDown(GLFW_KEY_UP)) {
            force.z += 1.0f;
        }
        if (wm.isKeyDown(GLFW_KEY_DOWN)) {
            force.z -= 1.0f;
        }



        a.addForce(force);
        pm.step(wm.getDeltaTime());
        
        bool colliding = Physics::CollisionHandler::GJK({a.getCollider(), a.getTransform()},
                                                        {b.getCollider(), b.getTransform()}).first;
        cube.transformModelMatrix(a.getPosition(), a.getRotation());
        renderer.clear();

        basicShader.use();
        camera.uploadToShader(basicShader);
        basicShader.setUniform("model", cube.getModelMatrix());
        basicShader.setUniform(
            "fragColor",
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
        );
        cube.draw();
        
        cube.transformModelMatrix(b.getPosition(), b.getRotation());
        basicShader.setUniform("model", cube.getModelMatrix());
        basicShader.setUniform(
            "fragColor",
            (colliding ? glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) : glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))
        );
        cube.draw();
        wm.swapBuffers();
    }
    return 0;
}