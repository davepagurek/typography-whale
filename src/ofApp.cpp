#include "ofApp.h"
#include "utils.hpp"
#include "SAO.hpp"

std::vector<ofMesh> percentMesh;
SAO sao;

//--------------------------------------------------------------
void ofApp::setup(){
  ofTrueTypeFont font;
  font.load("Lato/Lato-Black.ttf", 72, true, true, true);
  percentMesh = extrudeCharacter(font, '%', 10, 0xFFFFFF);
  sao.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  sao.begin();
  
  for (auto x : {0, 5, 10}) {
    ofPushMatrix();
    ofTranslate(60-x, ofGetHeight()/2, -x*40);
    ofScale(1 + x/5);
    ofRotateXDeg(ofGetFrameNum() * 3);
    ofTranslate(0, 30);
    for (auto& mesh : percentMesh) {
      mesh.draw();
    }
    ofPopMatrix();
  }
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
