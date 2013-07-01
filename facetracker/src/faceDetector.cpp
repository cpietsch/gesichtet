//
//  faceDetector.cpp
//  ofApp
//
//  Created by fairbaken on 22.04.13.
//
//

#include "faceDetector.h"

using namespace ofxCv;
using namespace cv;


void faceDetector::setup() {
    classifier.load(ofToDataPath(fileName));    
}
void faceDetector::addGUI(ofxPanel& gui){
    
    group.setup("Face Detector");
    group.add(fileName.set("Filename", "haarcascade_frontalface_alt2.xml"));
    group.add(cvScaleFactor.set("Cascade scaleFactor",1.06,1,2));
    group.add(cvMinSize.set("Min Face Size",2,0,100));
    group.add(cvMaxSize.set("Max Face Size",10,0,100));
    group.add(cvMode.set("Mode",0,0,8));
    group.add(cvNeighbours.set("Neighbours",4,0,10));
    group.add(cropTop.set("crop Top",0,0,0.8));
    group.add(imageScale.set("ImageScale",4,1,10));
    group.setHeaderBackgroundColor(color);
    gui.add(&group);
}
void faceDetector::updateImage(cv::Mat image) {
    scaleFactor = imageScale/20.0;
    resize(image, img, cv::Size(scaleFactor * image.cols, scaleFactor * image.rows));
    
    if(grayCv.cols!=img.cols && grayCv.rows != img.rows){
        grayCv.create(img.cols, img.rows, CV_8U);
    }
    convertColor(img, grayCv, CV_RGB2GRAY);
    equalizeHist(grayCv, grayCv);
    
    if(!vertical){
        cv::transpose(grayCv, turned);
        //cv::flip(dst, dst, 1);
    } else {
        turned = grayCv;
    }
    cv::Rect crop(0,turned.rows*cropTop,turned.cols,turned.rows-turned.rows*cropTop);
    dst = turned(crop);
    
    /*
     // rotation
    Point2f src_center(dst.cols/2.0F, dst.rows/2.0F);
    
    Mat rot_matrix = getRotationMatrix2D(src_center, 20, 1.0);
    
    Mat rotated_img(cv::Size(dst.size().width, dst.size().height), dst.type());
    
    warpAffine(dst, rotated_img, rot_matrix, rotated_img.size());
    
    dst = rotated_img;
     */
    
    doTracking=true;
}
void faceDetector::update(){
    track(dst);
}

void faceDetector::track(Mat image) {
        classifier.detectMultiScale(
                                    image,
                                    objects,
                                    cvScaleFactor,
                                    cvNeighbours,
                                    cvMode,
                                    cvSize(cvMinSize, cvMinSize),
                                    cvSize(cvMaxSize, cvMaxSize)
                                    );
        
        
        for(int i = 0; i < objects.size(); i++) {
            if(!vertical){
                int x = objects[i].x;
                objects[i].x = objects[i].y+ cropTop*turned.rows;
                objects[i].y = x;
            } else {
                objects[i].y += cropTop*turned.rows;
            }
            objects[i].x /= scaleFactor/externalFactor;
            objects[i].y /= scaleFactor/externalFactor ;
            objects[i].width /= scaleFactor/externalFactor;
            objects[i].height /= scaleFactor/externalFactor;
        }
}

void faceDetector::draw(){
    ofPushStyle();
    ofSetColor(color,100);
    for(int i = 0; i < objects.size(); i++) {
        ofRect(toOf(objects[i]));
    }
    ofPopStyle();
}

void faceDetector::drawDebugImage(int x, int y){
    if(debugImg.width !=dst.cols || debugImg.height !=dst.rows){
        debugImg.allocate(dst.cols, dst.rows, OF_IMAGE_GRAYSCALE);
    }
    toOf(dst,debugImg);
    debugImg.update();
    debugImg.draw(x,y);
}

vector<cv::Rect>& faceDetector::getObjects(){
    return objects;
}