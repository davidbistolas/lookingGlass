//
//  lgVideoArray.cpp
//  lookingGlass2
//
//  Created by David Bistolas on 2016-05-05.
//
//

#include "lgVideoArray.h"

bool lgVideoArray::setup(int width, int height){
    camWidth = width;
    camHeight = height;
    ofSetFrameRate(120);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    cameraOne = 0;
    cameraTwo = 0;
    fadeType = 5;
    fadeAmount = 0;
    setupFbo();
    setupfilters();
    videoFilter = 0;
    autoTransition = false;
}


void lgVideoArray::setupFbo(){
    //framebuffer setup
    ofBackground(0);
    ofFbo::Settings fboSettings;
    fboSettings.width = camWidth;
    fboSettings.height = camHeight;
    fboSettings.internalformat = GL_RGBA;
    fboSettings.textureTarget = GL_TEXTURE_2D;
    framebuffer.allocate(fboSettings);

    ofFbo::Settings wipefboSettings;
    wipefboSettings.width = camWidth;
    wipefboSettings.height = camHeight;
    wipefboSettings.internalformat = GL_RGBA;
    wipefboSettings.textureTarget = GL_TEXTURE_2D;

    wipebuffer.allocate(wipefboSettings);
    
}

void lgVideoArray::setupfilters(){
    filters.push_back(new AbstractFilter());
    filters.push_back(new PosterizeFilter(16));
    filters.push_back(new PosterizeFilter(16));
    filters.push_back(new PosterizeFilter(8));
    filters.push_back(new PosterizeFilter(4));
    filters.push_back(new HalftoneFilter(camWidth, camHeight, 0.01));
    filters.push_back(new KuwaharaFilter(6));
    filters.push_back(new SobelEdgeDetectionFilter(camWidth, camHeight));
    filters.push_back(new SketchFilter(camWidth, camHeight));
    filters.push_back(new PerlinPixellationFilter(camWidth, camHeight));
    filters.push_back(new XYDerivativeFilter(camWidth, camHeight));
    filters.push_back(new ZoomBlurFilter());
    filters.push_back(new EmbossFilter(camWidth, camHeight, 2.f));
    filters.push_back(new CGAColorspaceFilter());
    filters.push_back(new VignetteFilter());

    vector<GradientMapColorPoint> colors;
    for (float percent=0.0; percent<=1.0; percent+= 0.1)
        colors.push_back( GradientMapColorPoint(ofRandomuf(),ofRandomuf(),ofRandomuf(),percent) );
    filters.push_back(new GradientMapFilter(colors));

}

vector<ofVideoDevice> lgVideoArray::listGrabbers(){
    vector<ofVideoDevice> devices;
    vector<ofVideoDevice> availableDevices;

    ofVideoGrabber deviceLister;

    devices = deviceLister.listDevices();

    for(int i = 0; i < devices.size(); i++){
        if (devices[i].bAvailable) {
            availableDevices.push_back(devices[i]);
        }
    }
    return availableDevices;
}

bool lgVideoArray::setCameraOne(int index){
    if (videoDevices[cameraOne].isMovie())
        videoDevices[cameraOne].stopMovie();
    cameraOne = index;
    if (videoDevices[cameraOne].isMovie())
        videoDevices[cameraOne].startMovie();

    return true;
}

bool lgVideoArray::setCameraTwo(int index){
    if (videoDevices[cameraTwo].isMovie())
        videoDevices[cameraTwo].stopMovie();
    cameraTwo = index;
    if (videoDevices[cameraTwo].isMovie())
        videoDevices[cameraTwo].startMovie();
    return true;
}

bool lgVideoArray::switchCameras() {
    int c1 = cameraOne;
    int c2 = cameraTwo;
    setCameraTwo(c1);
    setCameraOne(c2);
}

int lgVideoArray::cameraCount(){
    return videoDevices.size();
}

bool lgVideoArray::addCamera(int index){
    lgVideo device;
    device.setup(index, camWidth, camHeight);
    videoDevices.push_back(device);
    return true;
}

bool lgVideoArray::addMovie(string path){
    lgVideo device;
    device.setup(path, camWidth, camHeight);
    videoDevices.push_back(device);
    return true;
}

bool lgVideoArray::addImage(string path){
    lgVideo device;
    device.setup(path, camWidth, camHeight);
    videoDevices.push_back(device);
    return true;
}

void lgVideoArray::update(){
    ofxAlphaMaskTexture *mask;

    videoDevices[cameraOne].update();
    videoDevices[cameraTwo].update();


    ofTexture startTexture;
    ofTexture endTexture;

    framebuffer.begin();
    ofClear(0);
    //setup textures for crossfade
    startTexture = videoDevices[cameraOne].getTexture();
    endTexture = videoDevices[cameraTwo].getTexture();

    mask = new ofxAlphaMaskTexture(endTexture,
                                   startTexture,
                                   wipebuffer.getTexture(),
                                   camWidth,
                                   camHeight);
    wipebuffer.begin();
    ofRectangle rectangle;
    ofClear(0);
    switch (fadeType) {
        case 0:
            ofSetCircleResolution(50);
            ofDrawCircle(camWidth / 2, camHeight /2, fadeAmount);
            break;
        case 1:
            rectangle.x = 0;
            rectangle.y = 0;
            rectangle.width = fadeAmount;
            rectangle.height = camHeight;
            ofDrawRectangle(rectangle);
            break;
        case 2:
            rectangle.x = camWidth-fadeAmount;
            rectangle.y = 0;
            rectangle.width = fadeAmount;
            rectangle.height = camHeight;
            ofDrawRectangle(rectangle);
            break;
        case 3:
            rectangle.x = 0;
            rectangle.y = 0;
            rectangle.width = camWidth;
            rectangle.height = fadeAmount;
            ofDrawRectangle(rectangle);
            break;
        case 4:
            rectangle.x = 0;
            rectangle.y = camHeight - fadeAmount;
            rectangle.width = camWidth;
            rectangle.height = fadeAmount;
            ofDrawRectangle(rectangle);
            break;
        case 5:
            rectangle.x=0;
            rectangle.y=0;
            rectangle.width = camWidth;
            rectangle.height = camHeight;
            ofSetColor(255,255,255,int((float(fadeAmount)/float(camWidth))*254));
            ofDrawRectangle(rectangle);
            break;
        case 6:
            ofSetCircleResolution(3);
            ofDrawCircle(camWidth / 2, camHeight /2, fadeAmount);
            break;
        case 7:
            ofSetCircleResolution(4);
            ofDrawCircle(camWidth / 2, camHeight /2, fadeAmount);
            break;
        case 8:
            ofSetCircleResolution(5);
            ofDrawCircle(camWidth / 2, camHeight /2, fadeAmount);
            break;

        default:
            break;
    }
    wipebuffer.end();
    mask->draw(0,0,camWidth,camHeight);
    framebuffer.end();


}

void lgVideoArray::draw(float x, float y, float w, float h){
    ofClear(0);
    ofSetColor(255, 255, 255, 255);
    ofPushMatrix();
    filters[videoFilter]->begin();
    framebuffer.draw(x,y);
    filters[videoFilter]->end();
    ofPopMatrix();
}

void lgVideoArray::draw(){
    lgVideoArray::draw(0,0,camWidth,camHeight);
}

void lgVideoArray::draw(float x, float y){
    lgVideoArray::draw(x, y, camWidth, camHeight);
}

bool lgVideoArray::setFadeAmount(float amount){
    fadeAmount = amount * camWidth;
}

float lgVideoArray::getFadeAmount(){
    return fadeAmount / camWidth;
}


bool lgVideoArray::setFadeType(int index){
    fadeType = index;
}

bool lgVideoArray::setFilter(int index){
    videoFilter = index;
}
