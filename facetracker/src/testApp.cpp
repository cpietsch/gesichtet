#include "testApp.h"

using namespace ofxCv;
using namespace cv;



static ofPoint fullHD = ofPoint(1920,1080);
static ofPoint halfHD = ofPoint(1280,720);
static ofPoint noHD = ofPoint(640, 480);

void testApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);

    drawGui = true;

    gui.setup();
        addGUI();
        detector.addGUI(gui);
        bubles.addGUI(gui);
    gui.loadFromFile(ofToDataPath("settings.xml"));
    
    detector.vertical = !horizontal;
    detector.setup();
    
    follower.setListener(this);
    bubles.setup();
    
    initVideo();
    
    
}

void testApp::initVideo(){
    
    if (useHD) {
        camDim = fullHD;
    } else {
        camDim = halfHD;
    }
    
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetVerticalSync(true);
    ofSetFrameRate(100);
    //ofSetWindowShape(camDim.x , camDim.y);
    ofBackground(0, 0, 0);

    if(testVideo){
        player.close();
        player.loadMovie("test.mp4");
        player.setVolume(0);
        player.play();
    } else {
        int camSelect=0;
        if (externalCam) {
            camSelect=1;
        }
        //cam.close();
        qtCam = ofPtr<ofQTKitGrabber>( new ofQTKitGrabber() );
        cam.setGrabber(qtCam);
        qtCam->setVideoDeviceID(camSelect);
        qtCam->setUseAudio(false);

        cam.initGrabber(camDim.x, camDim.y);
        //qtCam->setVideoCodec("QTCompressionOptionsHD720SizeH264Video");

    }
    
    camImg.allocate(camDim.x, camDim.y, OF_IMAGE_COLOR);
    
    
}

void testApp::addGUI(){
    appGroup.setup("General Settings");
    appGroup.add(fullscreenButton.setup("Fullscreen"));
    appGroup.add(initButton.setup("Reinitialize"));
    appGroup.add(drawDebug.set("Debug View",false));
    appGroup.add(horizontal.set("Horizontal Orientation", false));
    appGroup.add(externalCam.set("External Cam", false));
    appGroup.add(testVideo.set("Test Video", false));
    appGroup.add(useHD.set("Full HD", false));
    initButton.addListener(this,&testApp::initButtonPressed);
    fullscreenButton.addListener(this,&testApp::fullscreenButtonPressed);
    gui.add(&appGroup);
    
    trackGroup.setup("Tracking Settings");
    trackGroup.add(trackPersistence.set("trackPersistence",20,0,300));
    trackGroup.add(trackDistance.set("trackDistance",150,0,400));
    gui.add(&trackGroup);
    
}

void testApp::initButtonPressed(){
    initVideo();
}

void testApp::fullscreenButtonPressed(){
    ofToggleFullscreen();
}

void testApp::update() {
    newFrame = false;
    
    if(testVideo){
        player.update();
        newFrame = player.isFrameNew();
    } else {
        cam.update();
        newFrame = qtCam->hasPreview();
    }

	if(newFrame) {
        if(testVideo){
            camMat = toCv(player);
        } else {
            camMat = toCv(cam);
        }
        
        cv::flip(camMat, mirrorMat, 1);
        toOf(mirrorMat,camImg);
        camImg.update();
        
        detector.externalFactor = windowRatio;
        detector.vertical = !horizontal;
        detector.updateImage(toCv(camImg));
        detector.update();
    }
    
    follower.track(detector.objects);
    follower.setMaximumDistance(trackDistance);
    follower.setPersistence(trackPersistence);
    
    bubles.update();
}




void testApp::draw() {
    camImg.draw(0,0,camDim.x * windowRatio, camDim.y * windowRatio);
    
    
    bubles.draw();
    
    //ofPushStyle();
    if(drawDebug) {
        detector.drawDebugImage(ofGetWidth()-200,10);
        detector.draw();
        follower.draw();
    }
    
    if(drawGui) {
        gui.draw();
    }
    
    //ofPopStyle();
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 20);

}

void testApp::blobOn( faceFollower face ){
    bubles.createBuble(face.getLabel(),face.predicted.x,face.predicted.y,face.sizeSmooth.y);
}
void testApp::blobMoved( faceFollower face ){
    bubles.updateBuble(face.getLabel(),face.predicted.x,face.predicted.y,face.sizeSmooth.y);
}
void testApp::blobOff( faceFollower face ){
    bubles.destroyBuble(face.getLabel());
}

void testApp::windowResized(int w, int h){
    windowRatio = (float) ofGetWindowWidth()/camDim.x;
}

void testApp::keyPressed(int key){
    if( key == 'h' ){
		drawGui = !drawGui;
	}

}


