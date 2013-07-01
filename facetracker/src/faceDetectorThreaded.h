//
//  faceDetectorThreaded.h
//  ofApp
//
//  Created by Christopher Pietsch on 16.04.13.
//
//

#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

using namespace ofxCv;
using namespace cv;

class faceDetectorThreaded : public ofThread , public faceDetector {
public:
       
	~faceDetectorThreaded() {
		stopThread();
		ofSleepMillis(500);
	}
	void setup() {
        classifier.load(ofToDataPath(fileName));
        startThread(true, false);
	}
    void update(){
        //dataMutex.lock();
        //dst.copyTo(imageBack);
        //dataMutex.unlock();
    }
	
protected:
    
    
	void threadedFunction() {
        while(isThreadRunning()) {
			            
            //ofSleepMillis(1000);
            
            dataMutex.lock();
			if(doTracking){
                dst.copyTo(imageBack);
                track(imageBack);
            }  
			dataMutex.unlock();
		}
	}
	
    cv::Mat imageBack, imageFront;
	ofMutex dataMutex;
};
