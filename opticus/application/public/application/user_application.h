#pragma once

namespace opticus {

enum ApplicationType {
  APPLICATION_TYPE_SOFTWARE       = 0,
  APPLICATION_TYPE_GAME           = 1,
  APPLICATION_TYPE_SIMULATION     = 2,
  APPLICATION_TYPE_MULTIMEDIA     = 3,
  APPLICATION_TYPE_NOT_MENTIONEDs = 4
};

struct UserApplication {
  const char* description = "";
  const char* name = "";
};

};  