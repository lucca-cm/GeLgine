#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WindowManager {
    private:
        int height, width;
        float deltaTime;
        double lastTimeUpdate, currentTimeUpdate;
        GLFWwindow* window = nullptr;
    public:
        WindowManager(int height, int width);
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

        void initTime() {
            lastTimeUpdate = glfwGetTime();
        }
        void updateTime() {
            currentTimeUpdate = glfwGetTime();
            deltaTime = static_cast<float>(currentTimeUpdate - lastTimeUpdate);
            lastTimeUpdate = currentTimeUpdate;
        }

        float getDeltaTime() const {
            return deltaTime;
        }
};