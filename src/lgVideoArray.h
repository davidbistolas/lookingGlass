//
//  lgVideoArray.hpp
//  lookingGlass2
//
//  Created by David Bistolas on 2016-05-05.
//
//

#ifndef lgVideoArray_hpp
#define lgVideoArray_hpp

#include <stdio.h>
#include "lgVideo.h"
#include "ofxAlphaMaskTexture.h"
#include "ofxFilterLibrary.h"

#endif /* lgVideoArray_hpp */


class lgVideoArray {
public:
    bool setup(int width, int height);

    vector<ofVideoDevice> listGrabbers();
    bool addCamera(int index);
    bool addMovie(string path);
    bool addImage(string path);

    bool setCameraOne(int index);
    bool setCameraTwo(int index);
    bool switchCameras();

    int cameraCount();

    bool setFadeAmount(float amount);
    float getFadeAmount();
    bool setFadeType(int index);

    bool setFilter(int index);

    void update();
    void draw(float x, float y, float w, float h);
    void draw(float x, float y);
    void draw();


protected:
    int camWidth;
    int camHeight;
    bool fading;
    bool autoTransition;
    vector<lgVideo>videoDevices;

private:
    int cameraOne;
    int cameraTwo;
    int fadeType;
    float fadeAmount;
    void setupfilters();
    vector<AbstractFilter *> filters;
    int videoFilter;
    void setupFbo();
    ofFbo framebuffer;
    ofFbo wipebuffer;

};

