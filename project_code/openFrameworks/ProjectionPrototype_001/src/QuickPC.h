//
//  QuickPC.h
//  example_openni
//
//  Created by BRenfer on 6/10/13.
//
//

#pragma once
#include "ofMain.h"

class QuickPointCloud : protected ofThread, public ofVboMesh {
    
public:
    
    void start(){
        startThread();
    }
    
    void setup( int w, int h ){
        width = w;
        height = h;
        setupIndicesAuto();
        for ( int i=0; i<width * height; i++){
            addVertex(ofVec3f(0,0,0));
        }
        pixels = new unsigned short [ width * height ];
        bNew = false;
    }
    
    void update( unsigned short * pix ){
        memcpy(pix, pixels, sizeof(unsigned short));
        bNew = true;
    }
    
protected:
    
    void threadedFunction(){
        while (isThreadRunning()){
            static bool bLogged = false;
            if ( bNew ){
                lock();
                for ( int i=0; i<getNumVertices(); i ++){
                    int x = i % width;
                    int y = i / width;
                    setVertex(i, ofVec3f(x,y,pixels[i]));
                    if (!bLogged){
                        bLogged = true;
                    }
                }
                unlock();
                bNew = false;
            }
        }
    }
    
    bool bNew;
    int width, height;
    unsigned short * pixels;
};
