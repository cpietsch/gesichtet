//
//  speach.h
//  font_tests
//
//  Created by Christopher Pietsch on 20.02.13.
//
//
#include "buble.h"

buble::~buble(){
        
    // todo delete texture
    tex.clear();
    ofLog(OF_LOG_NOTICE, "delete buble %d",id);
};

    
buble::buble(int _id,int _x, int _y, int _headsize, ofTexture _tex){
        
    ofLog(OF_LOG_NOTICE, "init buble %d at %:%d", _id,_x,_y);
    
    id=_id;
    headsize = _headsize;
    headInterp = _headsize;
    anchor=ofPoint(_x,_y);
    tex=_tex;
    
    initialized = true;

};

void buble::update(int x,int y,int _headsize){
    headsize = _headsize;
    anchor.x=x;
    anchor.y=y;
};



void buble::draw(){
            
    ofPushStyle();
    ofPushMatrix();
        ofTranslate(anchor.x, anchor.y+headsize);
        ofSetColor(255, 255, 255);
        tex.draw(0, 0);
    ofPopMatrix();
    ofPopStyle();
    
}

