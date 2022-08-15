#include "runtime/engine_runtime.h"
#include "core/service_locator.h"
#include "core/platform_detection.h"

#ifdef OPTICUS_PLATFORM_WINDOWS
  #include "windows/win32_window.h"
#endif

#include <iostream>

namespace opticus {

Engine::Engine() {
  switch (opticus::enumerator) {
    case opticus::E_PLATFORM_WINDOWS:
      opticus::ServiceLocator::provide(new Win32Window);
      break;
    default:
      return;
  }
}

void Engine::Engine::run() {
  opticus::ServiceLocator::get_window()->open_window();
  opticus::ServiceLocator::get_window()->update_window();
}

} // namespace opticus