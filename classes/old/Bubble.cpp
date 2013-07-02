#include "ofMain.h"
#include "Bubble.h"

Bubble::Bubble() {
	cout << "Bubble constructor" << endl;
}


void Bubble::init() {
	cout << "Bubble init" << endl;
	visible = false;
	fade = 255;
	fading = false;
}


void Bubble::update(string t, int x, int y) {
	//cout << "Bubble update" << endl;
	text = t;
	pos.x = x;
	pos.y = y;
	
	//fadeIn();
	//fadeOut();
}


void Bubble::draw() {
	//cout << "Bubble draw" << endl;
	if (visible) {
		ofEnableAlphaBlending();
		/* Background
		 */
		ofFill();
		ofSetColor(ofColor::red, fade);
		ofRect(pos.x, pos.y, 100, 100);
		/* Text
		 */
		ofFill();
		ofSetColor(ofColor::black, fade);
		ofDrawBitmapString(text, pos.x+10, pos.y+10);
		ofDisableAlphaBlending();
	}
}


void Bubble::fadeIn() {
	if (visible && fading) {
		float t = ofClamp(ofGetElapsedTimef() / FADE_SPEED, 0, 255);
		// all functions take input 0. ~ 1., and outputs 0. ~ 1.
		fade = ofxEasingFunc::Cubic::easeInOut(t);
		cout << fade << endl;
		/* if the value is 255, stop fading
		 */
		if (fade >= 255) {
			fading = false;
			fade = 255;
			cout << "fading stop" << endl;
		}
	}
}


void Bubble::fadeOut() {
	
}