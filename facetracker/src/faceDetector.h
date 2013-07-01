//
//  faceDetector.h
//  ofApp
//
//  Created by fairbaken on 22.04.13.
//
//

#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

class faceDetector {
public:
    
    cv::CascadeClassifier classifier;
    cv::Mat img, grayCv, turned,dst,copped;
    vector<cv::Rect> objects;
    ofImage debugImg;
    
    ofParameterGroup opencv;
    ofxGuiGroup group;
    bool doTracking;
	
    ofParameter<float>  cvScaleFactor,cropTop;
    ofParameter<string> fileName;
    ofParameter<int> cvMinSize, cvMaxSize, cvMode, cvNeighbours,imageScale;
    
    ofColor color;
    bool vertical;
    float scaleFactor,externalFactor;
    
	faceDetector():
    externalFactor(1)
    ,color(ofColor(0,0,0))
    //,fileName("haarcascade_frontalface_alt2.xml")
    ,vertical(true)
    ,cropTop(0)
    ,scaleFactor(0.25)
    ,doTracking(false)
    {}
	void setup();
    void addGUI(ofxPanel& gui);
	void updateImage(cv::Mat image);
    void update();
    void track(cv::Mat image);
    void drawDebugImage(int x, int y);
    void draw();
    vector<cv::Rect>& getObjects();
};

