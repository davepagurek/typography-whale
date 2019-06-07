#include "ofApp.h"
#include "utils.hpp"
#include "SAO.hpp"

std::vector<ofMesh> percentMesh;
SAO sao;
ofPolyline spine;

//--------------------------------------------------------------
void ofApp::setup() {
  ofTrueTypeFont font;
  font.load("Lato/Lato-Black.ttf", 72, true, true, true);
  percentMesh = extrudeCharacter(font, '%', 10, 0xFFFFFF);
  sao.setup();
  
  spine.clear();
  spine.addVertex(glm::vec3(-200, 100, 0));
  spine.bezierTo(
    glm::vec3(0, 100, -20),
    glm::vec3(50, 30, -20),
    glm::vec3(200, 0, -100));
  spine = spine.getResampledBySpacing(20);
  
//  ofPath spinePath;
//  spinePath.moveTo(glm::vec3(-200, 100, 0));
//  spinePath.bezierTo(glm::vec3(0, 100, -20), glm::vec3(50, 30, -20), glm::vec3(200, 0, -100));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  sao.begin();
  
  constexpr float warpScale = 150.0f;
  
  ofTranslate(ofGetWidth()/2, ofGetHeight()/2, -15);
  ofRotateYDeg(-50 - 40 * sin(ofGetFrameNum() * 0.005));
  for (int i = 0; i < spine.size(); ++i) {
    ofPushMatrix();
    ofTranslate(warp(spine[i], warpScale));
    
    float t = float(i)/float(spine.size());
    glm::vec3 tangent;
    if (i == 0) {
      tangent = spine.getTangentAtIndex(1);
    } else if (i == spine.size() - 1) {
      tangent = spine.getTangentAtIndex(i - 1);
    } else {
      tangent = spine.getTangentAtIndex(i);
    }
    glm::quat r = glm::rotation(glm::vec3(0, 0, 1), tangent);
    ofMultMatrix(glm::toMat4(r));
    
    float s = 0.25 - 4.0 * t * (t - 1.0);
    ofScale(s, s, 1);
    
    for (auto& mesh : percentMesh) {
      mesh.draw();
    }
    ofPopMatrix();
  }
  
//  for (auto x : {0, 5, 10}) {
//    ofPushMatrix();
//    ofTranslate(60-x, ofGetHeight()/2, -x*40);
//    ofScale(1 + x/5);
//    ofRotateXDeg(ofGetFrameNum() * 3);
//    ofTranslate(0, 30);
//    for (auto& mesh : percentMesh) {
//      mesh.draw();
//    }
//    ofPopMatrix();
//  }
  sao.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
