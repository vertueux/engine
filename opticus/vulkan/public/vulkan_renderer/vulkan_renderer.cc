#include "vulkan_renderer/vulkan_renderer.h"
#include "vulkan_renderer/vulkan_initialize.h"

namespace opticus {
  
// Win32Window will be modified later to make it platform specific.
bool VulkanRenderer::initialize_renderer() {
  VkApplicationInfo app_info = {};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = "Application";
  app_info.pEngineName = "Opticus";

  const char *extensions[] = {
  #ifdef OPTICUS_PLATFORM_WINDOWS
    VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
  #elif OPTICUS_PLATFORM_LINUX
  #endif
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
    VK_KHR_SURFACE_EXTENSION_NAME
  };

  const char *layers[]{
    "VK_LAYER_KHRONOS_validation"
  };

  VkInstanceCreateInfo instance_info = {};
  instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instance_info.pApplicationInfo = &app_info;
  instance_info.ppEnabledExtensionNames = extensions;
  instance_info.enabledExtensionCount = ArraySize(extensions);
  instance_info.ppEnabledLayerNames = layers;
  instance_info.enabledLayerCount = ArraySize(layers);
  VK_CHECK(vkCreateInstance(&instance_info, 0, &private_context->instance));

  auto vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(private_context->instance, "vkCreateDebugUtilsMessengerEXT");

  if (vkCreateDebugUtilsMessengerEXT)
  {
    VkDebugUtilsMessengerCreateInfoEXT debug_info = {};
    debug_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debug_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
    debug_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
    debug_info.pfnUserCallback = vk_debug_callback;

    vkCreateDebugUtilsMessengerEXT(private_context->instance, &debug_info, 0, &private_context->debug_messenger);
  }
  else
  {
    return false;
  }

  {
    #ifdef OPTICUS_PLATFORM_WINDOWS
      VkWin32SurfaceCreateInfoKHR surface_info = {};
      surface_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
      surface_info.hwnd = window.hWnd;
      surface_info.hinstance = GetModuleHandleA(0);
      VK_CHECK(vkCreateWin32SurfaceKHR(private_context->instance, &surface_info, 0, &private_context->surface));
    #elif OPTICUS_PLATFORM_LINUX
    #endif
    }

    {
      private_context->graphics_idx = -1;

      uint32_t gpu_count = 0;
      //TODO: Suballocation from Main Allocation
      VkPhysicalDevice gpus[10];
      VK_CHECK(vkEnumeratePhysicalDevices(private_context->instance, &gpu_count, 0));
      VK_CHECK(vkEnumeratePhysicalDevices(private_context->instance, &gpu_count, gpus));

      for (uint32_t i = 0; i < gpu_count; i++)
      {
        VkPhysicalDevice gpu = gpus[i];

        uint32_t queue_family_count = 0;
        //TODO: Suballocation from Main Allocation
        VkQueueFamilyProperties queue_props[10];
        vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queue_family_count, 0);
        vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queue_family_count, queue_props);

        for (uint32_t j = 0; j < queue_family_count; j++)
        {
          if (queue_props[j].queueFlags & VK_QUEUE_GRAPHICS_BIT)
          {
            VkBool32 surface_support = VK_FALSE;
            VK_CHECK(vkGetPhysicalDeviceSurfaceSupportKHR(gpu, j, private_context->surface, &surface_support));

            if (surface_support)
            {
              private_context->graphics_idx = j;
              private_context->gpu = gpu;
              break;
            }
          }
        }
      }

      if (private_context->graphics_idx < 0)
      {
        return false;
      }
    }

    {
      float queue_priority = 1.0f;

      VkDeviceQueueCreateInfo queue_info = {};
      queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      queue_info.queueFamilyIndex = private_context->graphics_idx;
      queue_info.queueCount = 1;
      queue_info.pQueuePriorities = &queue_priority;

      const char *extensions[] = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
      };

      VkDeviceCreateInfo device_info = {};
      device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
      device_info.pQueueCreateInfos = &queue_info;
      device_info.queueCreateInfoCount = 1;
      device_info.ppEnabledExtensionNames = extensions;
      device_info.enabledExtensionCount = ArraySize(extensions);

      VK_CHECK(vkCreateDevice(private_context->gpu, &device_info, 0, &private_context->device));

      vkGetDeviceQueue(private_context->device, private_context->graphics_idx, 0, &private_context->graphics_queue);
    }

    // Swapchain
    {
      uint32_t format_count = 0;
      VkSurfaceFormatKHR surface_formats[10];
      VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(private_context->gpu, private_context->surface, &format_count, 0));
      VK_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(private_context->gpu, private_context->surface, &format_count, surface_formats));

      for (uint32_t i = 0; i < format_count; i++)
      {
        VkSurfaceFormatKHR format = surface_formats[i];

        if (format.format == VK_FORMAT_B8G8R8A8_SRGB)
        {
          private_context->surface_format = format;
          break;
        }
      }

      VkSurfaceCapabilitiesKHR surface_caps = {};
      VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(private_context->gpu, private_context->surface, &surface_caps));
      uint32_t img_count = surface_caps.minImageCount + 1;
      img_count = img_count > surface_caps.maxImageCount ? img_count - 1 : img_count;

      VkSwapchainCreateInfoKHR sc_info = {};
      sc_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
      sc_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
      sc_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
      sc_info.surface = private_context->surface;
      sc_info.imageFormat = private_context->surface_format.format;
      sc_info.preTransform = surface_caps.currentTransform;
      sc_info.imageExtent = surface_caps.currentExtent;
      sc_info.minImageCount = img_count;
      sc_info.imageArrayLayers = 1;

      VK_CHECK(vkCreateSwapchainKHR(private_context->device, &sc_info, 0, &private_context->swap_chain));

      VK_CHECK(vkGetSwapchainImagesKHR(private_context->device, private_context->swap_chain, &private_context->sc_img_count, 0));
      VK_CHECK(vkGetSwapchainImagesKHR(private_context->device, private_context->swap_chain, &private_context->sc_img_count, private_context->sc_images));
    }

    {
      VkCommandPoolCreateInfo pool_info = {};
      pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
      pool_info.queueFamilyIndex = private_context->graphics_idx;
      VK_CHECK(vkCreateCommandPool(private_context->device, &pool_info, 0, &private_context->command_pool));
    }

    {
      VkSemaphoreCreateInfo sema_info = {};
      sema_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
      VK_CHECK(vkCreateSemaphore(private_context->device, &sema_info, 0, &private_context->aquire_semaphore));
      VK_CHECK(vkCreateSemaphore(private_context->device, &sema_info, 0, &private_context->submit_semaphore));
    }

    return true;
}

bool VulkanRenderer::render()
{
  uint32_t img_idx;
  VK_CHECK(vkAcquireNextImageKHR(private_context->device, private_context->swap_chain, 0, private_context->aquire_semaphore, 0, &img_idx));

  VkCommandBuffer cmd;
  VkCommandBufferAllocateInfo alloc_info = {};
  alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.commandBufferCount = 1;
  alloc_info.commandPool = private_context->command_pool;
  VK_CHECK(vkAllocateCommandBuffers(private_context->device, &alloc_info, &cmd));

  VkCommandBufferBeginInfo begin_info = OPTRenderInit::cmd_begin_info();
  VK_CHECK(vkBeginCommandBuffer(cmd, &begin_info));

  // Rendering Commands
  {
    VkClearColorValue color = {1, 1, 0, 1};
    VkImageSubresourceRange range = {};
    range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    range.layerCount = 1;
    range.levelCount = 1;

    vkCmdClearColorImage(cmd, private_context->sc_images[img_idx], VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, &color, 1, &range);
  }

  VK_CHECK(vkEndCommandBuffer(cmd));

  VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

  VkSubmitInfo submit_info = {};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.pWaitDstStageMask = &wait_stage;
  submit_info.commandBufferCount = 1;
  submit_info.pCommandBuffers = &cmd;
  submit_info.pSignalSemaphores = &private_context->submit_semaphore;
  submit_info.signalSemaphoreCount = 1;
  submit_info.pWaitSemaphores = &private_context->aquire_semaphore;
  submit_info.waitSemaphoreCount = 1;
  VK_CHECK(vkQueueSubmit(private_context->graphics_queue, 1, &submit_info, 0));

  VkPresentInfoKHR present_info = {};
  present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  present_info.pSwapchains = &private_context->swap_chain;
  present_info.swapchainCount = 1;
  present_info.pImageIndices = &img_idx;
  present_info.pWaitSemaphores = &private_context->submit_semaphore;
  present_info.waitSemaphoreCount = 1;
  VK_CHECK(vkQueuePresentKHR(private_context->graphics_queue, &present_info));

  vkFreeCommandBuffers(private_context->device, private_context->command_pool, 1, &cmd);

  return true;
}

}