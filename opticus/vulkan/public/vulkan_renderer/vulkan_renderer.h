#pragma once

#ifdef _WIN32
  #define VK_USE_PLATFORM_WIN32_KHR
#endif

#include <vulkan/vulkan.h>

#ifdef _WIN32
  #include <vulkan/vulkan_win32.h>
  #include "windows/win32_window.h"
#endif

#include "core/platform_detection.h"
#include "core/window.h"
#include "core/renderer.h"

namespace opticus {

struct VkContext {
  VkInstance instance;
  VkDebugUtilsMessengerEXT debug_messenger;
  VkSurfaceKHR surface;
  VkSurfaceFormatKHR surface_format;
  VkPhysicalDevice gpu;
  VkDevice device;
  VkQueue graphics_queue;
  VkSwapchainKHR swap_chain;
  VkCommandPool command_pool;

  VkSemaphore aquire_semaphore;
  VkSemaphore submit_semaphore;

  uint32_t sc_img_count;
  VkImage sc_images[5];

  int graphics_idx;
};

class VulkanRenderer : public opticus::Renderer {
 public:
  virtual bool initialize_renderer() override;
  virtual bool render() override;

 private:
  Win32Window window;
  VkContext *private_context;
};

}