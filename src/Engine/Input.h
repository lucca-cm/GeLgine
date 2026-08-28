#pragma once

#include "../WindowManager.h"

namespace GeLgine {
    enum class Key : int {
        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,

        W = GLFW_KEY_W,
        S = GLFW_KEY_S,
        D = GLFW_KEY_D,

        Space = GLFW_KEY_SPACE,
        Escape = GLFW_KEY_ESCAPE,

        Left = GLFW_KEY_LEFT,
        Right = GLFW_KEY_RIGHT,
        Up = GLFW_KEY_UP,
        Down = GLFW_KEY_DOWN
    };

    class Input {
        private:
            WindowManager *window;
        public: 
            bool isKeyDown(Key key) {
                return window->isKeyDown(static_cast<int>(key));
            }
    };
}