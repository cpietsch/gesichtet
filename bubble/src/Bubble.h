#ifndef BUBBLE
#define BUBBLE

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

//private:
	/* Variables
	 */
	bool visible;
	string text;
	ofVec2f pos;
};

#endif BUBBLE