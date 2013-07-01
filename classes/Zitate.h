
#ifndef ZITATE
#define ZITATE

#include "ofMain.h"
#include "ofxJSONElement.h"


class Zitate {
public:
	Zitate();
	
	void load(string file);
	
	ofxJSONElement json;
};

#endif