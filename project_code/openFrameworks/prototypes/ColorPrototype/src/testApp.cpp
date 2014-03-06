#include "testApp.h"
#include "DepthRemapToRange.h"

float width = 640.0;
float height = 480.0;
float rowCount = width  * .75;
float columnCount = height * .75;
float extrudeAmount = 480;
bool  bUseMeshColors = false;
bool  bUseCubeColor  = false;

// color layer stuff
float zRange = 100;
float zInc   = 50.;

// near / far cutoff
float near = 500;
float far  = 1000;

ofPixels pixFront;
ofPixels pixBack;

//--------------------------------------------------------------
void testApp::setup(){
    
#ifdef USE_OPENNI
    device = new ofxNI2::Device();
    bool bSetup = device->setup();
    cout << device->isRegistrationSupported() << endl;
#else
    bool bSetup = kinect.init(false, true, true);
    kinect.setRegistration(true);
#endif
    if ( bSetup ){
#ifdef USE_OPENNI
        bool bDepthSetup = depth.setup(*device);
#else
        bool bDepthSetup = true;
        kinect.open();
#endif
        if ( bDepthSetup ){
            
#ifdef USE_OPENNI
            depth.setSize(width, height);
            depth.start();
            
            color.setup(*device);
            color.setSize(width, height);
            color.start();
            
            device->setEnableRegistration();
#endif
            
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
    
    // setup color layers
    float hue = ofRandom(360.0f);
    
    for (int i=0; i<zRange; i+= zInc) {
        colors.push_back(ColorLayer());
        colors.back().color.setSaturation(360.0);
        colors.back().color.setBrightness(360.0);
        colors.back().color.setHue(hue);
        
        hue += ofRandom(20,40);
        
        colors.back().z = i;
    }
    
    // setup color cube
    ofColor c;
    c.setSaturation(360.0);
    c.setBrightness(360.0);
    c.setHue(ofRandom(360.0f));
    cubeColors.push_back(c);
    
    c.setHue(ofRandom(360.0f));
    cubeColors.push_back(c);
    
    c.setHue(ofRandom(360.0f));
    cubeColors.push_back(c);
    
    c.setHue(ofRandom(360.0f));
    cubeColors.push_back(c);
    
    c.setHue(ofRandom(360.0f));
    cubeColors.push_back(c);
    
    c.setHue(ofRandom(360.0f));
    cubeColors.push_back(c);
    
    c.setHue(ofRandom(360.0f));
    cubeColors.push_back(c);
    
    c.setHue(ofRandom(360.0f));
    cubeColors.push_back(c);
    
    ofMesh colorFront;
    colorFront.addVertex(ofVec2f(0,0));
    colorFront.addVertex(ofVec2f(0,width));
    colorFront.addVertex(ofVec2f(height,width));
    colorFront.addVertex(ofVec2f(height,0));
    colorFront.addIndex(0); colorFront.addIndex(1); colorFront.addIndex(3);
    colorFront.addIndex(1); colorFront.addIndex(2); colorFront.addIndex(3);
    
    colorFront.addColor(cubeColors[0]);
    colorFront.addColor(cubeColors[1]);
    colorFront.addColor(cubeColors[2]);
    colorFront.addColor(cubeColors[3]);
    
    colorImageFront.allocate(width, height);
    colorImageFront.begin();
    ofClear(0,0,0,0);
    colorFront.draw();
    colorImageFront.end();
    
    colorFront.setColor(0,cubeColors[4]);
    colorFront.setColor(1,cubeColors[5]);
    colorFront.setColor(2,cubeColors[6]);
    colorFront.setColor(3,cubeColors[7]);
    
    colorImageBack.allocate(width, height);
    colorImageBack.begin();
    ofClear(0,0,0,0);
    colorFront.draw();
    colorImageBack.end();
    
    colorImageFront.readToPixels(pixFront);
    colorImageBack.readToPixels(pixBack);
    
    // setup gui
    gui = new ofxUICanvas(0, 0, ofGetWidth(), ofGetHeight());
    gui->addSlider("extrudeAmount", 0.0, 1000.0, &extrudeAmount);
    gui->addToggle("use mesh colors?", &bUseMeshColors);
    gui->addToggle("use cube color?", &bUseCubeColor);
    gui->addSlider("OpenNI Near Threshold", 0.0, 10000.0, &near);
    gui->addSlider("OpenNI Far Threshold", 0.0, 10000.0, &far);
    gui->setVisible(false);
    
    camera.setPosition(ofGetWidth()/2.0, ofGetHeight()/2.0, 0.);
    ofBackground(0);
}

//--------------------------------------------------------------
void testApp::update(){
#ifdef USE_OPENNI
    depth.updateTextureIfNeeded();
    color.updateTextureIfNeeded();
    ofxNI2::depthRemapToRange(depth.getPixelsRef(), remappedPix, near, far, true);
#else
    kinect.update();
    if ( !kinect.isFrameNew() ) return;
    kinect.setDepthClipping(near, far);
    remappedPix = kinect.getDepthPixelsRef();
#endif
    remappedImage.setFromPixels(remappedPix);
    
    
#ifdef USE_OPENNI
    // why are these pixels so volatile?
    if ( color.getWidth() == 0 && color.getPixelsRef().getWidth() == color.getWidth() ) return;
#endif
    
    if ( bUseMeshColors ){
        
        ofPixels pix;
        
#ifdef USE_OPENNI
        int width = color.getWidth();
        int height = color.getHeight();
        pix = color.getPixelsRef();
#else
        int width = kinect.getWidth();
        int height = kinect.getHeight();
        pix = kinect.getPixelsRef();
#endif
        
        for(int i=0; i<vbo.getNumVertices(); i++) {
            ofVec3f mV = vbo.getVertex(i);
            if ( mV.x < width && mV.y < height ){
                vbo.setColor(i, pix.getColor((int) mV.x, (int) mV.y) );
            }
        }
    } else {
        if ( !bUseCubeColor ){
            for(int i=0; i<vbo.getNumVertices(); i++) {
                ofVec3f mV = vbo.getVertex(i);
                if ( mV.x < remappedPix.getWidth() && mV.y < remappedPix.getHeight() ){
                    float z = remappedPix.getColor((int) mV.x, (int) mV.y ).r;
                    float index = ofMap(z, 0, 255, 0, colors.size()-1, true);
                    int nextHue = index + 1 >= colors.size() ? 0 : index+1;
                    
                    int select = floor(index);
                    float weight = index - select;
                    
                    // stick ourselves right in this crust
                    //vbo.setColor(i, colors[index].color );
                    // interpolate between current and next
                    ofColor c = colors[index].color;
                    ofColor p = colors[nextHue].color;
                    c.setHue(c.getHue() * weight + (p.getHue() * (1-weight)));
                    vbo.setColor(i, c );
                }
            }
        } else {
            for(int i=0; i<vbo.getNumVertices(); i++) {
                ofVec3f mV = vbo.getVertex(i);
                if ( mV.x < remappedPix.getWidth() && mV.y < remappedPix.getHeight() ){
                    float z = remappedPix.getColor((int) mV.x, (int) mV.y ).r;
                    
                    // is there a smart way to do this?
                    float hueOne = pixFront.getColor(mV.x, mV.y).getHue();
                    float hueTwo = pixBack.getColor(mV.x, mV.y).getHue();
                    float hue    = ofMap(z, 0, 255, hueOne, hueTwo);
                    
                    ofColor c = ofColor();
                    c.setSaturation(360.0);
                    c.setBrightness(360.0);
                    c.setHue(hue);
                    
                    vbo.setColor(i, c );
                }
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    //remappedImage.draw(0,480);
    
#ifdef USE_OPENNI
    if ( color.getWidth() == 0 ) return;
#endif
    
    ofEnableDepthTest();
    
    camera.begin();
    ofTranslate(-ofGetWidth()/2.0, -ofGetHeight()/2.0);
    
    bumpShader.begin();
    bumpShader.setUniformTexture("depthTex", remappedImage.getTextureReference(), 0);
    bumpShader.setUniform2f ("depthDims", 640.0, 480.0f);
    bumpShader.setUniform2f ("screenDims", 640.0, 480.0f);
    bumpShader.setUniform1f ("extrusion", extrudeAmount);
    vbo.draw();
    bumpShader.end();
    camera.end();
    
    //colorImageFront.draw(0,0);
    //colorImageBack.draw(0,colorImageFront.getHeight());
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
