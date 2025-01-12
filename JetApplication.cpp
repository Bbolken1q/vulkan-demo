#include "JetApplication.hpp"
#include "helperFunctions.hpp"

void JetApplication::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void JetApplication::initWindow() { // initialize glfw window (WINDOW SUPPOSEDLY WORKS ONLY AFTER DRAW ON WAYLAND, DO NOT )
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(this->W_HEIGHT, this->W_WIDTH, "Vulkan", nullptr, nullptr);
    std::cout<<"initialized window" << std::endl;
}

void JetApplication::createInstance() /*
* vulkan-tutorial.com said to do this so i did
* Initializes a bunch of important stuff vulkan needs (version data & such)
*/
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;
    VkResult result = vkCreateInstance(&createInfo, nullptr, &this->instance);
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}



void JetApplication::initVulkan() {
    createInstance();
    pickPhysicalDevice();
    createLogicalDevice();
}

void JetApplication::mainLoop() {
    while (!glfwWindowShouldClose(this->window)) {
        glfwPollEvents();
    }
}

void JetApplication::pickPhysicalDevice() { // programmer went to jail for rendering on cpu // TODO: PICK A FUCKING GPU
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(this->instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
    for (const auto& device : devices) {
        int max_score = 0;
        std::cout << device <<", score: " << rateDeviceSuitability(device) << std::endl;
        if (isDeviceSuitable(device)) {
            if(rateDeviceSuitability(device) > max_score) {
                physicalDevice = device;
            }
        }
    }

    std::cout << physicalDevice << std::endl;

    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

void JetApplication::cleanup() { // TODO: destroy stuff that needs to be destroyed because i only leak out of my peanits
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void JetApplication::createLogicalDevice() {

}
