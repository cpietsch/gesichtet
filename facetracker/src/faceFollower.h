//
//  faceFollower.h
//  ofApp
//
//  Created by Christopher Pietsch on 17.04.13.
//
//

#pragma once

#include "ofMain.h"
#include "ofxCv.h"



class faceFollower : public ofxCv::RectFollower {
protected:
	
	ofRectangle rect;

    cv::KalmanFilter KF;
	cv::Mat_<float> measurement;
	float startedDying;
    float startedBorn;
    
public:
	faceFollower()
    :startedDying(0),
    startedBorn(0),
    born(false),
    added(false)
    {
	}
	void setup(const cv::Rect& track);
	void update(const cv::Rect& track);

	void kill();
	void draw();
    bool added,born;
    ofVec2f cur, predicted,estimated,size,sizeSmooth, smooth;
};
