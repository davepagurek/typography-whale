#include "SAO.hpp"

void SAO::setup() {
  ofFbo::Settings settings;
  settings.width = ofGetWidth();
  settings.height = ofGetHeight();
  settings.useDepth = true;
  settings.textureTarget = GL_TEXTURE_RECTANGLE_ARB;
  settings.internalformat = GL_RGBA32F;
//  settings.useStencil = true;
  settings.depthStencilAsTexture = true;
//  settings.textureTarget = ofGetUsingArbTex() ? GL_TEXTURE_RECTANGLE_ARB : GL_TEXTURE_2D;
  
  deferredFbo.allocate(settings);
  deferredFbo.setUseTexture(true);
  
  deferred.load("shaders/deferred");
  occlusion.load("shaders/occlusion");
  
//  test.allocate(750, 600, OF_IMAGE_COLOR);
//  composite.load("shaders/composite");
}

void SAO::begin() {
  deferredFbo.begin();
  deferredFbo.activateAllDrawBuffers();
  ofClear(0);
//  deferredFbo.clearDepthBuffer(1);
  ofEnableDepthTest();
  deferred.begin();
}

void SAO::end() {
  // End deferred render
  deferred.end();
  deferredFbo.end();
  
  // Begin AO render
  
  ofDisableDepthTest();
  occlusion.begin();
  //  deferredFbo.getDepthTexture().bind();
//  test.getTexture().bind();
  occlusion.setUniformTexture("depth", deferredFbo.getDepthTexture(), 1);
  auto proj = ofGetCurrentMatrix(OF_MATRIX_PROJECTION);
  occlusion.setUniform4f("projInfo",
    -2.0f / (ofGetWidth() * proj[0][0]),
    -2.0f / (ofGetHeight() * proj[1][1]),
    (1.0f - proj[0][2]) / proj[0][0],
    (1.0f + proj[1][2]) / proj[1][1]);
  occlusion.setUniform2i("screenSize", ofGetWidth(), ofGetHeight());
//  ofPath rect;
//  rect.rectangle(0, 0, ofGetWidth(), ofGetHeight());
//  rect.draw();
  deferredFbo.draw(0, 0);
//  test.getTexture().unbind();
  occlusion.end();
  
  ofEnableDepthTest();
//  deferredFbo.getDepthTexture().unbind();
//  deferredFbo.getDepthTexture().draw(0, 0, ofGetWidth(), ofGetHeight());
}
