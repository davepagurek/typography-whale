#include "utils.hpp"

std::vector<ofMesh> extrudeCharacter(ofTrueTypeFont& font, char character, float depth, ofColor color) {
  std::vector<ofMesh> mesh;
  
  ofRectangle box = font.getStringBoundingBox(std::string("") + character, 0, 0);
  
  // front
  mesh.push_back(font.getCharacterAsPoints(character, true, true).getTessellation());
  for (auto& v : mesh.back().getVertices()) {
    v.y *= -1;
    v.y -= box.getHeight()/2;
    v.x -= box.getWidth()/2;
    mesh.back().addColor(color);
  }
  
  // back
  mesh.push_back(mesh.front());
  for (auto& v : mesh.back().getVertices()) {
    v.z += depth;
    mesh.back().addColor(color);
  }
  
  // Sides
  std::vector<ofPolyline> outline = font.getCharacterAsPoints(character, true, false).getOutline();
  for (auto& line : outline) {
    mesh.emplace_back();
    auto vertices = line.getVertices();
    for (auto& v : vertices) {
      v.y *= -1;
      v.y -= box.getHeight()/2;
      v.x -= box.getWidth()/2;
    }
    
    for (int i = 0; i < vertices.size() - 1; ++i) {
      mesh.back().addVertex(vertices[i]);
      mesh.back().addVertex(vertices[i+1]);
      mesh.back().addVertex(vertices[i] + glm::vec3(0, 0, depth));
      
      mesh.back().addVertex(vertices[i] + glm::vec3(0, 0, depth));
      mesh.back().addVertex(vertices[i+1] + glm::vec3(0, 0, depth));
      mesh.back().addVertex(vertices[i+1]);
      
      for (int j = 0; j < 6; ++j) {
        mesh.back().addColor(color);
      }
    }
    
    mesh.back().addVertex(vertices.front());
    mesh.back().addVertex(vertices.back());
    mesh.back().addVertex(vertices.front() + glm::vec3(0, 0, depth));
    
    mesh.back().addVertex(vertices.front() + glm::vec3(0, 0, depth));
    mesh.back().addVertex(vertices.back() + glm::vec3(0, 0, depth));
    mesh.back().addVertex(vertices.back());
    
    for (int j = 0; j < 6; ++j) {
      mesh.back().addColor(color);
    }
  }
  
  return mesh;
}

float jitter(float mixAmount, float offset) {
  float amount = 0.0;
  float scale = 1.0;
  offset += ofGetFrameNum() * 0.00002;
  for (int power = 0; power < 3; power++) {
    amount += sin((offset * 1234.0 + mixAmount) * scale) / scale;
    scale *= 2.0;
  }
  amount *= 0.09;
  // ramp down to 0 at 0 and 1
//  amount *= -4.0 * mixAmount * (mixAmount - 1.0);
  return amount;
}

glm::vec3 warp(glm::vec3 v, float scale) {
  constexpr float s = 100.0;
  return v + scale * glm::vec3(jitter(v.x/s, 0.0), jitter(v.y/s, 0.2), jitter(v.z/s, 0.5));
}
