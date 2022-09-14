#include "VulkanRenderer.h"

VulkanRenderer::VulkanRenderer(){

}

int VulkanRenderer::init(GLFWwindow* window){
    window = window;
    
    try{
        createInstance();
    }
    catch(const std::runtime_error e){
        printf("Error : %s\n", e.what());
        return EXIT_FAILURE;
    }
    return 0;
}


VulkanRenderer::~VulkanRenderer(){
    
}

void VulkanRenderer::createInstance(){
    // Information about the application
    // Most data here doesn't affect the program and is for developer convenience
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan App";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0 ,0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // Creation Information for a VkInstance
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO; // stype = structure type
    createInfo.pApplicationInfo = &appInfo;

    // Create list to hold instance extensions
    std::vector<const char*> instanceExtensions = std::vector<const char*>();
    // Set up extensions instance will use
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;                                                

    // Get GLFW extensions
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount); // Names of glfw extensions

    // Add GLFW extensions to list of extensions
    for(size_t i = 0; i < glfwExtensionCount; i++){
        instanceExtensions.push_back(glfwExtensions[i]);
    }

    createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
    createInfo.ppEnabledExtensionNames = instanceExtensions.data();
    
    // TODO: Set up Validation layers that the instance will use;
    createInfo.enabledLayerCount = false;// Validation
    createInfo.ppEnabledLayerNames = nullptr;

    // Create instance
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    if(result != VK_SUCCESS){
        throw std::runtime_error("Failed to create instance");
    }
}