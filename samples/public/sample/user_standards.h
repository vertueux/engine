#include <runtime/engine_runtime.h>
#include <application/user_application.h>

namespace sample {
  class UserStandards {
   public:
    UserStandards();

    opticus::Engine engine;
    opticus::UserApplication app;
  };
}