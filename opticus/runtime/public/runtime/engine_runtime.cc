#include "vulkan_renderer/vulkan_renderer.h"

#include "runtime/engine_runtime.h"
#include "runtime/service_locator.h"
#include "core/platform_detection.h"

#ifdef OPTICUS_PLATFORM_WINDOWS
  #include "windows/win32_window.h"
#else 
  #include "posix/posix_window.h"
#endif

#include <iostream>

namespace opticus {

Engine::Engine() {
  switch (enumerator) {
    case E_PLATFORM_WINDOWS:
      ServiceLocator::provide_window(new Win32Window);
      break;
    default:
      // ServiceLocator::provide_window(new PosixWindow);
      return;
  }

  // ServiceLocator::provide_renderer(new VulkanRenderer);
}

void Engine::Engine::run() {
  ServiceLocator::get_window()->open_window();

  // if (!ServiceLocator::get_renderer()->initialize_renderer()) 
    return;
    
  while (is_running) {
    ServiceLocator::get_window()->update_window();

    // if (!ServiceLocator::get_renderer()->render()) 
      // return;
  }
}

} // namespace opticus