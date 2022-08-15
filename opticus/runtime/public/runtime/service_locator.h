#pragma once

#include "core/window.h"
#include <memory>
#include <iostream>

namespace opticus {

class ServiceLocator {
 public:
  static inline const std::unique_ptr<Window>& get_window() { return _window; }
  
  static inline void provide(Window* window) {
    if (_window != nullptr) 
      return;
      
    _window = std::unique_ptr<Window>(window);
  }

 private:
  static inline std::unique_ptr<Window> _window = nullptr;
};

} // namespace opticus
