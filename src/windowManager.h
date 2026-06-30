#include <GLFW/glfw3.h>
#include <iostream>

class WindowManager {
    private:
        GLFWwindow* window;
    public:
        WindowManager();
        ~WindowManager();
        bool shouldExit() {
            return glfwWindowShouldClose(window);
        } 
};