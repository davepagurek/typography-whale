#include "utils.hpp"

std::vector<ofMesh> extrudeCharacter(ofTrueTypeFont& font, char character, float depth) {
  std::vector<ofMesh> mesh;
  
  // front
  mesh.push_back(font.getCharacterAsPoints(character, true, true).getTessellation());
  
  // back
  mesh.push_back(mesh.front());
  for (auto& v : mesh.back().getVertices()) {
    v.z += depth;
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
    }
  }
  
  return mesh;
}
