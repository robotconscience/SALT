//
//  SaltData.h
//  SALT
//
//  Created by Brett Renfer on 3/20/14.
//
//  This class will process incoming data from Spacebrew and transform it
//  into activity levels for our pumps

#pragma once

#include "ofMain.h"

// for talking about activity, we want some sort of human-readable data
// about what it is, and some idea of a min/max for scaling values
struct SaltActivity {
    string name;
    int min = 0;
    int max = 1;
    int value = 0; //raw value from some API
};

struct PumpPins {
    int enablePin;
    int dataPin1;
    int dataPin2;
};

class SaltData {
public:
    
    // this is weird right now, will re-architect when i have a better idea
    // @param {ofArduino} ard
    // @param {map<int,PumpPins>} pumpData map, where int == 0 or 1; 0 == api, 1 == local
    void setup( ofArduino & ard, map<int, vector<PumpPins> > pumpData ){
        // hook into arduino object
        arduino = &ard;
        
        // for now, let's set up the APIs in here?
        SaltActivity gplus;
        gplus.min = 0; gplus.max = 12;
        APIlevels.push_back( gplus );
        
        SaltActivity peopleInSpace;
        peopleInSpace.max = 2; // right now, it's just shobun and i in here!
        localLevels.push_back(peopleInSpace);
        
        // how many pumps are we controlling?
        map<int, vector<PumpPins> >::iterator it = pumpData.begin();
        for (it; it != pumpData.end(); ++it ){
            cout << it->first << endl;
            switch ( it->first ){
                case 0:
                    pumps_api.insert( pumps_api.begin(), it->second.begin(), it->second.end());
                    break;
                case 1:
                    pumps_local.insert( pumps_local.begin(), it->second.begin(), it->second.end());
                    break;
                default:
                    ofLogWarning()<<"Got a weird pump index! "<<it->first;
            }
        }
        
        bWriteToPumps = true;
        
        // auto-update
        ofAddListener(ofEvents().update, this, &SaltData::update);
    }
    
    void update( ofEventArgs & e ){
        // get average of API input
        float APIAverage = 0;
        for (int i=0; i<APIlevels.size(); i++){
            APIAverage += ofMap(APIlevels[i].value, APIlevels[i].min, APIlevels[i].max, 0.,1.0,true);
//            APIlevels[i].value *= .999; // easing down now in case we don't get values a lot?
        }
        APIAverage /= (float) APIlevels.size();
        
        cout << "api " << APIAverage << endl;
        int apiValue = ofMap(APIAverage, 0, 1.0, 100, 255 );
        
        cout << apiValue << endl;
        
        // get average of local input
        float localAverage = 0;
        for (int i=0; i<localLevels.size(); i++){
            localAverage += ofMap(localLevels[i].value, localLevels[i].min, localLevels[i].max, 0.,1.0,true);
        }
        localAverage /= (float) APIlevels.size();
        
        cout << "local " << localAverage << endl;
        int localValue = ofMap(localAverage, 0, 1.0, 100, 255 );
        
        cout << localValue << endl;
        
        
        // pumps freak out at 0-100!
        if ( apiValue == 100 ) apiValue = 0;
        if ( bWriteToPumps ){
            for ( int i=0; i<pumps_api.size(); i++){
                arduino->sendPwm(pumps_api[i].enablePin, apiValue);
                arduino->sendDigital(pumps_api[i].dataPin1, ARD_HIGH);
                arduino->sendDigital(pumps_api[i].dataPin2, ARD_LOW);
            }
            
            for ( int i=0; i<pumps_local.size(); i++){
                arduino->sendPwm(pumps_local[i].enablePin, localValue);
                arduino->sendDigital(pumps_local[i].dataPin1, ARD_HIGH);
                arduino->sendDigital(pumps_local[i].dataPin2, ARD_LOW);
            }
        }
    }
    
    vector<SaltActivity> APIlevels;      // ambient data from "the web"
    vector<SaltActivity> localLevels;    // local activity (e.g. number of people in the space!)
    
    vector<PumpPins>     pumps_api;       // where should this relationship be set up??!?!?
    vector<PumpPins>     pumps_local;       // where should this relationship be set up??!?!?
    
    bool bWriteToPumps;
    
protected:
    
    ofArduino * arduino;
};