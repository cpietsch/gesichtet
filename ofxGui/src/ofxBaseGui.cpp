#include "ofxBaseGui.h"
#include "ofxXmlSettings.h"
#include "ofImage.h"

const ofColor
ofxBaseGui::headerBackgroundColor(64),
ofxBaseGui::backgroundColor(0),
ofxBaseGui::borderColor(120,100),
ofxBaseGui::textColor(255),
ofxBaseGui::fillColor(128);

const int ofxBaseGui::textPadding = 4;
const int ofxBaseGui::defaultWidth = 400;
const int ofxBaseGui::defaultHeight = 20;

ofTrueTypeFont ofxBaseGui::font;
bool ofxBaseGui::fontLoaded = false;

ofxBaseGui::ofxBaseGui(){
	bGuiActive = false;
	currentFrame = 0;
	serializer = new ofxXmlSettings;

	thisHeaderBackgroundColor=headerBackgroundColor;
	thisBackgroundColor=backgroundColor;
	thisBorderColor=borderColor;
	thisTextColor=textColor;
	thisFillColor=fillColor;

	if(!fontLoaded)
		loadFont(OF_TTF_SANS,10,true,true);
}

void ofxBaseGui::loadFont(string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet, int dpi){
	font.loadFont(filename,fontsize,_bAntiAliased,_bFullCharacterSet,dpi);
	fontLoaded = true;
}

ofxBaseGui::~ofxBaseGui(){
	ofUnregisterMouseEvents(this);
}

void ofxBaseGui::saveToFile(string filename) {
	serializer->load(filename);
	saveTo(*serializer);
	serializer->save(filename);
}

void ofxBaseGui::loadFromFile(string filename) {
	serializer->load(filename);
	loadFrom(*serializer);
}


void ofxBaseGui::saveTo(ofBaseFileSerializer& serializer){
	serializer.serialize(getParameter());
}

void ofxBaseGui::loadFrom(ofBaseFileSerializer& serializer){
	serializer.deserialize(getParameter());
}


void ofxBaseGui::setDefaultSerializer(ofBaseFileSerializer& _serializer){
	serializer = &_serializer;
}

string ofxBaseGui::getName(){
	return getParameter().getName();
}

void ofxBaseGui::setName(string _name){
	getParameter().setName(_name);
}

void ofxBaseGui::setPosition(ofPoint p){
	setPosition(p.x,p.y);
}

void ofxBaseGui::setPosition(float x, float y){
	b.x = x;
	b.y = y;
	generateDraw();
}

void ofxBaseGui::setSize(float w, float h){
	b.width = w;
	b.height = h;
	generateDraw();
}

void ofxBaseGui::setShape(ofRectangle r){
	b = r;
	generateDraw();
}

void ofxBaseGui::setShape(float x, float y, float w, float h){
	b.set(x,y,w,h);
	generateDraw();
}

ofPoint ofxBaseGui::getPosition(){
	return ofPoint(b.x,b.y);
}

ofRectangle ofxBaseGui::getShape(){
	return b;
}

float ofxBaseGui::getWidth(){
	return b.width;
}

float ofxBaseGui::getHeight(){
	return b.height;
}

ofColor ofxBaseGui::getHeaderBackgroundColor(){
	return thisHeaderBackgroundColor;
}

ofColor ofxBaseGui::getBackgroundColor(){
	return thisBackgroundColor;
}

ofColor ofxBaseGui::getBorderColor(){
	return thisBorderColor;
}

ofColor ofxBaseGui::getTextColor(){
	return thisTextColor;
}

ofColor ofxBaseGui::getFillColor(){
	return thisFillColor;
}

void ofxBaseGui::setHeaderBackgroundColor(const ofColor & color){
	generateDraw();
	thisHeaderBackgroundColor = color;
}

void ofxBaseGui::setBackgroundColor(const ofColor & color){
	generateDraw();
	thisBackgroundColor = color;
}

void ofxBaseGui::setBorderColor(const ofColor & color){
	generateDraw();
	thisBorderColor = color;
}

void ofxBaseGui::setTextColor(const ofColor & color){
	generateDraw();
	thisTextColor = color;
}

void ofxBaseGui::setFillColor(const ofColor & color){
	generateDraw();
	thisFillColor = color;
}

string ofxBaseGui::saveStencilToHex(ofImage& img) {
	stringstream strm;
	int width = img.getWidth();
	int height = img.getHeight();
	int n = width * height;
	unsigned char cur = 0;
	int shift = 0;
	strm << "{";
	for(int i = 0; i < n;) {
		if(img.getPixels()[i * 4 + 3] > 0) {
			cur |= 1 << shift;
		}
		i++;
		if(i % 8 == 0) {
			strm << "0x" << hex << (unsigned int) cur;
			cur = 0;
			shift = 0;
			if(i < n) {
				strm << ",";
			}
		} else {
			shift++;
		}
	}
	strm << "}";
	return strm.str();
}

void ofxBaseGui::loadStencilFromHex(ofImage& img, unsigned char* data) {
	int width = img.getWidth();
	int height = img.getHeight();
	int i = 0;
	ofColor on(255, 255);
	ofColor off(255, 0);
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			int shift = i % 8;
			int offset = i / 8;
			bool cur = (data[offset] >> shift) & 1;
			img.setColor(x, y, cur ? on : off);
			i++;
		}
	}
	img.update();
}