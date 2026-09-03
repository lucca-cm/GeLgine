#pragma once

#include "../WindowManager.h"

namespace Gelgine {
    class WindowContext {
        private:
            WindowManager *window;
        public:
            WindowContext(WindowManager *window) : window(window) {}
            void setWindowSize(int width, int height) {
                window->setWindowSize(width, height);
            }
    };
}