#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

class NameApplication {
public:
    void run();

private:
    const uint32_t W_WIDTH = 800;
    const uint32_t W_HEIGHT = 600;
    GLFWwindow* window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    void initWindow();

    void createInstance();

    void initVulkan();

    void mainLoop();

    void pickPhysicalDevice();

    void cleanup();

    void createLogicalDevice();
};
