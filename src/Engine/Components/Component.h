#pragma once

namespace Gelgine {
    class GameObject;
    class Component {
        protected:
            GameObject *owner;
        public:
            Component(GameObject *owner) : owner(owner) {}
            virtual void attach() {};
            virtual void dettach() {};
    };
}