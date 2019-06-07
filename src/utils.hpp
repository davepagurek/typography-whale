#pragma once

#include "ofMain.h"

std::vector<ofMesh> extrudeCharacter(ofTrueTypeFont& font, char character, float depth, ofColor color);

float jitter(float mixAmount, float offset);

glm::vec3 warp(glm::vec3 v, float scale);
