//
//  speach.h
//  font_tests
//
//  Created by Christopher Pietsch on 20.02.13.
//
//

class bubleManager;


struct word {
    string text;
    int width;
    int height;
    ofPoint pos;
    float alpha;
    ofImage image;
    float speed;
    bool arrived;
    float force;
    float distance;
    int bornTime;
};


class word2 {
public:
    int width;
    int height;
    ofPoint pos;
    float alpha;
    ofImage image;
};


class buble {
    
public:
    
    int id;
    vector<word> words;
    vector<word> queue;
    
    ofPoint anchor;
    int size;
    int headsize, headInterp;
    
    int fontHeight;
    int rectSpacing;
    int counter;
    float force;
    ofColor backgroundColor, fontColor;
    
    bool horizontal=false;
    bool initialized=false;
    
    ~buble(){
        
        for (int i = 0; i<words.size(); i++) {
            words.erase(words.begin()+i);
        };
        for (int i = 0; i<queue.size(); i++) {
            queue.erase(queue.begin()+i);
        };
        ofLog(OF_LOG_NOTICE, "delete buble %d",id);
    };
    
    
    buble(int _id,int _x, int _y, int _headsize, const string _text, ofTrueTypeFont* _myFont, float _force, ofFbo* fbo, ofColor _backgroundColor, ofColor _fontColor){
        
        ofLog(OF_LOG_NOTICE, "init buble %d at %:%d", _id,_x,_y);
        
        counter=0;
        size=0;
        id=_id;

        backgroundColor = _backgroundColor;
        fontColor = _fontColor;
        
        rectSpacing=5;
        headsize = _headsize;
        headInterp = _headsize;
        force = _force;
        anchor=ofPoint(_x,_y);
        
        fontHeight = (int) _myFont->getLineHeight();
        
        vector<string> split = ofSplitString(_text, " ");
        int wordsSize=split.size();
        
        
        if(wordsSize>0){
            //words.resize(size);
            for(int i = 0; i < wordsSize; ++i) {
                ofRectangle rect = _myFont->getStringBoundingBox(split[wordsSize-1-i], 0,0);
                
                word tmp;
                tmp.bornTime = 0;
                tmp.force = _force;
                tmp.text = split[(wordsSize-1)-i];
                tmp.pos = ofPoint(_x,_y);
                tmp.width = rect.width+rectSpacing*3;
                tmp.height = fontHeight+rectSpacing*2;
                tmp.alpha = 0;
                tmp.distance = 0;
                tmp.arrived = false;
                tmp.image.allocate(rect.width, rect.height, OF_IMAGE_COLOR);
                
                getWordImage(_myFont,fbo,tmp.text,tmp.width,tmp.height).readToPixels(tmp.image);
                
                queue.push_back(tmp);
            }
            initialized = true;
        }
        
    };
    
    void updateBuble(int x,int y,int _headsize){
        if(words.size()>0){
            headsize = _headsize;
            anchor.x=x;
            anchor.y=y;
        }
        
    };
    

    void checkQueue(){
        if(queue.size()>0){
            
            //ofLog(OF_LOG_NOTICE, "check for new animation");
            
           if(words.size()==0 || ofGetFrameNum()-words[words.size()-1].bornTime > 10){
                queue[0].bornTime=ofGetFrameNum();
                words.push_back(queue[0]);
                queue.erase(queue.begin());
            }
        
        }
    }
    
    
    void updatePos(){
        if(words.size()>0){
            
            ofPoint dir, from, to;
            float force2, distance;
            
            for (int i = 0; i<words.size(); i++) {
                
                if(words[i].alpha<255){
                    words[i].alpha +=2;
                }
                
                if(i==0){
                    from=anchor;
                    force2=0.7;
                } else {
                    from = words[i-1].pos;
                    force2 = force;
                }
                
                to = words[i].pos;
                
                if(horizontal){
                    if(i==0){
                        to.x += headsize*0.80;
                    } else {
                        to.x += fontHeight*1.5;
                    }
                } else {
                    if(i==0){
                        to.y += headsize*0.80;
                    } else {
                        to.y += fontHeight*1.5;
                    }
                }
                
                dir = (from - to) * force;
                distance = dir.length();
                words[i].distance = distance;
                words[i].pos += dir;
                
                
            }
        }
    }
    
    void update(){
        checkQueue();
        updatePos();
    }
    
    void draw(){
        
        for (int i=0; i<words.size(); i++) {
            word* a = &words[i];
            
            ofPushStyle();
            ofPushMatrix();
                ofTranslate(a->pos.x, a->pos.y-fontHeight);
                ofSetColor(255, 255, 255,a->alpha);
                if(horizontal){
                    ofRotate(-90);
                }
                a->image.draw(0, 0);
            ofPopMatrix();
            ofPopStyle();
        }
    }

    ofTexture &getWordImage(ofTrueTypeFont* _myFont,ofFbo* fbo,string text, int width, int height){
        fbo->begin();
        ofPushStyle();
        ofPushMatrix();
            ofClear(255,255,255);
            ofSetColor(backgroundColor);
            ofFill();
            ofRect(0,0,width,height);
            ofSetColor(fontColor);
            _myFont->drawString(text, rectSpacing, fontHeight-rectSpacing/2);
        ofPopMatrix();
        ofPopStyle();
        fbo->end();
        
        return fbo->getTextureReference();
    }
    
};

