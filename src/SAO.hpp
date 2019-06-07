#pragma once

#include "ofMain.h"

class SAO {
  ofShader deferred, occlusion, composite;
  ofFbo deferredFbo;
  
public:
  void setup();
  void begin();
  void end();
};
