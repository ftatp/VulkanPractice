#include "VulkanRenderer.h"

VulkanRenderer::VulkanRenderer(){

}

int VulkanRenderer::init(GLFWwindow* window){
    window = window;
    
    try{
        createInstance();
        getPhysicalDevice();
    }
    catch(const std::runtime_error e){
        printf("Error : %s\n", e.what());
        return EXIT_FAILURE;
    }
    return 0;
}
void VulkanRenderer::cleanUp(){
    vkDestroyInstance(instance, nullptr);
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

    // Check Instance extensions supported
    if(!checkInstanceExtensionSupport(&instanceExtensions)){
        throw std::runtime_error("VkInstance does not support required extensions");
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

void VulkanRenderer::getPhysicalDevice(){
    // Enumerate physhical devices the vkInstance can access
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    // If no devices available, then nono support Vulkan
    if(deviceCount == 0){
        throw std::runtime_error("Con't find GPUs that support Vulkan Instance");
    }

    // Get list of physical devices
    std::vector<VkPhysicalDevice> deviceList(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, deviceList.data());

    for(const auto &device : deviceList){
        if(checkDeviceSuitable(device)){
            mainDevice.physicalDevice = device;
            break;
        }
    }
}

bool VulkanRenderer::checkInstanceExtensionSupport(std::vector<const char*> *checkExtensions){
    //Need to get nuber of extensions to create array of correct size to hold extensions
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    // Create a list of VKExtenxionsProperties usin count
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    // Check if given extensions are in list of available extensions
    for(const auto &checkExtension : *checkExtensions){
        bool hasExtension = false;
        for(const auto &extension : extensions){
            if(strcmp(checkExtension, extension.extensionName)){
                hasExtension = true;
                break;
            }
        }

        if(hasExtension == false){
            return false;
        }
    }

    return true;
}

bool VulkanRenderer::checkDeviceSuitable(VkPhysicalDevice device){
    // // Information about the device itself
    // VkPhysicalDeviceProperties deviceProperties;
    // vkGetPhysicalDeviceProperties(device, &deviceProperties);

    // // Information about what the device can do (geo shader, tess shader, wide lines, etc)
    // VkPhysicalDeviceFeatures deviceFeatures;
    // vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    QueueFamilyIndices indices = getQueueFamilies(device);

    return indices.isValid();
}

QueueFamilyIndices VulkanRenderer::getQueueFamilies(VkPhysicalDevice device){
    QueueFamilyIndices indices;

    // Get all Queue family property info for the given device
    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilyList(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyList.data());

    // Go through each queue family and check if it has at least 1 of the required types of queue
    int i = 0;
    for(const auto &queueFamily : queueFamilyList){
        // Check if queue family has at leasts 1 queue in that family (could have no queues).
        // Queue can be multiple types defined through bitfield. Need to bitwise and with VK_QUEUE_*_BIT 
        // to check if has required type
        if(queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT){
            indices.graphicsFamily = i; // If Queue family is valid, then get index
        }

        if(indices.isValid()){
            break;
        }

        i++;
    }

    return indices;
}