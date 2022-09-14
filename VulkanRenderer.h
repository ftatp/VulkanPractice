#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <string.h>
#include "Utilities.h"

class VulkanRenderer{
public:
    VulkanRenderer();
    int init(GLFWwindow* newWindow);
    void cleanUp();
    ~VulkanRenderer();
private:
    GLFWwindow* window;
    //Vulkan Components
    VkInstance instance;
    struct {
        VkPhysicalDevice physicalDevice;
        VkDevice logicalDevice;
    } mainDevice;

    //Vulkan Functions
    // Create Functions
    void createInstance();
    // GetFunctions
    void getPhysicalDevice();

    // Support Functions
    bool checkInstanceExtensionSupport(std::vector<const char*> * checkExtensions);
    bool checkDeviceSuitable(VkPhysicalDevice device);

    // Getter functions
    QueueFamilyIndices getQueueFamilies(VkPhysicalDevice device);
};