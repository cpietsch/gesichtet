//
//  ofxTextBox.cpp
//
//  Created by Jamie White on 30/10/2012.
//
//

#include "ofxTextBox.h"

void ofxTextBox::setup(string filename, int size, ofRectangle bounds, string hAlignment, string vAlignment, bool debug) {
    
    bDebug = debug;
    numLines = 0;
    hAlign = hAlignment;
    vAlign = vAlignment;
    rBounds = bounds;
    
    ofTrueTypeFont::loadFont(filename, size, true, true, true);

}

void ofxTextBox::setBounds(ofRectangle bounds, string hAlignment, string vAlignment) {
    hAlign = hAlignment;
    vAlign = vAlignment;
    rBounds = bounds;
}

void ofxTextBox::setText(string text) {
    lines = splitLines(text);
}

void ofxTextBox::draw() {
    
    int lineWidth;
    int xOffset = 0;
    int yOffset = rBounds.height-((lines.size()-1)*int(getLineHeight()));
    
    // set yOffset
    if(vAlign == "center") {
        yOffset = (yOffset
                   )/2;
    } else if(vAlign == "top") {
        yOffset = 0;
    }
    
    for(int i = 0; i < lines.size(); ++i) {
        
        lineWidth = ofTrueTypeFont::getStringBoundingBox(lines[i], 0, 0).width;
        xOffset = (rBounds.width - lineWidth); // reset.
        
        if(hAlign == "center") {
            xOffset = (rBounds.width - lineWidth) / 2;
        } else if (hAlign == "top") {
            xOffset = 0;
        }
        
        //ofTrueTypeFont::drawStringAsShapes(lines[i], rBounds.x+centerOffset, rBounds.y+((i+1)*int(getLineHeight())));
        ofTrueTypeFont::drawString(lines[i], rBounds.x+xOffset, rBounds.y+yOffset+((i+1)*int(getLineHeight())));
    }
    
    if(bDebug) {
        ofNoFill();
        ofSetColor(255,0,0,127);
        ofRect(rBounds);
        ofFill();
    }
    //OF_EXIT_APP(0);
}

/* protected */
vector<string> ofxTextBox::splitLines(string text) {
        
    // split line at carriage return.
    vector<string> linebreaks = ofSplitString(text, "\n");
    //ofLog(OF_LOG_NOTICE, "CARRIAGE RETURNS: %d", linebreaks.size());
            
    vector<string> words;
    vector<string> lines;
    
    numLines = 0;
    lines.push_back("");
    
    for(int k = 0; k < linebreaks.size(); ++k) {
        
        words = ofSplitString(linebreaks[k], " ");
        
        for(int i = 0; i < words.size(); ++i) {
            
            // check word size is smaller than bounds width.
            int wordWidth = ofTrueTypeFont::getStringBoundingBox(words[i], 0, 0).width;
            
            //ofLog(OF_LOG_NOTICE, "Word %d width: %d", i, wordWidth);
            if(wordWidth > rBounds.width) {
                //ofLog(OF_LOG_NOTICE, "Word too big! Split Me!");
                vector<string> wordLines = hyphenateWord(words[i], rBounds.width);
                
                for(int j = 0; j < wordLines.size(); ++j) {
                    lines.push_back(wordLines[j]);
                    numLines ++;
                }
                
            } else {
                
                int lineSize = (ofTrueTypeFont::getStringBoundingBox(lines[numLines]+words[i]+" ", 0, 0).width);
                
                if(lineSize > rBounds.width) {
                    // create
                    lines.push_back("");
                    numLines ++;
                }
                
                lines[numLines] += (words[i]+" ");
                
            }
        }
        
        lines.push_back("");
        numLines ++;
     }
    
    return lines;
}

vector<string> ofxTextBox::hyphenateWord(string text, int maxWidth) {
    vector<string> lines;
    int numChars = text.size();
    int length = 0;
    string nextLine;
    
    //ofLog(OF_LOG_NOTICE, "SPLITTING WORD: " + text);
    
    for (int i = 0; i < numChars; i++) {
        if(ofTrueTypeFont::getStringBoundingBox(nextLine+text[i]+"-", 0, 0).width <= maxWidth) {
            nextLine+=text[i];
            //ofLog(OF_LOG_NOTICE, "nextLine: " + nextLine);
        } else {
            
            if(i != (numChars-1)) {
                nextLine += "-";
                lines.push_back(nextLine);
                nextLine = text[i];
                //ofLog(OF_LOG_NOTICE, "addHyphen: " + nextLine);
            } else {
                nextLine = text[i];
                lines.push_back(nextLine);
                //ofLog(OF_LOG_NOTICE, "Last Char added: " + nextLine);
                nextLine = "";
            }
            
        }
        
    }
    
    if(nextLine.size() > 0) {
        lines.push_back(nextLine);
    }
    
    return lines;
}


