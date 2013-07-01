#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	bubble.init();

}

//--------------------------------------------------------------
void testApp::update(){
	bubble.update("Hello World", mouseX, mouseY);
}

//--------------------------------------------------------------
void testApp::draw(){
	bubble.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	cout << "key: " << key << endl;
	
	switch (key) {
		case '1':
			bubble.visible = !bubble.visible;
			break;
		default:
			break;
	}

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