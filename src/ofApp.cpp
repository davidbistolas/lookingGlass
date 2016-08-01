#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    videoArray.setup(1280,760);
    //TODO: Make the file path configurable
    //TODO: Make images/movies/grabber matrix configurable
    videoArray.addImage("/Users/davidbistolas/lookingGlass/images/default.png");
    //videoArray.addCamera(0);
    videoArray.addMovie("/Users/davidbistolas/lookingGlass/movies/1.mp4");
    videoArray.addMovie("/Users/davidbistolas/lookingGlass/movies/2.mp4");
    videoArray.addMovie("/Users/davidbistolas/lookingGlass/movies/3.mp4");
    videoArray.addMovie("/Users/davidbistolas/lookingGlass/movies/4.mp4");
    filterID=0;
    videoArray.setFadeType(5);
    videoArray.setFilter(0);
    videoArray.setCameraOne(0);
    current = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
    if (autoFade) {
        float amount = (videoArray.getFadeAmount() * 100) + 4;
        if (amount < 100) {
            videoArray.setFadeAmount(amount / 100);
        } else {
            autoFade = false;
            videoArray.setFadeAmount(0);
            videoArray.switchCameras();
        }
    }

    videoArray.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    videoArray.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (current > videoArray.cameraCount() - 1) {
        current = 0;
    }
    videoArray.setCameraTwo(current++);
    autoFade = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
