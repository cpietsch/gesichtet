//
//  ofxTextBox.h
//
//  Created by Jamie White on 30/10/2012.
//
//

#ifndef __emptyExample__TextBox__
#define __emptyExample__TextBox__

#include "ofMain.h"
#include "ofTrueTypeFont.h"

class ofxTextBox : public ofTrueTypeFont {
    public:
    void setup(string filename, int fontsize, ofRectangle bounds, string hAlignment="left", string vAlignment="top", bool debug=false);
        void draw();
        void setText(string text);
        void setBounds(ofRectangle bounds, string hAlignment, string vAlignment);
    
    protected:
        vector<string> splitLines(string text);
        vector<string> hyphenateWord(string text, int maxWidth);
    
        bool bDebug;
        ofRectangle rBounds;
        int numLines;
        string hAlign;
        string vAlign;
        vector<string> lines;
};

#endif /* defined(__emptyExample__TextBox__) */