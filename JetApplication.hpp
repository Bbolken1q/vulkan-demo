#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

class JetApplication {
public:
    void run();

private:
    const uint32_t W_WIDTH = 800;
    const uint32_t W_HEIGHT = 600;
    int validationLayers = 0;
    GLFWwindow* window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkPhysicalDeviceFeatures deviceFeatures{};
    bool enableValidationLayers = false;
    VkQueue graphicsQueue;
    VkSurfaceKHR surface;

    void initWindow();

    void createInstance();

    void initVulkan();

    void mainLoop();

    void pickPhysicalDevice();

    void cleanup();

    void createLogicalDevice();
};
