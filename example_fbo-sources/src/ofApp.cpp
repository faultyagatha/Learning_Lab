/*
 original version has the addon ofxOMXPlayer that couldn't compile because of libavutil.
 the addon is deleted, try to add it again in case of problems.
 */

#include "ofApp.h"

//------- original version (ofxOMXPlayer is deleted - read above)

//void ofApp::setup(){
//    ofBackground(0);
//
//    // Enable or disable audio for video sources globally
//    // Set this to false to save resources on the Raspberry Pi
////    ofx::piMapper::VideoSource::enableAudio = true;
////    ofx::piMapper::VideoSource::useHDMIForAudio = false;
//
//    // Register our sources.
//    // This should be done before mapper.setup().
//    piMapper.registerFboSource(customSource);
//    piMapper.registerFboSource(slideShowSource);
//    piMapper.setup();
//
//    // This will set the app fullscreen if compiled on Raspberry Pi.
//    #ifdef TARGET_RASPBERRY_PI
//        ofSetFullscreen(true);
//    #endif
//
//    // Start slideshow.
//    slideShowSource.play();
//}
//
//void ofApp::update(){
//    piMapper.update();
//}
//
//void ofApp::draw(){
//    piMapper.draw();
//}
//
//void ofApp::keyPressed(int key){
//    piMapper.keyPressed(key);
//}
//
//void ofApp::keyReleased(int key){
//    piMapper.keyReleased(key);
//}
//
//void ofApp::mousePressed(int x, int y, int button){
//    piMapper.mousePressed(x, y, button);
//}
//
//void ofApp::mouseReleased(int x, int y, int button){
//    piMapper.mouseReleased(x, y, button);
//}
//
//void ofApp::mouseDragged(int x, int y, int button){
//    piMapper.mouseDragged(x, y, button);
//}
//

//------- modified version (@faulty_agatha)

void ofApp::setup(){
    ofBackground(0);
    
    // Register our sources.
    // This should be done before mapper.setup().
    piMapper.registerFboSource(customSource);
    piMapper.setup();
    
    customSource.setActive(true);
    
    // This will set the app fullscreen if compiled on Raspberry Pi.
#ifdef TARGET_RASPBERRY_PI
    ofSetFullscreen(true);
#endif

}

void ofApp::update(){
    piMapper.update();
}

void ofApp::draw(){
    piMapper.draw();
}

void ofApp::keyPressed(int key){
    piMapper.keyPressed(key);
}

void ofApp::keyReleased(int key){
    piMapper.keyReleased(key);
}

void ofApp::mousePressed(int x, int y, int button){
    piMapper.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
    piMapper.mouseReleased(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button){
    piMapper.mouseDragged(x, y, button);
}



