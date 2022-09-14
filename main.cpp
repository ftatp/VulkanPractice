#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <iostream>

GLFWwindow* window;

void initWindow(std::string wName = "Test", const int width = 800, const int height = 600){
    glfwInit();

    // Set GLFW do not open with OpenGL
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
}

int main(){

    //Create window
    initWindow("Test window, 800, 600");

    //Loop until close
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }

    //Destroy window and stop GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}