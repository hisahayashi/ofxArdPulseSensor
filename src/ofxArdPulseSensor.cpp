//
//  ofxArdPulseSensor.cpp
//  ------------------------
//
//  Created by hisahayashi on 2015/01/27.
//  Copyright (c) 2015 hisahayashi.
//

#include "ofxArdPulseSensor.h"

//--------------------------------------------------------------
void ofxArdPulseSensor::setup(){
    
    // Get serial port
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    string deviceLine, serialID;
    
    // Get port name
    for( int i = 0; i < deviceList.size(); i++ ){
        deviceLine = deviceList[i].getDeviceName().c_str();
        
        if( deviceLine.substr(0,12) == "tty.usbmodem" ){
            serialID = "/dev/" + deviceLine;
            ofLog() << "Arduino serial = " << serialID << endl;
        }
    }
    
    // Connect to Arduino
    serial.setup(serialID, 115200);
    
    // Initialize the parameter
    bSetupArduino = false;
    pulseVal = 0;
    BPM = 0;
    IBI = 800;
}

//--------------------------------------------------------------
void ofxArdPulseSensor::setupArduino(){
     ofLog() << "ofSerial Setup";
    
    // Connected flag
    bSetupArduino = true;
}

//--------------------------------------------------------------
void ofxArdPulseSensor::update(){
    
    if( serial.isInitialized() && !bSetupArduino ){
        setupArduino();
    }
    
    // Connected process
    if( bSetupArduino ){
        updateSerial();
    }
}

//--------------------------------------------------------------
void ofxArdPulseSensor::updateSerial(){
    
    int len = SERIAL_LEN - 1;
    nBytesRead = 0;
    int nRead = 0;
    char bytesRead[len];
    unsigned char bytesReturned[len];
    
    memset(bytesReturned, 0, len);
    memset(bytesReadString, 0, SERIAL_LEN);
    
    // Read to data received by the serial communication
    while ((nRead = serial.readBytes(bytesReturned, len)) > 0) {
        nBytesRead = nRead;
    };
    
    if (nBytesRead > 0) {
        memcpy(bytesReadString, bytesReturned, len);
        string str = bytesReadString;
        
        // Perth the byte
        vector< string > splitString = ofSplitString( str, "\n" );
        for( int i = 0; i < splitString.size(); i++ ){
            
            if( splitString[i] != "" ){
                string spStr = splitString[i];
                char spIndex = ofToChar(spStr.substr(0,1));
                int spNum = ofToInt( spStr.substr(1) );
                
                switch( spIndex ){
                    case 'S':
                        // ofLog() << "------ Pulse sensor value";
                        pulseVal = spNum;
                        break;
                    case 'B':
                        // ofLog() << "------ BPM";
                        if( spNum > 0 ){
                            BPM = spNum;
                            if( BPM > 150 ) BPM = 150;
                            if( BPM < 50 ) BPM = 50;
                        }
                        break;
                    case 'Q':
                        // ofLog() << "------ IBI";
                        if( spNum > 0 ) IBI = spNum;
                        break;
                    default:
                        break;
                }
                
                // ofLog() << "i: " << i << ", spNum: " << ofToString( spNum ) << ", spIndex: " << ofToString(spIndex);
            }
        }
    }
}

//--------------------------------------------------------------
PulseData ofxArdPulseSensor::getSensor(){
    PulseData data = {
        bSetupArduino,
        pulseVal,
        BPM,
        IBI
    };
    return data;
}
