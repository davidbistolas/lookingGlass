//
//  lgVideo.cpp
//  lookingGlass2
//
//  Created by David Bistolas on 2016-05-02.
//
//

#include "lgVideo.h"


bool lgVideo::setup(int device, int width, int height){
    //set up the grabber
    camWidth = width;
    camHeight = height;

    __grabber.setDeviceID(device);
    __grabber.initGrabber(camWidth, camHeight);
    __videoType = CAMERA;
    return true;
}

bool lgVideo::setup(string path, int width, int height){
    camWidth = width;
    camHeight = height;

    ofFile file;
    string extension;

    if (file.open(path)) {
        extension = file.getExtension();
        if ((extension == "mp4") || ( extension == "mov")){
            //set the type to movie
            __player.setPixelFormat(OF_PIXELS_RGBA);
            __player.loadAsync(path);
            __player.setLoopState(OF_LOOP_NORMAL);
            __videoType = MOVIE;
            return true;

        } else if ((extension == "png")) {
        //set the type to image
            __image.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
            __image.setColor(ofColor::black);
            __image.load(file);
            __videoType = IMAGE;
            return true;
        } else {
            return false;
        }

    } else {
        return false;
    }

}


bool lgVideo::isMovie(){
    return __videoType == MOVIE;
}

bool lgVideo::isCamera(){
    return __videoType == CAMERA;
}

bool lgVideo::isImage(){
    return __videoType == IMAGE;
}

lgVideoType lgVideo::getVideoType(){
    return __videoType;
}

bool lgVideo::startMovie(){
    if (__videoType == MOVIE) {
        if (! __player.isPlaying()) {
            __player.play();
        }
    }

}

bool lgVideo::stopMovie(){
    if (__videoType == MOVIE) {
        if ( __player.isPlaying()) {
            __player.stop();
        }
    }
}


ofTexture lgVideo::getTexture(){
    ofTexture result;
    switch (__videoType) {
        case CAMERA:
            result = __grabber.getTexture();
            break;
        case MOVIE:
            result = __player.getTexture();
            break;
        case IMAGE:
            result = __image.getTexture();
            break;
        default:
            break;
    }
    return result;
}

void lgVideo::update(){
    switch (__videoType) {
        case CAMERA:
            __grabber.update();
            break;
        case MOVIE:
            __player.update();
            break;
        case IMAGE:
            __image.update();
            break;
        default:
            break;
    }
}

void lgVideo::draw(){
    lgVideo::draw(0,0,camWidth, camHeight);
}

void lgVideo::draw(float x, float y){
    lgVideo::draw(x, y, camWidth, camHeight);
}

void lgVideo::draw(float x, float y, float w, float h){
    switch (__videoType) {
        case CAMERA:
            __grabber.draw(x, y, w, h);
            break;
        case MOVIE:
            __player.draw(x, y, w, h);
            break;
        case IMAGE:
            __image.draw(x, y, w, h);
            break;
        default:
            break;
    }
}
