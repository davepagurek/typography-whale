#include "ofApp.h"
#include "utils.hpp"
#include "SAO.hpp"

#include "ofxSimpleScreenRecorder.h"

std::vector<ofMesh> spineMesh, ribMesh, armMesh, skullMesh, faceMesh, jawMesh;
SAO sao;
ofPolyline spine;
ofxSimpleScreenRecorder recorder;

bool record = false;

//--------------------------------------------------------------
void ofApp::setup() {
  ofTrueTypeFont font;
  font.load("Lato/Lato-Black.ttf", 72, true, true, true);
  spineMesh = extrudeCharacter(font, 'x', 8, 0xFFFFFF);
  ribMesh = extrudeCharacter(font, '@', 8, 0xFFFFFF);
  armMesh = extrudeCharacter(font, '?', 8, 0xFFFFFF);
  skullMesh = extrudeCharacter(font, '{', 15, 0xFFFFFF);
  jawMesh = extrudeCharacter(font, '/', 10, 0xFFFFFF);
  faceMesh = extrudeCharacter(font, '&', 10, 0xFFFFFF);
  sao.setup();
  
  spine.clear();
  spine.addVertex(glm::vec3(-300, 100, 0));
  spine.bezierTo(
    glm::vec3(0, 100, -20),
    glm::vec3(50, 30, -20),
    glm::vec3(250, 0, -100));
  spine = spine.getResampledBySpacing(20);
  
  if (record) {
    recorder.setup(ofGetWidth(), ofGetHeight(), "");
    recorder.start();
  }
  
//  ofPath spinePath;
//  spinePath.moveTo(glm::vec3(-200, 100, 0));
//  spinePath.bezierTo(glm::vec3(0, 100, -20), glm::vec3(50, 30, -20), glm::vec3(200, 0, -100));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  if (record) recorder.begin();
  sao.begin();
  
  constexpr float warpScale = 150.0f;
  
  ofTranslate(ofGetWidth()*0.35, ofGetHeight()/2, -170);
  ofRotateYDeg(-30 - 40 * sin(ofGetFrameNum() * 0.005));
  
  int ribStart = int(spine.size() * 0.75);
  int armStart = int(spine.size() * 0.8);
  
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
    
    ofPushMatrix();
    ofScale(0.7, 0.7, 1);
    float s = 0.25 - 4.0 * t * (t - 1.0);
    ofScale(s, s, 1);
    ofTranslate(0, 60, 0);
    for (auto& mesh : spineMesh) {
      mesh.draw();
    }
    ofPopMatrix();
    
    if (i >= ribStart) {
      ofPushMatrix();
      ofScale(1.7, 1.7, 1);
      
      float s = 0.25 - 4.0 * (t*0.9) * (t*0.9 - 1.0);
      ofScale(s, s, 1);
      for (auto& mesh : ribMesh) {
        mesh.draw();
      }
      ofPopMatrix();
    }
    
    if (i == armStart) {
      for (auto side : {-1, 1}) {
        ofPushMatrix();
        
        ofScale(side, 1, 1);
        ofTranslate(100, -40, 0);
        ofRotateYDeg(90-45);
        ofRotateZDeg(-150);
        ofRotateXDeg(20);
        ofScale(2, 2, 1);
        
        for (auto& mesh : armMesh) {
          mesh.draw();
        }
        
        ofPopMatrix();
      }
    }
    
    if (i == spine.size()-1) {
      // Skull
      ofPushMatrix();
      ofTranslate(0, 30, 150);
      ofRotateYDeg(-90);
      ofRotateZDeg(-80);
      ofScale(1.85);
      
      for (auto& mesh : skullMesh) {
        mesh.draw();
      }
      ofPopMatrix();
      
      // Jaw
      ofPushMatrix();
      ofTranslate(0, -30, 120);
      ofRotateYDeg(-90);
      ofRotateZDeg(-80);
      ofScale(1.4);
      
      for (auto& mesh : jawMesh) {
        mesh.draw();
      }
      ofPopMatrix();
      
      // Face
      ofPushMatrix();
      ofTranslate(0, 0, 50);
      ofRotateXDeg(-90);
      ofRotateZDeg(-90);
      ofRotateYDeg(-90);
      ofScale(1.8);
      
      for (auto& mesh : faceMesh) {
        mesh.draw();
      }
      ofPopMatrix();
    }
    
    ofPopMatrix();
  }

  sao.end();
  if (record) recorder.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (record) {
    recorder.stop();
  }
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
