#pragma once

#include "Component.h"
#include "../GameObject.h"
#include "../../Physics/RigidBody.h"

namespace Gelgine {
    class RigidBodyComponent : public Component {
        private:
            size_t rigidBodyID;
            Physics::RigidBody *rb;

            void updateBodyPointer() {
                rb = &(owner->getContext()->physics.getRigidBody(rigidBodyID));
            }
        public:
            RigidBodyComponent(GameObject *owner) : Component(owner) {
                rigidBodyID = owner->getContext()->physics.createBody();
                updateBodyPointer();
            }
    };
}