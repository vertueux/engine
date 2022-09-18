#include "posix/posix_window.h"

#include <stdexcept>

namespace opticus {

PosixWindow::PosixWindow(int w, int h, std::string name) : width{w}, height{h}, window_name{name} {
  open_window();
}

PosixWindow::~PosixWindow() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void PosixWindow::open_window() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
  glfwSetWindowUserPointer(window, this);
  glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void PosixWindow::create_window_surface(VkInstance instance, VkSurfaceKHR *surface) {
  if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
    // Print error.
  }
}

void PosixWindow::update_window() {
  while (!window.shouldClose()) {
    glfwPollEvents();
  }
}

void PosixWindow::frame_buffer_resize_callback(GLFWwindow *window, int width, int height) {
  auto window = reinterpret_cast<PosixWindow*>(glfwGetWindowUserPointer(window));
  window->framebufferResized = true;
  window->width = width;
  window->height = height;
}

}  // namespace opticus