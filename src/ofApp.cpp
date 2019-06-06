#include "ofApp.h"
#include "utils.hpp"

std::vector<ofMesh> percentMesh;

//--------------------------------------------------------------
void ofApp::setup(){
  ofTrueTypeFont font;
  font.load("Lato/Lato-Black.ttf", 72, true, true, true);
  percentMesh = extrudeCharacter(font, '%', 10);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofPushMatrix();
  ofTranslate(60, ofGetHeight()/2);
  ofRotateXDeg(ofGetFrameNum() * 3);
  ofTranslate(0, 30);
  for (auto& mesh : percentMesh) {
    mesh.draw();
  }
  ofPopMatrix();
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
