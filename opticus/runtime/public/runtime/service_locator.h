#pragma once

#include <memory>
#include <iostream>

#include "core/window.h"
#include "core/renderer.h"

namespace opticus {

class ServiceLocator {
 public:
  static inline const std::unique_ptr<Window>& get_window() { return _window; }
  static inline const std::unique_ptr<Renderer>& get_renderer() { return _renderer; }
  
  static inline void provide_window(Window* window) {
    if (_window != nullptr) 
      return;
      
    _window = std::unique_ptr<Window>(window);
  }

  static inline void provide_renderer(Renderer* renderer) {
    if (_renderer != nullptr) 
      return;
      
    _renderer = std::unique_ptr<Renderer>(renderer);
  }

 private:
  static inline std::unique_ptr<Window> _window = nullptr;
  static inline std::unique_ptr<Renderer> _renderer = nullptr;
};

} // namespace opticus
