//
//  lgVideo.hpp
//  lookingGlass2
//
//  Created by David Bistolas on 2016-05-02.
//
//

#ifndef lgVideo_h
#define lgVideo_h

#include <stdio.h>
#endif /* lgVideo_hpp */

#include "ofMain.h"

enum lgVideoType { CAMERA, MOVIE, IMAGE };
enum lgVideoFilter { POSTERIZE, VINGETTE, ZOOMBLUR, CGA, GRADIENT };



class lgVideo {

public:
    bool setup(string path, int width, int height);
    bool setup(int index, int width, int height);

    bool setup(ofVideoGrabber grabber);
    bool setup(ofVideoPlayer player);
    bool setup(ofImage image);

    bool setGrabberDevice(int device);
    bool startMovie();
    bool stopMovie();
    lgVideoType getVideoType();
    bool isMovie();
    bool isCamera();
    bool isImage();
    void update();
    void draw(float x, float y, float w, float h);
    void draw(float x, float y);
    void draw();

    ofTexture getTexture();

private:
    lgVideoType __videoType;
    ofVideoGrabber __grabber;
    ofVideoPlayer  __player;
    ofImage        __image;
    ofFbo   framebuffer;
    int camWidth;
    int camHeight;


};

