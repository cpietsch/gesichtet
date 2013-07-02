#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxJSONElement.h"
#include "faceFollower.h"
#include "faceDetector.h"
#include "faceDetectorThreaded.h"
#include "Tracker.h"
#include "bubleManager.h"

class testApp : public ofBaseApp, public TrackerListener<faceFollower> {
public:
	void setup();
	void update();
	void draw();
    void keyPressed(int key);
    void addGUI();
    void initButtonPressed();
	void initVideo();
    void fullscreenButtonPressed();
    void windowResized(int w, int h);
    
    void blobOn( faceFollower face );
    void blobMoved( faceFollower face );
    void blobOff( faceFollower face );
    
	ofVideoGrabber cam;
    ofPtr<ofQTKitGrabber> qtCam;
    ofVideoPlayer player;

	ofImage camImg, gray, graySmall, debugSmall;
	ofTexture tex;

    ofxPanel gui;
    ofParameterGroup app;
    ofxGuiGroup appGroup,trackGroup;
    
    float windowRatio;
    bool drawGui;
    
    ofParameter<int> frameRate,trackPersistence,trackDistance;
    ofParameter<bool> horizontal,testVideo,externalCam, useHD,drawDebug;
    ofxButton initButton,fullscreenButton;
    
    ofPoint camDim,scaleDim;
    
	faceDetectorThreaded detector;
    RectTrackerFollowerEvent<faceFollower> follower;

    bubleManager bubles;
    bool newFrame;
    
    cv::Mat camMat, mirrorMat;

};
