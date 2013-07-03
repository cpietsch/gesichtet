

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
    /*
        group.add(drawTest.set("Draw Testbuble", false));
        group.add(messageUrl.set("Message URL", "messages.json"));
        group.add(fontFace.set("FontFace", "arial.ttf"));
        group.add(fontSize.set( "FontSize", 15, 10, 20 ));
        group.add(fontColor.set("FontColor", ofColor(255,255,255),ofColor(0,0),ofColor(255,255)));
        group.add(backgroundColor.set("BackgroundColor", ofColor(255,255,255),ofColor(0,0),ofColor(255,255)));
        group.add(lineForce.set( "Line Force", 0.1, 0.01, 0.5 ));
    */
        gui.add(&group);
    };
    


    
void bubleManager::setup(){
    
    webTexWidth = 600;
	webTexHeight = 400;
   /*
    webCore = WebCore::Initialize(WebConfig());
    webView = webCore->CreateWebView(webTexWidth, webTexHeight);
    */
    Awesomium::WebCoreConfig config;
    webCore = new Awesomium::WebCore(config);
	webView = webCore->createWebView(webTexWidth, webTexHeight);
    initialized=true;
    
    
}
    /*
     
     
     WebURL url(WSLit("http://localhost/~chrispie/transparent.html"));
     webView->LoadURL(url);
     while (webView->IsLoading())
     webCore->Update();
     sleep(300);
     webCore->Update();
     BitmapSurface* surface = (BitmapSurface*)webView->surface();
     ofTexture tex;
     tex.allocate(webTexWidth,webTexHeight,GL_RGBA);
     tex.loadData(surface->buffer(), webTexWidth, webTexHeight, GL_BGRA);


     */



    
void bubleManager::createBuble(int id,int x, int y, int headsize) {
    ofTexture tex;
    webView->loadURL("http://localhost/~chrispie/transparent.html");
    //webView->loadURL("http://twitter.com");
    webView->focus();
    webView->setTransparent(true);
    webView->createObject(L"Dimensions");
    webView->setObjectCallback(L"Dimensions", L"setDimensions");
    webCore->update();
    renderBuffer = webView->render();
    if (renderBuffer) {
        tex.loadData(renderBuffer->buffer, webTexWidth, webTexHeight, GL_BGRA);
    }
            
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
        
        
    }
    
    

