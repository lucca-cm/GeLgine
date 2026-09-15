#pragma once

#include "../Rendering/Rendering.h"
#include "../Engine/Components/Components.h"
#include "../Engine/GameObject.h"
#include "../Ensemble.h"


class MyEnsemble : public Gelgine::Ensemble {
    private:
        Gelgine::GameObject *cube;
    public:
        void onStart() override {
            auto cubeData = Graphics::Geometry::createBox(glm::vec3(0.5f, 0.5f, 0.5f));
            cube = &createObject<Gelgine::GameObject>();
            cube->addComponent<Gelgine::RigidBodyComponent>();
            auto& cubeRb = cube->getComponent<Gelgine::RigidBodyComponent>().getRigidBody();
            cubeRb.addPosition(glm::vec3(0.0f, 1.0f, 0.0f));
            auto shader = new Graphics::Shader("./shaders/basic.vert", "./shaders/basic.frag");
            Graphics::Material mat;
            mat.setShader(shader);
            cube->addComponent<Gelgine::MeshComponent>(cubeData.first, cubeData.second, mat);
            cube->getComponent<Gelgine::MeshComponent>().updateMeshTransform(cubeRb.getPosition(), cubeRb.getRotation());

            Physics::Collider *boxCollider = new Physics::BoxCollider(glm::vec3(0.5f, 0.5f, 0.5f));
            cube->getComponent<Gelgine::RigidBodyComponent>().setCollider(boxCollider);

            auto& plane = createObject<Gelgine::GameObject>();
            plane.addComponent<Gelgine::RigidBodyComponent>();
            auto& planeRb = plane.getComponent<Gelgine::RigidBodyComponent>();
            Physics::Collider *planeCollider = new Physics::PlaneCollider(glm::vec3(0.0f, 1.0f, 0.0f), -1);
            planeRb.setCollider(planeCollider);

            auto& camera = createObject<Gelgine::GameObject>();
            camera.addComponent<Gelgine::CameraComponent>();
            auto& c = camera.getComponent<Gelgine::CameraComponent>();
            c.moveTo(glm::vec3(0.0f, 0.0f, 3.0f));
            c.setCameraAsCurrent();
        }
        void onUpdate() override {}
        void onFixedUpdate() override {}
        void onRender() override {}

};