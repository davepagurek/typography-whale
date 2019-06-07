#include "utils.hpp"

std::vector<ofMesh> extrudeCharacter(ofTrueTypeFont& font, char character, float depth, ofColor color) {
  std::vector<ofMesh> mesh;
  
  // front
  mesh.push_back(font.getCharacterAsPoints(character, true, true).getTessellation());
  for (auto& _ : mesh.back().getVertices()) {
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
