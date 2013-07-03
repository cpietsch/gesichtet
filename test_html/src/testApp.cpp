#include "testApp.h"


void testApp::setup(){
    //ofSetFullscreen(true);
    ofSetWindowShape(2200, 700);
    
	webTexWidth = ofGetWindowWidth();
	webTexHeight = ofGetWindowHeight();
    webTex.allocate(webTexWidth, webTexHeight, GL_RGBA);
    
    // Disable scrollbars via the WebCoreConfig
    Awesomium::WebCoreConfig config;
    //config.setCustomCSS("::-webkit-scrollbar { display: none; }");
    
	// Create our WebCore singleton with the default options
	webCore = new Awesomium::WebCore(config);
	
	// Create a new WebView instance with a certain width and height, using the
	// WebCore we just created
	webView = webCore->createWebView(webTexWidth, webTexHeight);
	
	// Load a file into our WebView instance
	webCore->setBaseDirectory(ofToDataPath("", true));
	//webView->loadFile("index.html");
    webView->loadURL("http://www.openframeworks.cc/");
	
	webView->focus();
    webView->setTransparent(true);
    webView->createObject(L"MyObject");
    webView->setObjectCallback(L"MyObject", L"OnSelectItem");
}

void testApp::OnSelectItem(){
    
    
}

void testApp::exit(){
    // Destroy our WebView instance
	webView->destroy();
	delete webCore;
}


void testApp::update(){
    webCore->update();
    
    // Call our display func when the WebView needs rendering
	if (webView->isDirty()) {
        const Awesomium::RenderBuffer* renderBuffer = webView->render();
        if (renderBuffer) {
            webTex.loadData(renderBuffer->buffer, webTexWidth, webTexHeight, GL_BGRA);
        }
    }
}


void testApp::draw(){
    ofSetColor(255);
	//webTex.draw(mouseX, mouseY, 100, 100);
    webTex.draw(mouseX, mouseY);
	
    if (webView->isLoadingPage()) {
        ofSetColor(0);
        ofDrawBitmapString("Loading...", 10, ofGetHeight()-20);
    }
}


void testApp::keyPressed(int key){
    if (key == 'f') {
        // No fullscreen
        if (ofGetWindowMode() == 0) {
            ofSetFullscreen(true);
        } else {
            ofSetFullscreen(false);
        }
    }
}


void testApp::keyReleased(int key){

}


void testApp::injectKey(int keyCode) {
	Awesomium::WebKeyboardEvent keyEvent;
    
	char* buf = new char[20];
	keyEvent.virtualKeyCode = keyCode;
	Awesomium::getKeyIdentifierFromVirtualKeyCode(keyEvent.virtualKeyCode, &buf);
	strcpy(keyEvent.keyIdentifier, buf);
	delete[] buf;
	
	keyEvent.modifiers = 0;
	keyEvent.nativeKeyCode = 0;
	keyEvent.type = Awesomium::WebKeyboardEvent::TYPE_KEY_DOWN;
    
	webView->injectKeyboardEvent(keyEvent);
    
	keyEvent.type = Awesomium::WebKeyboardEvent::TYPE_KEY_UP;
    
	webView->injectKeyboardEvent(keyEvent);
}



void testApp::mouseMoved(int x, int y ){
    webView->injectMouseMove(x, y);
}


void testApp::mouseDragged(int x, int y, int button){
    webView->injectMouseMove(x, y);
}


void testApp::mousePressed(int x, int y, int button){
    webView->injectMouseDown(Awesomium::LEFT_MOUSE_BTN);
}


void testApp::mouseReleased(int x, int y, int button){
    webView->injectMouseUp(Awesomium::LEFT_MOUSE_BTN);
}


void testApp::windowResized(int w, int h){

}
