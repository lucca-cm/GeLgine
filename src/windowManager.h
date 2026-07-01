#include <iostream>

#include <GLFW/glfw3.h>
#include <GL/glew.h>

class WindowManager {
    private:
        GLFWwindow* window = nullptr;
    public:
        WindowManager();
        ~WindowManager();

        bool shouldExit() const {
            if (!window) 
                return true;
            return glfwWindowShouldClose(window);
        } 

        void pollEvents() {
            glfwPollEvents();
        }

        void swapBuffers() {
            glfwSwapBuffers(window);
        }

        bool isKeyDown(int key) const {
            return glfwGetKey(window, key) == GLFW_PRESS;
        }
};