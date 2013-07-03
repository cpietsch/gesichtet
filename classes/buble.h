//
//  speach.h
//  font_tests
//
//  Created by Christopher Pietsch on 20.02.13.
//
//
#pragma once

#include "ofMain.h"


class buble {
    
public:
    
    int id;
 
    ofPoint anchor;
    ofPoint offset;
    int headsize, headsizeOrig,headInterp,blur;
    ofTexture tex;
    bool initialized=false;
    
    ~buble();
    buble(int _id,ofPoint _anchor,ofPoint _offset, int _headsize, ofTexture _tex);
    
    void update(ofPoint _anchor,int _headsize);
    void draw();

};

