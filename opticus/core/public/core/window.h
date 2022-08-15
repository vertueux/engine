#pragma once

namespace opticus {

class Window {
 public:
  virtual void open_window() = 0;
  virtual void update_window() = 0;
};

} // namespace opticus
