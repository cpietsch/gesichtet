//
//  faceFollower.cpp
//  ofApp
//
//  Created by Christopher Pietsch on 17.04.13.
//
//

#include "faceFollower.h"

using namespace ofxCv;
using namespace cv;


const float dyingTime = 0.1;
const float bornTime = 0.1;


void faceFollower::setup(const cv::Rect& track) {
	rect = toOf(track);
	cur = rect.getCenter();
    predicted = estimated = cur;
    
    size.x = rect.getWidth();
    size.y = rect.getHeight();
    
    sizeSmooth = size;
	
	KF.init(4, 2, 0);
	
	KF.transitionMatrix = *(Mat_<float>(4, 4) <<
							1,0,1,0,
							0,1,0,1,
							0,0,1,0,
							0,0,0,1);
	
	measurement = Mat_<float>::zeros(2,1);
	
	KF.statePre.at<float>(0) = cur.x;
	KF.statePre.at<float>(1) = cur.y;
	KF.statePre.at<float>(2) = 0;
	KF.statePre.at<float>(3) = 0;
	
	setIdentity(KF.measurementMatrix);
	setIdentity(KF.processNoiseCov, Scalar::all(1e-4));
	setIdentity(KF.measurementNoiseCov, Scalar::all(1e-1));
	setIdentity(KF.errorCovPost, Scalar::all(0.7));
	

}

void faceFollower::update(const cv::Rect& track) {
    rect = toOf(track);
	cur = rect.getCenter();
    
    size.x = rect.getWidth();
    size.y = rect.getHeight();
    sizeSmooth.interpolate(size, 0.1);
	
	Mat prediction = KF.predict();
	cv::Point predictPt(prediction.at<float>(0),prediction.at<float>(1));
	predicted = toOf(predictPt);

	measurement(0) = cur.x;
	measurement(1) = cur.y;
    
	Mat estimation = KF.correct(measurement);
	cv::Point statePt(estimation.at<float>(0),estimation.at<float>(1));
	estimated = toOf(statePt);
	
    float curTime = ofGetElapsedTimef();
    if(!born){
        if(startedBorn == 0) {
            startedBorn = curTime;
        } else if(curTime - startedBorn > bornTime) {
            born = true;
        }
    }
}

void faceFollower::kill() {
    dead = true;
    /*
	float curTime = ofGetElapsedTimef();
    if(startedBorn!=0){
        dead=true;
    }
	if(startedDying == 0) {
		startedDying = curTime;
	} else if(curTime - startedDying > dyingTime) {
		dead = true;
	}
     */
}

void faceFollower::draw() {
    if(born){
        ofPushStyle();
        //float size = 30;
        ofSetColor(0,100);
        if(startedDying) {
            ofSetColor(ofColor::red);
        }
        ofCircle(predicted, size.x/4);

        ofSetColor(255);
        ofDrawBitmapString(ofToString(label), predicted);
        ofPopStyle();
    }
	
}
