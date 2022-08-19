#pragma once

#include <vulkan/vulkan.h>
#include <iostream>

#define ArraySize(arr) sizeof((arr)) / sizeof((arr[0]))

#define VK_CHECK(result)                                  \
  if (result != VK_SUCCESS)                               \
  {                                                       \
    std::cout << "Vulkan Error: " << result << std::endl; \
    __debugbreak();                                       \
    return false;                                         \
  }

static VKAPI_ATTR VkBool32 VKAPI_CALL vk_debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT msgSeverity,
    VkDebugUtilsMessageTypeFlagsEXT msgFlags,
    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
    void *pUserData)
{
  std::cout << "Validation Error: " << pCallbackData->pMessage << std::endl;
  return false;
}

namespace opticus {

class OPTRenderInit {
 public:
  VkCommandBufferBeginInfo cmd_begin_info()
  {
    VkCommandBufferBeginInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    return info;
  }
};

}