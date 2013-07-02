//
//  ofxInput.h
//  bangUpdate
//
//  Created by Christopher Pietsch on 20.03.13.
//
//

#pragma once

#include "ofParameter.h"
#include "ofxBaseGui.h"

class ofxInput : public ofxBaseGui{
public:
	ofxInput(){};
	~ofxInput();
	ofxInput(ofParameter<string> _bVal, float width = defaultWidth, float height = defaultHeight);
	ofxInput * setup(ofParameter<string> _bVal, float width = defaultWidth, float height = defaultHeight);
	ofxInput * setup(string toggleName, string _bVal, float width = defaultWidth, float height = defaultHeight);
	
    
	virtual void mouseMoved(ofMouseEventArgs & args);
	virtual void mousePressed(ofMouseEventArgs & args);
	virtual void mouseDragged(ofMouseEventArgs & args);
	virtual void mouseReleased(ofMouseEventArgs & args);
	
	void draw();
    
	template<class ListenerClass>
	void addListener(ListenerClass * listener, void ( ListenerClass::*method )(string&)){
		value.addListener(listener,method);
	}
    
	template<class ListenerClass>
	void removeListener(ListenerClass * listener, void ( ListenerClass::*method )(string&)){
		value.removeListener(listener,method);
	}
    
    
	string operator=(string v);
	operator const string & ();
    
	virtual ofAbstractParameter & getParameter();
    
protected:
	ofRectangle checkboxRect;
	ofParameter<string> value;
	
	void setValue(float mx, float my, bool bCheck);
	void generateDraw();
	void valueChanged(string & value);
	ofPath bg,fg,cross;
	ofVboMesh textMesh;
};
