#include <glm/gtc/matrix_transform.hpp>

#include "WindowManager.h"
#include "Rendering/Rendering.h"
#include "Physics/PhysicsEngine.h"

int main() {
    WindowManager wm(800, 600);
    Graphics::Renderer renderer;
    Graphics::Shader basicShader("./shaders/basic.vert", "./shaders/basic.frag");
    auto boxData = Graphics::Geometry::createBox({0.5f, 0.5f, 0.5f});
    Graphics::Mesh cube(boxData.first, boxData.second);

    auto sphereData = Graphics::Geometry::createSphere(0.5f, 16, 32);
    Graphics::Mesh sphere(sphereData.first, sphereData.second);

    Physics::PhysicsWorld pm;

    Physics::BoxCollider boxCollider(glm::vec3(0.5f, 0.5f, 0.5f));
    Physics::SphereCollider sphereCollider(0.5f);

    glm::vec3 bodyPos(0.0f, 1.0f, 0.0f);
    glm::quat rotation(1.0f, 0.0f, 0.0f, 0.0f);
    glm::mat3 inertia(1.0f);
    Physics::RigidBody rb(bodyPos, rotation, 1, inertia, 1);

    glm::vec3 bPos(2.0f, 1.0f, 0.0f);
    Physics::RigidBody rigidb(bPos, rotation, 1, inertia, 1);
    rigidb.setCollider(&boxCollider);
    rb.setCollider(&sphereCollider);

    glm::mat3 Iner(0.0f);
    Physics::RigidBody plane(glm::vec3(0.0f), rotation, 0, inertia, 0);
    Physics::PlaneCollider planeCollider(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
    plane.setCollider(&planeCollider);

    auto aId = pm.addBody(rigidb);
    auto bId = pm.addBody(rb);
    pm.addBody(plane);
    pm.addCollider(&planeCollider);
    pm.addCollider(&boxCollider);
    pm.addCollider(&sphereCollider);


    glm::vec3 cameraPosition(0.0f, 0.0f, 3.0f);
    glm::quat cameraRotation(1.0f, 0.0f, 0.0f, 0.0f);
    Graphics::Camera camera(cameraPosition, cameraRotation, 60.0f, 800.0f / 600.0f, 0.1f, 100.0f);

    glm::vec3 gravity(0.0f, -5.0f, 0.0f);

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
        a.addForce(gravity);
        b.addForce(gravity);
        pm.step(wm.getDeltaTime());
        
        glm::vec3 deltaPos(0.0f);
        if (wm.isKeyDown(GLFW_KEY_D)) {
            deltaPos.x += 0.1f;
        }
        if (wm.isKeyDown(GLFW_KEY_A)) {
            deltaPos.x -= 0.1f;
        }
        if (wm.isKeyDown(GLFW_KEY_W)) {
            deltaPos.y += 0.1f;
        }
        if (wm.isKeyDown(GLFW_KEY_S)) {
            deltaPos.y -= 0.1f;
        }
        
        camera.moveBy(deltaPos);

        camera.updateCamera();
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
        
        sphere.transformModelMatrix(b.getPosition(), b.getRotation());
        basicShader.setUniform("model", sphere.getModelMatrix());
        basicShader.setUniform(
            "fragColor",
            (colliding ? glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) : glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))
        );
        sphere.draw();
        wm.swapBuffers();
    }
    return 0;
}