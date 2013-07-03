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

    
buble::buble(int _id,ofPoint _anchor,ofPoint _offset, int _headsize, ofTexture _tex){
        
    ofLog(OF_LOG_NOTICE, "init buble %d", _id);
    cout << _anchor << endl;
    cout << _offset << endl;
    
    id=_id;
    headsize = _headsize;
    headsizeOrig = _headsize;
    headInterp = _headsize;
    anchor=_anchor;
    offset=_offset;
    tex=_tex;
    
    initialized = true;

};

void buble::update(ofPoint _anchor,int _headsize){
    headsize = _headsize;
    anchor = _anchor;
    //headInterp += (headInterp-headsize)*0.1;
};



void buble::draw(){

    
        ofTranslate(anchor.x-offset.x, anchor.y-offset.y-250);
        tex.draw(0, 0);

    
}

