#pragma once

#include "../Game.h"

class MyGame : public Gelgine::Game {
    private:
        Physics::RigidBody *a;
        Graphics::Mesh *boxMesh;
        Graphics::Camera *camera;
        Graphics::Shader *shader;
    public:
        MyGame() : Game(1280, 720, 1/60.0f) {}

        void onStart() override {
            Physics::Collider *boxCollider = new Physics::BoxCollider(glm::vec3(0.5f, 0.5f, 0.5f));
            auto* box = new Physics::RigidBody();
            box->setPosition(glm::vec3(0.0f, 2.0f, 0.0f));
            box->setCollider(boxCollider);
            auto aPlace = ctx->physics.addBody(*box);
            ctx->physics.addCollider(boxCollider);
            auto boxData = ctx->graphics.createBox({0.5f, 0.5, 0.5f});
            boxMesh =  new Graphics::Mesh(boxData.first, boxData.second);
            ctx->physics.createPlane(glm::vec3(0.0f, 1.0f, 0.0f), -1.0f);
            shader = new Graphics::Shader("./shaders/basic.vert", "./shaders/basic.frag");
            camera = new Graphics::Camera(60.0f, 1280.0f/720.0f);
            camera->moveTo(glm::vec3(0.0f, 0.0f, 3.0f));
            camera->forceUpdateCamera();
            a = &(ctx->physics.getRigidBody(aPlace));
        }   

        void onUpdate(float dt) override {

        }

        void onFixedUpdate() override {
            boxMesh->transformModelMatrix(a->getPosition(), a->getRotation());
            glm::vec3 force(0.0f);
            
            if (ctx->input.isKeyDown(Gelgine::Key::Right)) {
                force.x += 1.0f;
            }
            if (ctx->input.isKeyDown(Gelgine::Key::Left)) {
                force.x -= 1.0f;
            }
            if (ctx->input.isKeyDown(Gelgine::Key::Up)) {
                force.z += 1.0f;
            }
            if (ctx->input.isKeyDown(Gelgine::Key::Down)) {
                force.z -= 1.0f;
            }

            glm::vec3 delta(0.0f);
            if (ctx->input.isKeyDown(Gelgine::Key::D)) {
                delta.x += 1.0f;
            }
            if (ctx->input.isKeyDown(Gelgine::Key::A)) {
                delta.x -= 1.0f;
            }
            if (ctx->input.isKeyDown(Gelgine::Key::W)) {
                delta.z += 1.0f;
            }
            if (ctx->input.isKeyDown(Gelgine::Key::S)) {
                delta.z -= 1.0f;
            }

            camera->moveBy(delta);
            camera->updateCamera();

            a->addForce(force);
            a->addForce(glm::vec3(0.0f, -9.81f, 0.0f));
        }
        
        void onRender() override {
            boxMesh->transformModelMatrix(a->getPosition(), a->getRotation());
            ctx->graphics.begin(*camera, shader);
            ctx->graphics.draw(*boxMesh, 
                Graphics::Uniform<glm::mat4>{"model", boxMesh->getModelMatrix()}, 
                Graphics::Uniform<glm::vec4>{"fragColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)});
        }

};