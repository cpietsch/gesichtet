#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    gui.setup();
    
    bubles.setup();
    bubles.addGUI(gui);
    gui.loadFromFile(ofToDataPath("settings.xml"));
    headsize=50;
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
    if(key=='1'){
        headsize-=10;
    } else if(key=='2'){
        headsize+=10;
    } else if(key=='q'){
        bubles.destroyLastBuble();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    bubles.updateBuble(1,x,y,headsize);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    bubles.createBuble(1,x,y,headsize);
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