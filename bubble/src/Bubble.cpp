#include "ofMain.h"
#include "Bubble.h"

Bubble::Bubble() {
	cout << "Bubble constructor" << endl;
}


void Bubble::init() {
	cout << "Bubble init" << endl;
	visible = false;
}


void Bubble::update(string t, int x, int y) {
	//cout << "Bubble update" << endl;
	text = t;
	pos.x = x;
	pos.y = y;
}


void Bubble::draw() {
	//cout << "Bubble draw" << endl;
	if (visible) {
		/* Background
		 */
		ofFill();
		ofSetColor(ofColor::red);
		ofRect(pos.x, pos.y, 100, 100);
		/* Text
		 */
		ofFill();
		ofSetColor(ofColor::black);
		ofDrawBitmapString(text, pos.x+10, pos.y+10);
	}
}