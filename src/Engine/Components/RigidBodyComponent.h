#pragma once

#include "Component.h"
#include "../GameObject.h"
#include "../../Physics/RigidBody.h"

namespace Gelgine {
    class RigidBodyComponent : public Component {
        private:
            size_t rigidBodyID;

        public:
            RigidBodyComponent(GameObject *owner) : Component(owner) {
                rigidBodyID = owner->getContext()->physics.createBody();
            }
            
            Physics::RigidBody &getRigidBody() {
                return owner->getContext()->physics.getRigidBody(rigidBodyID);
            }

            void setCollider(Physics::Collider *collider) {
                getRigidBody().setCollider(collider);
                owner->getContext()->physics.addCollider(collider);
            }
    };
}