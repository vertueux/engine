#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>


#include "core/window.h"


namespace opticus {

class PosixWindow : public Window {
 public:
  PosixWindow(int w, int h, std::string name);
  ~PosixWindow();

  PosixWindow(const PosixWindow &) = delete;
  PosixWindow &operator=(const PosixWindow &) = delete;

  bool should_close() { return glfwWindowShouldClose(window); }
  VkExtent2D get_extent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }
  bool window_resized() { return frame_buffer_resized; }
  void reset_window_resized_flag() { frame_buffer_resized = false; }

  virtual void open_window() = 0;
  virtual void update_window() = 0;

  GLFWwindow *get_GLFW_window() const { return window; }

  void create_window_surface(VkInstance instance, VkSurfaceKHR *surface);

 private:
  static void frame_buffer_resize_callback(GLFWwindow *window, int width, int height);

  int width;
  int height;
  bool frame_buffer_resized = false;

  std::string window_name;
  GLFWwindow *window;
};
}  // namespace opticus