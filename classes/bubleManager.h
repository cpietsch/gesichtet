//
//  speach.h
//  font_tests
//
//  Created by Christopher Pietsch on 20.02.13.
//
//

#include "buble.h"

class bubleManager {
    
public:
    ofTrueTypeFont myFont;
    ofFbo myFbo;
    
    ofxJSONElement json;
    vector<string> messages;
    vector<buble*> bubles;
    buble* testBuble=NULL;
    
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

    bubleManager(){};
    ~bubleManager(){
        for (int i =0; i<bubles.size(); i++){
            buble* tmp = bubles[i];
            bubles.erase(bubles.begin()+i);
            delete tmp;
        }
    };
    
    void addGUI(ofxPanel& gui){
        group.setup("Buble Manager");
        group.add(drawTest.set("Draw Testbuble", false));
        group.add(messageUrl.set("Message URL", "messages.json"));
        group.add(fontFace.set("FontFace", "arial.ttf"));
        group.add(fontSize.set( "FontSize", 15, 10, 20 ));
        group.add(fontColor.set("FontColor", ofColor(255,255,255),ofColor(0,0),ofColor(255,255)));
        group.add(backgroundColor.set("BackgroundColor", ofColor(255,255,255),ofColor(0,0),ofColor(255,255)));
        group.add(lineForce.set( "Line Force", 0.1, 0.01, 0.5 ));
    
        drawTest.addListener(this,&bubleManager::drawTestChanged);
        fontSize.addListener(this,&bubleManager::updateFont);
        
        gui.add(&group);
    };
    
    void updateFont(int & val){
        myFont.unbind();
        myFont.loadFont(fontFace, fontSize, true, true, true);
    };
    
    void drawTestChanged(bool & generate){
        if(initialized){
            if(generate){
                testBuble = new buble(111,ofGetWidth()/2,ofGetHeight()/2,1,getTextForBuble(),&myFont,lineForce, &myFbo, backgroundColor,fontColor);
            } else {
                delete testBuble;
            }
        }
    };
    
    void setup(){
        
        fontBoarder=3;
        index= 0;
        lastLoaded = 0;
        updateInterval = 4;
        drawTest=false;
               
        myFont.loadFont(fontFace, fontSize, true, true, true);
        myFontHeight = (int) myFont.getLineHeight();
    
        myFbo.allocate(100, myFontHeight+2*fontBoarder, GL_RGBA);
        myFbo.begin();
            ofClear(255,255,255);
        myFbo.end();
        
        readMessageFile();
        initialized=true;
        
    };
    
    void readMessageFile(){
        bool success = json.open(messageUrl);
        int counter = 0;
        if(success)
        {
            //cout << "file has " << json["messages"].size() << " messages" << endl;
            for(int i=lastLoaded; i<json["messages"].size(); i++)
            {
                messages.push_back(json["messages"][i]["text"].asString());
                counter++;
                lastLoaded++;
            }
            if(counter>0){
                ofLog(OF_LOG_NOTICE, "loaded " + ofToString(counter) + " new messages");
            }
        }
    }
    
    string getTextForBuble(){
        int random = ofRandom(0, 1);
        int size = messages.size()-1;
        
        if(random < 0.9){
            index++;
        } else {
            index = size-index;
        }
        
        if(index>size) index=0;
        if(index<0) index=int(size/random);
        
        return messages[index];
    }
    
    void createBuble(int id,int x, int y, int headsize) {
        buble* tmp = new buble(id,x,y,headsize,getTextForBuble(),&myFont,lineForce, &myFbo, backgroundColor,fontColor);
        bubles.push_back(tmp);
    }
    
    void destroyLastBuble(){
        if(bubles.size()>0){
            int i = bubles.size()-1;
            buble* tmp = bubles[i];
            bubles.erase(bubles.begin()+i);
            delete tmp;
            return;
        }
    }
    
    void destroyBuble(int _id){

        for (int i =0; i<bubles.size(); i++) {
            buble* tmp = bubles[i];
            if(tmp->id == _id){
                bubles.erase(bubles.begin()+i);
                delete tmp;
                return;
            }
        }
    }
    
    void updateBuble(int _id,int x, int y, int headsize){
        for (int i =0; i<bubles.size(); i++) {
            if(bubles[i]->id == _id){
                bubles[i]->updateBuble(x, y,headsize);
            }
        }
    }
    
    void simulate(int x, int y){
        for (int i =0; i<bubles.size(); i++) {
            bubles[i]->updateBuble(x,y,50);
        }
    }
    
    void update(){
        
        // check for new messages
        if(ofGetElapsedTimef()-lastUpdated > updateInterval)
        {
            readMessageFile();
            lastUpdated = ofGetElapsedTimef();
        }
        
        for (int i =0; i<bubles.size(); i++) {
            bubles[i]->force = lineForce;
            bubles[i]->horizontal = horizontal;
            bubles[i]->update();
        }
    }
    
    void draw(){
        
        for (int i =0; i<bubles.size(); i++) {
            bubles[i]->draw();
        }
            
        if(drawTest && initialized){
            testBuble->horizontal = horizontal;
            testBuble->update();
            testBuble->draw();
        }
        
    }
    
    
};
