//
//  speach.h
//  font_tests
//
//  Created by Christopher Pietsch on 20.02.13.
//
//

#include "bubleManager.h"

bubleManager::bubleManager(){};

bubleManager::~bubleManager(){
        for (int i =0; i<bubles.size(); i++){
            buble* tmp = bubles[i];
            bubles.erase(bubles.begin()+i);
            delete tmp;
        }
    };
    
void bubleManager::addGUI(ofxPanel& gui){
        group.setup("Buble Manager");
        group.add(drawTest.set("Draw Testbuble", false));
        group.add(messageUrl.set("Message URL", "messages.json"));
        group.add(fontFace.set("FontFace", "arial.ttf"));
        group.add(fontSize.set( "FontSize", 15, 10, 20 ));
        group.add(fontColor.set("FontColor", ofColor(255,255,255),ofColor(0,0),ofColor(255,255)));
        group.add(backgroundColor.set("BackgroundColor", ofColor(255,255,255),ofColor(0,0),ofColor(255,255)));
        group.add(lineForce.set( "Line Force", 0.1, 0.01, 0.5 ));
    
       
        fontSize.addListener(this,&bubleManager::updateFont);
        
        gui.add(&group);
    };
    
void bubleManager::updateFont(int & val){
        myFont.unbind();
        myFont.loadFont(fontFace, fontSize, true, true, true);
    };

    
void bubleManager::setup(){
        
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
    
void bubleManager::readMessageFile(){
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
    
string bubleManager::getTextForBuble(){
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
    
void bubleManager::createBuble(int id,int x, int y, int headsize) {
    ofTexture tex;
    tex.allocate(100,100,GL_RGB);

    buble* tmp = new buble(id,x,y,headsize,tex);
    bubles.push_back(tmp);
}

void bubleManager::destroyLastBuble(){
        if(bubles.size()>0){
            int i = bubles.size()-1;
            buble* tmp = bubles[i];
            bubles.erase(bubles.begin()+i);
            delete tmp;
            return;
        }
    }
    
void bubleManager::destroyBuble(int _id){

        for (int i =0; i<bubles.size(); i++) {
            buble* tmp = bubles[i];
            if(tmp->id == _id){
                bubles.erase(bubles.begin()+i);
                delete tmp;
                return;
            }
        }
    }
    
void bubleManager::updateBuble(int _id,int x, int y, int headsize){
        for (int i =0; i<bubles.size(); i++) {
            if(bubles[i]->id == _id){
                bubles[i]->update(x, y,headsize);
            }
        }
    }
    
void bubleManager::simulate(int x, int y){
        for (int i =0; i<bubles.size(); i++) {
            bubles[i]->update(x,y,50);
        }
    }
    
void bubleManager::update(){
    for (int i =0; i<bubles.size(); i++) {
        //bubles[i]->update();
    }
}

void bubleManager::draw(){
        
        for (int i =0; i<bubles.size(); i++) {
            bubles[i]->draw();
        }
            
        if(drawTest && initialized){
            testBuble->draw();
        }
        
    }
    
    

