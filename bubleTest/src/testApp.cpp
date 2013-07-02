#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    gui.setup();
    
    bubles.setup();
    bubles.addGUI(gui);
    gui.loadFromFile(ofToDataPath("settings.xml"));
}

//--------------------------------------------------------------
void testApp::update(){
    bubles.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    gui.draw();
    bubles.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    bubles.destroyLastBuble();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    bubles.updateBuble(1,x,y,10);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    bubles.createBuble(1,x,y,10);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

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