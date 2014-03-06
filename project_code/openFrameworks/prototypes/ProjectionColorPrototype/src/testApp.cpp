#include "testApp.h"

float near = 500;
float far = 4000;

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetWindowPosition(0,0);
    ofSetFrameRate(60);
    ofBackground(50);
    
    kinect.setRegistration(false);
    kinect.setDepthClipping(near, far); //mm (50cm - 4mt)
    kinect.enableDepthNearValueWhite(true);
    // ir:false, rgb:false, texture:true
    kinect.init(false, false, true);
    kinect.open();
    
    // Load camara lucida
    string cfg = ofToDataPath("camara_lucida/config.xml");
    
    cml = new cml::CamaraLucida( cfg );
    
    ofAddListener( cml->render_texture,
                  this, &testApp::render_texture );
    
    ofAddListener( cml->render_3d,
                  this, &testApp::render_3d );
    
    ofAddListener( cml->render_2d,
                  this, &testApp::render_2d );
    
    // center of gobstopper
    center.set(kinect.getWidth()/2.0, kinect.getHeight()/2.0, .5 );
    
    // setup gui
    gui = new ofxUICanvas(0,0,400,600);
    gui->toggleVisible();
    gui->addSlider("Near", 0.0, 10000.0, &near);
    gui->addSlider("Far", 0.0, 10000.0, &far);
    gui->addSlider("Center.x", 0.0, ofGetHeight(), &center.x);
    gui->addSlider("Center.y", 0.0, ofGetWidth(), &center.y);
    gui->addSlider("Center.z", 0.0, 10000.0, &center.z);
    
    // setup gobstopper render
    gobStopper.load("shaders/gobstopper.vert", "shaders/gobstopper.frag");
    colorMap.allocate(cml->getConfig()->tex_width, cml->getConfig()->tex_height);
    
    colorsGLSL = new float[10 * 3];
    // colors
    for ( int i=0; i<10; i++){
        colors.push_back( ofColor() );
        colors.back().setSaturation(1.0);
        colors.back().setBrightness(1.0);
        colors.back().setHue(ofRandom(0,1.0));
        colorsGLSL[i * 3] = colors.back().r;
        colorsGLSL[i * 3 + 1] = colors.back().g;
        colorsGLSL[i * 3 + 2] = colors.back().b;
    }
    colorMesh.setMode(OF_PRIMITIVE_POINTS);
    
    colorMesh.setupIndicesAuto();
    for (int x=0; x<kinect.getWidth(); x++){
        for (int y=0; y<kinect.getHeight(); y++){
            colorMesh.addVertex(ofVec3f(x,y,0));
        }
    }
}

//--------------------------------------------------------------
void testApp::update()
{
    if ( ! kinect.isConnected() )
        return;
    kinect.setDepthClipping(near, far);
    
    // update settings on CML
    cml->getDepthCamera()->config().near = ofMap(near, 0, 10000, 0, 255);
    cml->getDepthCamera()->config().far = ofMap(far, 0, 10000, 0, 255);
    
    kinect.update();
    
    if ( kinect.isFrameNew() ){
        cml->update( kinect.getRawDepthPixels() );
        for (int x=0; x<colorMesh.getNumVertices(); x++){
            ofVec3f v = colorMesh.getVertex(x);
            float zmts = kinect.getDistanceAt(v.x, v.y);// * 0.001;
            //zmts = CLAMP((zmts==0.?5.:zmts),0.,5.);
            v.z = zmts;
            colorMesh.setVertex(x, v);
        }
    }
}

//--------------------------------------------------------------
void testApp::draw()
{
    
    // update hue map
    colorMap.begin();
    ofClear(0,0,0,0);
    gobStopper.begin();
    gobStopper.setUniformTexture("depth_tex", kinect.getDepthTextureReference(), 0);
    gobStopper.setUniform3fv("colors", colorsGLSL, 10);
    gobStopper.setUniform3f("center", (float) center.x, (float) center.y, center.z);
    ofScale((float) colorMap.getWidth() / kinect.getWidth(), (float) colorMap.getHeight() / kinect.getHeight());
    colorMesh.draw();
    gobStopper.end();
    colorMap.end();
    
    cml->render();;
    ofSetColor(255);
}

//--------------------------------------------------------------
void testApp::render_texture(ofEventArgs &args)
{
//    ofClear(127, 0, 0, 1);
//    
//    float w = cml->tex_width();
//    float h = cml->tex_height();
//    
//    ofPushView();
//    ofViewport(ofRectangle(0,0,w,h));
//    ofSetupScreenOrtho(w, h, -1, 1);
//    ofSetColor(255);
//
//    glClearColor(0.5, 0, 0, 1);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ofClear(255 * 0.5, 0, 0, 1);
    
    float w = cml->tex_width();
    float h = cml->tex_height();
    
    ofPushView();
    ofViewport(0,0,w,h,true);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //kinect.drawDepth(0, 0, w, h);
    colorMap.draw(0, 0, w, h);
    //cml->get_hue_tex_ref( kinect.getRawDepthPixels() ).draw( 0, 0, w, h );
    ofPopView();
}

//--------------------------------------------------------------
void testApp::render_3d(ofEventArgs &args)
{
    ofPushMatrix();
    ofScale( 1., -1., 1. );
    ofTranslate( -0.3 * ofGetWidth(), 0.3 * ofGetHeight(), 1. );
    ofSetColor(255);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(center);
    //hm
    ofScale( -11., -1., 1. );
    ofSpherePrimitive(.01,8).draw();
    ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::render_2d(ofEventArgs &args)
{
    ofSetColor(255, 255, 255);
    kinect.drawDepth(0, 0, 200, 150);
    ofDrawBitmapString("press h for help",10,10);
    colorMap.draw(200,0,200,150);
    
    ofPushMatrix();
    ofTranslate(center);
    ofEllipse(0, 0, 20, 20);
    ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::exit(){
    ofLog(OF_LOG_VERBOSE, "exit!");
    
    ofRemoveListener( cml->render_texture,
                     this, &testApp::render_texture );
    
    ofRemoveListener( cml->render_3d,
                     this, &testApp::render_3d );
    
    ofRemoveListener( cml->render_2d,
                     this, &testApp::render_2d );
    
    cml->dispose();
    
    kinect.close();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    // camera lucida keys
    switch (key)
    {
            
        case 'o':
            cml->gpu( !cml->gpu() );
            break;
            
        case 'w':
            cml->wireframe( ! cml->wireframe() );
            break;
            
        case 'e':
            kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
            break;
            
        case 'f':
            ofToggleFullscreen();
            break;
            
        case 'p':
            ofSetWindowPosition( ofGetWindowPositionX() == 0 ? 1440 : 0, 0 );
            break;
            
        case 'g':
            gui->toggleVisible();
            break;
            
        case 'r':
            gobStopper.unload();
            gobStopper.load("shaders/gobstopper.vert", "shaders/gobstopper.frag");
            break;
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
void testApp::dragEvent(ofDragInfo dragInfo){}
