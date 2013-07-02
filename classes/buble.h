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
    int headsize, headInterp;
    ofTexture tex;
    bool initialized=false;
    
    ~buble();
    buble(int _id,int _x, int _y, int _headsize, ofTexture _tex);
    
    void update(int x,int y,int _headsize);
    void draw();

};

