#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofSerial        serialPort;
        ofVideoGrabber  camera;
		
        ofxCv::FlowPyrLK flow;
    
        bool solenoidState;
    
        static bool vec2fSort( ofVec2f first, ofVec2f second );
};
