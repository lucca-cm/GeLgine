#pragma once


#include "../Game.h"

#include "MyEnsemble.h"

class MyGame : public Gelgine::Game {
    private:
        Physics::RigidBody *a;
        Graphics::Mesh *boxMesh;
        Graphics::Camera *camera;
        Graphics::Shader *shader;
    public:
        MyGame() : Game(1280, 720, 1/60.0f) {}

        void onStart() override {
            addEnsemble<MyEnsemble>("Demo ensemble"); 
            getEnsemble("Demo ensemble")->onStart();
        }   

        void onUpdate(float dt) override {

        }

        void onFixedUpdate() override {
        }
        
        void onRender() override {
        }

};