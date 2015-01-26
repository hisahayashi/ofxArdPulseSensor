//
//  ofxArdPulseSensor.h
//  ------------------------
//
//  Created by hisahayashi on 2015/01/27.
//  Copyright (c) 2015 hisahayashi.
//

#ifndef __emptyExample__ofxArdPulseSensor__
#define __emptyExample__ofxArdPulseSensor__

#include "ofMain.h"

#define SERIAL_LEN 20
#define DEBUG 1

struct PulseData{
    bool bSetupArduino;
    int pulseVal;
    int BPM;
    int IBI;
};

class ofxArdPulseSensor {
    
public:
    void setup();
    void update();
    PulseData getSensor();
    
private:
    void setupArduino();
    void updateSerial();
    
    // serial
    ofSerial serial;
    bool bSetupArduino;
    int nBytesRead = 0;
    char bytesReadString[SERIAL_LEN];
    int pulseVal = 0;
    
    // pulse sensor
    int BPM = 0;
    int IBI = 0;
    
};

#endif /* defined(__emptyExample__ofxArdPulseSensor__) */
