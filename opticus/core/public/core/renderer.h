#pragma once

namespace opticus {

class Renderer {
 public:
  virtual bool initialize_renderer() = 0;
  virtual bool render() = 0;
};

} // namespace opticus
