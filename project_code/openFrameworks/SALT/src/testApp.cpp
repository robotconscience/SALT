#include "testApp.h"

float near = 500;
float far = 4000;

bool bUseCL = true;

// arduino setup
string arduinoName = "/dev/tty.usbmodem1451";
int engagePin1 = 11;
int engagePin2 = 5;
int hIn1       = 10;
int hIn2       = 9;
int hIn3       = 4;
int hIn4       = 3;


// debugging with gui!
int pumpOneVal = 0;
int pumpTwoVal = 0;

float rotateX  = 0;
float rotateY  = 0;
float rotateZ  = 0;
float translateX  = 0;
float translateY  = 0;
float translateZ  = 0;
float scale       = 1.0;
float origin      = .5;

float shaderMin   = 0.0;
float shaderMax   = 1000.0;

bool  bUseData    = false;

// spacebrew settings
string host = "spacebrew.robotconscience.com";
string name = "salt";

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetWindowPosition(0,0);
    ofSetFrameRate(60);
    ofBackground(50);
    
    // KINECT SETUP
    kinect.setRegistration(false);
    kinect.setDepthClipping(near, far); //mm (50cm - 4mt)
    kinect.enableDepthNearValueWhite(true);
    // ir:false, rgb:false, texture:true
    kinect.init(false, false, true);
    kinect.open();
    
    // CAMARA LUCIDA SETUP
    string cfg = ofToDataPath("camara_lucida/config.xml");
    
    cml = new cml::CamaraLucida( cfg );
    
    ofAddListener( cml->render_texture, this, &testApp::render_texture );
    ofAddListener( cml->render_3d, this, &testApp::render_3d );
    ofAddListener( cml->render_2d, this, &testApp::render_2d );
    
    // center of gobstopper
    center.set(kinect.getWidth()/2.0, kinect.getHeight()/2.0, .5 );
    
    // OFX UI SETUP!
    
    gui = new ofxUICanvas(0,0,400,1000);
    gui->toggleVisible();
    gui->addSlider("Near", 0.0, 10000.0, &near);
    gui->addSlider("Far", 0.0, 10000.0, &far);
    gui->addSlider("Center.x", 0.0, ofGetHeight(), &center.x);
    gui->addSlider("Center.y", 0.0, ofGetWidth(), &center.y);
    gui->addSlider("Center.z", 0.0, 10000.0, &center.z);
    gui->addToggle("Use Camara Lucida", &bUseCL);
    gui->addSpacer();
    gui->addIntSlider("Pump 1 Value", 0, 255, &pumpOneVal);
    gui->addIntSlider("Pump 2 Value", 0, 255, &pumpTwoVal);
    gui->addSpacer();
    gui->addSlider("rotate x", 0, 360.0, &rotateX);
    gui->addSlider("rotate y", 0, 360.0, &rotateY);
    gui->addSlider("rotate z", 0, 360.0, &rotateZ);
    gui->addSlider("trans x", -1.0, 1.0, &translateX);
    gui->addSlider("trans y", -1.0, 1.0, &translateY);
    gui->addSlider("trans z", -1.0, 1.0, &translateZ);
    gui->addSlider("scale", 0.0, 2.0, &scale);
    gui->addSlider("origin", -1.0, 1.0, &origin);
    gui->addSlider("shaderMin", -100.0, 1000.0, &shaderMin);
    gui->addSlider("shaderMax", -100.0, 1000.0, &shaderMax);
    gui->addToggle("useData", &bUseData);
    gui->loadSettings("settings/gui.xml");
    
    // COLOR SETUP: setup gobstopper render
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
    
    // ARDUINO SETUP
    // load settings from XML
    ofxXmlSettings arduinoSettings;
    bool bSettingsLoaded = arduinoSettings.load("settings/arduino.xml");
    
    if ( bSettingsLoaded ){
        arduinoName = arduinoSettings.getValue("name", arduinoName);
        engagePin1  = arduinoSettings.getValue("engagePin1", engagePin1);
        engagePin2  = arduinoSettings.getValue("engagePin2", engagePin2);
        hIn1        = arduinoSettings.getValue("hIn1", hIn1);
        hIn2        = arduinoSettings.getValue("hIn2", hIn2);
        hIn3        = arduinoSettings.getValue("hIn3", hIn3);
        hIn4        = arduinoSettings.getValue("hIn4", hIn4);
    } else {
        // need to save settingsarduinoSettings.getValue("name", arduinoName);
        arduinoSettings.setValue("engagePin1", engagePin1);
        arduinoSettings.setValue("engagePin2", engagePin2);
        arduinoSettings.setValue("hIn1", hIn1);
        arduinoSettings.setValue("hIn2", hIn2);
        arduinoSettings.setValue("hIn3", hIn3);
        arduinoSettings.setValue("hIn4", hIn4);
        arduinoSettings.save("settings/arduino.xml");
    }
    
    // connect to arduino and stuff
    arduino.connect( arduinoName, 57600);
	ofAddListener(arduino.EInitialized, this, &testApp::setupArduino);
	bSetupArduino	= false;
    
    
    // SALT DATA SETUP
    map<int, vector<PumpPins> > pumps;
    pumps[0] = vector<PumpPins>();
    pumps[1] = vector<PumpPins>();
    
    PumpPins pumpOne;
    pumpOne.enablePin = engagePin1;
    pumpOne.dataPin1 = hIn1;
    pumpOne.dataPin2 = hIn2;
    
    pumps[1].push_back(pumpOne);
    
    PumpPins pumpTwo;
    pumpTwo.enablePin = engagePin2;
    pumpTwo.dataPin1 = hIn3;
    pumpTwo.dataPin2 = hIn4;
    
    pumps[0].push_back(pumpTwo);
    
    saltData.setup(arduino, pumps);
    
    // SETUP SPACEBREW + CONNECT TO PUMP DATA
    spacebrew.addSubscribe("gplus_api", &saltData.APIlevels[0].value );
    spacebrew.addSubscribe("numPeople", &saltData.localLevels[0].value );
    spacebrew.connect(host, name);
}

//--------------------------------------------------------------
void testApp::update()
{
    // update arduino if we're set up
    arduino.update();
    if ( bSetupArduino && !bUseData){
        
        arduino.sendPwm(engagePin1, pumpOneVal);
        arduino.sendDigital(hIn1, ARD_HIGH);
        arduino.sendDigital(hIn2, ARD_LOW);
        
        arduino.sendPwm(engagePin2, pumpTwoVal);
        arduino.sendDigital(hIn3, ARD_HIGH);
        arduino.sendDigital(hIn4, ARD_LOW);
    }
    
    saltData.bWriteToPumps = bUseData;
    
    // update kinect!
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
    gobStopper.setUniform1f("minVal", shaderMin);
    gobStopper.setUniform1f("maxVal", shaderMax);
    ofScale((float) colorMap.getWidth() / kinect.getWidth(), (float) colorMap.getHeight() / kinect.getHeight());
    colorMesh.draw();
    gobStopper.end();
    colorMap.end();
    
    if ( bUseCL ){
        cml->render();
        
    // non-camara Lucida
    } else {
        ofEnableDepthTest();
        ofPushMatrix();
//        ofRotateX(rotateX);
//        ofRotateX(rotateY);
//        ofRotateX(rotateZ);
        ofTranslate(translateX, translateY,translateZ);
        colorMap.begin();
        cml->getMesh()->render();
        colorMap.end();
        ofPopMatrix();
    }
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
    
    ofTranslate(translateX * (cml->gpu() ? 10.0 : 1.0), translateY * (cml->gpu() ? 10.0 : 1.0),translateZ * (cml->gpu() ? 10.0 : 1.0));
    ofTranslate(0, 0, origin * (cml->gpu() ? 10.0 : 1.0));
    ofRotateX(rotateX);
    ofRotateY(rotateY);
    ofRotateZ(rotateZ);
    ofScale(scale, scale, scale);
    ofTranslate(0, 0, -origin);
}

//--------------------------------------------------------------
void testApp::render_2d(ofEventArgs &args)
{
    return;
    ofSetColor(255, 255, 255);
    //kinect.drawDepth(0, 0, 200, 150);
    ofDrawBitmapString("press h for help",10,10);
    //colorMap.draw(200,0,200,150);
    
    ofPushMatrix();
    ofTranslate(center);
    //ofEllipse(0, 0, 20, 20);
    ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::exit(){
    ofLog(OF_LOG_VERBOSE, "exit!");
    
    ofRemoveListener( cml->render_texture, this, &testApp::render_texture );
    ofRemoveListener( cml->render_3d, this, &testApp::render_3d );
    ofRemoveListener( cml->render_2d, this, &testApp::render_2d );
    
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
        case 's':
            gui->saveSettings("settings/gui.xml");
            break;
    }
}


//--------------------------------------------------------------
void testApp::setupArduino(const int & version){
    cout <<"ARDUINO SET UP!" << endl;
    // remove listener because we don't need it anymore
	ofRemoveListener(arduino.EInitialized, this, &testApp::setupArduino);
    
    
    // Note: pins A0 - A5 can be used as digital input and output.
    // Refer to them as pins 14 - 19 if using StandardFirmata from Arduino 1.0.
    
    // Set up based on data we loaded!
    // engage pins == PWM, everything else is digital output
    
	arduino.sendDigitalPinMode(engagePin1, ARD_PWM);
	arduino.sendDigitalPinMode(engagePin2, ARD_PWM);
    
	arduino.sendDigitalPinMode(hIn1, ARD_OUTPUT);
	arduino.sendDigitalPinMode(hIn2, ARD_OUTPUT);
	arduino.sendDigitalPinMode(hIn3, ARD_OUTPUT);
	arduino.sendDigitalPinMode(hIn4, ARD_OUTPUT);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // debug
}

//--------------------------------------------------------------
// non-used events...

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
