#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofBackground(0,0,0);
    
    pSensor.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    pSensor.update();
    pData = pSensor.getSensor();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    bool bSetupArduino = pData.bSetupArduino;
    int pulseVal = pData.pulseVal;
    int bpm = pData.BPM;
    int ibi = pData.IBI;
    
    string msg = "";
    msg += "FPS: " + ofToString(ofGetFrameRate()) + "\n";
    msg += "bSetupArduino: " + ofToString(bSetupArduino) + "\n";
    msg += "pulseVal: " + ofToString(pulseVal) + "\n";
    msg += "BPM: " + ofToString(bpm) + "\n";
    msg += "IBI: " + ofToString(ibi) + "\n";
    ofSetColor( 255, 255 );
    ofDrawBitmapString(msg, 20, 20);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}