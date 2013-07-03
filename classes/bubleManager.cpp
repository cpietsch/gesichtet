

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
    
        gui.add(&group);
    };
    


    
void bubleManager::setup(){
        
            
        myFbo.allocate(100, myFontHeight+2*fontBoarder, GL_RGBA);
        myFbo.begin();
            ofClear(255,255,255);
        myFbo.end();
        
        initialized=true;
        
    };
    

    
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
    
    

