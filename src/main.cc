#include "windowManager.h"

int main() {
    WindowManager wm;
    
    while (!wm.shouldExit()) {
        wm.pollEvents();
        
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        wm.swapBuffers();
    }
    return 0;
}