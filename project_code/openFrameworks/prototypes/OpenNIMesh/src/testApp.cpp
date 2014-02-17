#include "testApp.h"
#include "DepthRemapToRange.h"

float width = 640.0;
float height = 480.0;
float rowCount = width / 2.0;
float columnCount = height / 2.0;
float extrudeAmount = 480;

//--------------------------------------------------------------
void testApp::setup(){
    device = new ofxNI2::Device();
    bool bSetup = device->setup();
    if ( bSetup ){
        cout << device->isRegistrationSupported() << endl;
        bool bDepthSetup = depth.setup(*device);
        if ( bDepthSetup ){
            
            depth.setSize(width, height);
            depth.start();
            
            color.setup(*device);
            color.setSize(width, height);
            color.start();
            
            device->setEnableRegistration();
            
            vbo.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
            
            bumpShader.load("shaders/bumpMap.vert", "shaders/bumpMap.frag");
            
            int spacing = 10;
            float x,y,z;
            
            for(int row=0; row < rowCount; row++){
                for (int col=0; col < columnCount; col++) {
                    
                    // set current x y z
                    x = width * (col/(columnCount-1));
                    y = height * (row/(rowCount-1));
                    z = 0;
                    
                    // vbo
                    // add colour, vertex and texture coord
                    vbo.addColor(ofFloatColor(1,1,1,1));
                    //vbo.addNormal(ofVec3f(0, 0, 1));
                    vbo.addVertex(ofVec3f(x, y, z));
                    
                    vbo.addTexCoord(ofVec2f( col/(columnCount-1), row/(rowCount-1)) );
                }
            }
            
            int n = 0;
            int colSteps = columnCount * 2;
            int rowSteps = rowCount - 1;
            vector<ofIndexType> indices;
            
            for ( int r = 0; r < rowSteps; r++ ) {
                for ( int c = 0; c < colSteps; c++ ) {
                    int t = c + r * colSteps;
                    if ( c == colSteps - 1 ) {
                        indices.push_back( n );
                    } else {
                        indices.push_back( n );
                        ( t%2 == 0 ) ? n += columnCount : (r%2 == 0) ? n -= (columnCount-1) : n -= (columnCount+1);
                    }  
                }  
            }
            vbo.addIndices(indices);
        }
    }
    
    // setup gui
    gui = new ofxUICanvas(0, 0, ofGetWidth(), ofGetHeight());
    gui->addSlider("extrudeAmount", 0.0, 1000.0, &extrudeAmount);
    
    camera.setPosition(ofGetWidth()/2.0, ofGetHeight()/2.0, 0.);
    ofBackground(0);
}

//--------------------------------------------------------------
void testApp::update(){
    depth.updateTextureIfNeeded();
    color.updateTextureIfNeeded();
    ofxNI2::depthRemapToRange(depth.getPixelsRef(), remappedPix, 500, 1000, true);
    remappedImage.setFromPixels(remappedPix);
    
    // why are these pixels so volatile?
    if ( color.getWidth() == 0 && color.getPixelsRef().getWidth() == color.getWidth() ) return;
    
    ofPixels pix = color.getPixelsRef();
    
    for(int i=0; i<vbo.getNumVertices(); i++) {
        ofVec3f mV = vbo.getVertex(i);
        if ( mV.x < color.getWidth() && mV.y < color.getHeight() ){
            vbo.setColor(i, pix.getColor((int) mV.x, (int) mV.y) );
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    //remappedImage.draw(0,480);
    
    if ( color.getWidth() == 0 ) return;
    
    ofEnableDepthTest();
    
    camera.begin();
    
    bumpShader.begin();
    bumpShader.setUniformTexture("depthTex", remappedImage.getTextureReference(), 0);
    bumpShader.setUniform2f ("depthDims", 640.0, 480.0f);
    bumpShader.setUniform2f ("screenDims", 640.0, 480.0f);
    bumpShader.setUniform1f ("extrusion", extrudeAmount);
    vbo.draw();
    bumpShader.end();
    camera.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if ( key == 'g' ){
        gui->toggleVisible();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ }
