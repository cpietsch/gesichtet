//
//  ofxInput.cpp
//  bangUpdate
//
//  Created by Christopher Pietsch on 20.03.13.
//
//

#include "ofxInput.h"
#include "ofGraphics.h"
#include "ofSystemUtils.h"

ofxInput::ofxInput(ofParameter<string> _bVal, float width, float height){
	setup(_bVal,width,height);
}

ofxInput::~ofxInput(){
	value.removeListener(this,&ofxInput::valueChanged);
}

ofxInput * ofxInput::setup(ofParameter<string> _bVal, float width, float height){
	b.x = 0;
	b.y = 0;
	b.width = width;
	b.height = height;
	currentFrame = 0;
	bGuiActive = false;
	value.makeReferenceTo(_bVal);
	checkboxRect.set(1, 1, b.height - 2, b.height - 2);
    
	value.addListener(this,&ofxInput::valueChanged);
	ofRegisterMouseEvents(this);
	generateDraw();
    
	return this;
    
}

ofxInput * ofxInput::setup(string toggleName, string _bVal, float width, float height){
	value.set(toggleName,_bVal);
	return setup(value,width,height);
}


void ofxInput::mouseMoved(ofMouseEventArgs & args){
}

void ofxInput::mousePressed(ofMouseEventArgs & args){
	setValue(args.x, args.y, true);
}

void ofxInput::mouseDragged(ofMouseEventArgs & args){
}

void ofxInput::mouseReleased(ofMouseEventArgs & args){
	bGuiActive = false;
}

void ofxInput::generateDraw(){
	bg.clear();
	bg.setFillColor(thisBackgroundColor);
	bg.moveTo(b.x,b.y);
	bg.lineTo(b.x+b.width,b.y);
	bg.lineTo(b.x+b.width,b.y+b.height);
	bg.lineTo(b.x,b.y+b.height);
	bg.close();
    
	textMesh = font.getStringMesh(getName()+": "+value.get(), b.x+textPadding, b.y+b.height / 2 + 4);
}

void ofxInput::draw(){
	currentFrame = ofGetFrameNum();
    
	bg.draw();

	
	ofColor c = ofGetStyle().color;
	ofBlendMode blendMode = ofGetStyle().blendingMode;
	if(blendMode!=OF_BLENDMODE_ALPHA){
		ofEnableAlphaBlending();
	}
	ofSetColor(thisTextColor);
	font.getFontTexture().bind();
	textMesh.draw();
	font.getFontTexture().unbind();
	ofSetColor(c);
	if(blendMode!=OF_BLENDMODE_ALPHA){
		ofEnableBlendMode(blendMode);
	}
}

string ofxInput::operator=(string v){
	value = v;
	return v;
}

ofxInput::operator const string & (){
	return value;
}

void ofxInput::setValue(float mx, float my, bool bCheck){
    
	if( ofGetFrameNum() - currentFrame > 1 ){
		bGuiActive = false;
		return;
	}
	if( bCheck ){
	
        
		if( b.inside(mx, my) ){
			bGuiActive = true;
		}else{
			bGuiActive = false;
            
		}
	}
	if( bGuiActive ){
        cout << "change" << endl;
        
        string text = ofSystemTextBoxDialog("choose sketch name", value.get());
        value = text;
        
		font.getFontTexture().bind();
        textMesh.draw();
        font.getFontTexture().unbind();
	}
}

ofAbstractParameter & ofxInput::getParameter(){
	return value;
}

void ofxInput::valueChanged(string & value){
	generateDraw();
}
