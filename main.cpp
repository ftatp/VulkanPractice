#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include "VulkanRenderer.h"

GLFWwindow* window;
VulkanRenderer vulkanRenderer;

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

    //Create Vulkan Renderer instance
    if(vulkanRenderer.init(window) == EXIT_FAILURE){
        return EXIT_FAILURE;
    }

    //Loop until close
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }

    vulkanRenderer.cleanUp();

    //Destroy window and stop GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}