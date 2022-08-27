#pragma once

namespace opticus {

class Engine {
 public:
  Engine();
  
  void run();

  bool is_running = true;
};

} // namespace opticus