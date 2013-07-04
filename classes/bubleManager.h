//
//  speach.h
//  font_tests
//
//  Created by Christopher Pietsch on 20.02.13.
//
//
#pragma once

#include "ofMain.h"
#include <Awesomium/WebCore.h>

#include "ofxGui.h"
#include "buble.h"
#include "ofxJSONElement.h"

using namespace Awesomium;

class bubleManager {
    
public:
    vector<buble*> bubles;
    ofxGuiGroup group;
    ofShader shader;
    string channel;

    
    bool initialized=false;
    
    WebView* webView;
	WebCore* webCore;
    int webTexWidth;
	int webTexHeight;
    const RenderBuffer* renderBuffer;

    bubleManager();
    ~bubleManager();
    
    void addGUI(ofxPanel& gui);    
    void setup();
    void createBuble(int id,int x, int y, int headsize);
    void destroyLastBuble();
    void destroyBuble(int _id);
    void updateBuble(int _id,int x, int y, int headsize);
    void simulate(int x, int y);
    void update();
    void draw();
    
    ofParameter<int> blurLevel;
    ofParameter<int> blurRange;


};
