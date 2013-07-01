#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    tb.setup("hel.ttf", 20, ofRectangle(20,20,350,350), "top", "top", true);
    tb.setText("Hi, my name is fred.\nI liked cheese and things.\nDo you?");
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0, 0, 0);
    ofSetHexColor(0xff0000);
    tb.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    drawArea.x = x;
    drawArea.y = y;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    drawArea.width = x-drawArea.x;
    drawArea.height = y-drawArea.y;
    
    tb.setBounds(drawArea, "center", "center");
    tb.setText("Hi, my name is fred.\nI liked cheese and things.\nDo you?");
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}