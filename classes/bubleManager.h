//
//  speach.h
//  font_tests
//
//  Created by Christopher Pietsch on 20.02.13.
//
//
#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "buble.h"
#include "ofxJSONElement.h"


class bubleManager {
    
public:
    ofTrueTypeFont myFont;
    ofFbo myFbo;
    
    ofxJSONElement json;
    vector<string> messages;
    vector<buble*> bubles;
    buble* testBuble=NULL;
    vector<ofTexture> bubleImages;
    
    int myFontHeight;
    int fontBoarder;
    bool horizontal;
    int index, lastLoaded;
    float lastUpdated, updateInterval;
    string max_id;
    
    ofParameter<float> lineForce;
    ofParameter<string> fontFace,messageUrl;
    ofParameter<ofColor> fontColor, backgroundColor;
    ofParameter<int> fontSize;
    ofParameter<bool> drawTest;
    ofxGuiGroup group;
    
    bool initialized=false;

    bubleManager();
    ~bubleManager();
    
    void addGUI(ofxPanel& gui);    
    void updateFont(int & val);
    void setup();
    void readMessageFile();
    void createBuble(int id,int x, int y, int headsize);
    void destroyLastBuble();
    void destroyBuble(int _id);
    void updateBuble(int _id,int x, int y, int headsize);
    void simulate(int x, int y);
    void update();
    void draw();
    string getTextForBuble();
    
};
