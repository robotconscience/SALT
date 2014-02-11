#include "testApp.h"

//--------------------------------------------------------------
bool testApp::vec2fSort( ofVec2f first, ofVec2f second ){
    return ( first.x > second.x );
}

//--------------------------------------------------------------
void testApp::setup(){
    vector<ofSerialDeviceInfo> info = serialPort.getDeviceList();
    for ( int i=0; i<info.size(); i++){
        cout << info[i].getDeviceName() << endl;
        if ( info[i].getDeviceName().find("usbmodem") != string::npos ){
            serialPort.setup(i, 9600);
            break;
        }
    }
    
    solenoidState = false;
    
    camera.initGrabber(320, 240);
}

//--------------------------------------------------------------
void testApp::update(){
    camera.update();
    if (camera.isFrameNew()){
        flow.calcOpticalFlow(camera);
        
        vector<ofVec2f> currentFlow = flow.getMotion();
        sort( currentFlow.begin(), currentFlow.end(), vec2fSort);
        
        if ( currentFlow.size() == 0 ) return;
        
        ofVec2f max_flow = currentFlow[0];
        
        cout << max_flow << endl;
        
        if (abs(max_flow.x) > 5.0 && !solenoidState){
            solenoidState = true;
            serialPort.writeByte('1');
        } else if ( solenoidState ){
            solenoidState = false;
            serialPort.writeByte('0');
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
	camera.draw(400,100,640,480);
	flow.draw(400,100,640,480);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}