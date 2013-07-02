#ifndef BUBBLE
#define BUBBLE

#include "ofxEasingFunc.h"

#define FADE_SPEED 1.2


class Bubble {
public:
	/* Constructor
	 */
	Bubble();
	/* Methods
	 */
	void init();
	void update(string t, int x, int y);
	void draw();
	void fadeIn();
	void fadeOut();
	
	/* Variables
	 */
	bool visible;
	
	float fade;
	bool fading;
	
	string text;
	ofVec2f pos;
};

#endif BUBBLE