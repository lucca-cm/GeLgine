#include <GLFW/glfw3.h>
#include <iostream>

class WindowManager {
    private:
        GLFWwindow* window;
    public:
        WindowManager();
        ~WindowManager();

        bool shouldExit() const {
            return glfwWindowShouldClose(window);
        } 

        void pollEvents() {
            glfwPollEvents();
        }

        void swapBuffers() {
            glfwSwapBuffers(window);
        }

        bool isKeyDown(int key) {
            return glfwGetKey(window, key) == GLFW_PRESS;
        }
};