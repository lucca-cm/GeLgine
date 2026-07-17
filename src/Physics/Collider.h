#pragma once

class Collider {
    public:
        virtual ~Collider() = default;
        virtual bool collidedWith(const Collider& object) const = 0;   
};