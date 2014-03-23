#version 120
#extension GL_ARB_texture_rectangle: enable

uniform sampler2DRect depth_tex;
uniform vec3 center;
uniform vec3 colors[10];
varying vec4 pos;

uniform float minVal;
uniform float maxVal;

float ofMap(float value, float inputMin, float inputMax, float outputMin, float outputMax, bool bClamp) {

    float outVal = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);
    
    if( bClamp ){
        if(outputMax < outputMin){
            if( outVal < outputMax ) outVal = outputMax;
            else if( outVal > outputMin ) outVal = outputMin;
        }else{
            if( outVal > outputMax ) outVal = outputMax;
            else if( outVal < outputMin ) outVal = outputMin;
        }
    }
    return outVal;
}

void main()
{
    vec2 p2 = gl_TexCoord[0].st;
    vec4 color = texture2DRect( depth_tex, p2 );
    vec3 adj = vec3(pos.xyz);
    adj.z = ofMap(adj.z, minVal, maxVal, 0, 1000.0, true );
    
    float dist = distance(adj.xyz, center);
    int c = int(ofMap(dist, 0., 1000.0, 0., 9, true) );
    
    if ( pos.z > maxVal || pos.z < minVal ){
        discard;
    } else {
        gl_FragColor = vec4(colors[c].rgb, 1.0);//color.r > 0.0 ? vec4(colors[c].rgb, 1.0) : vec4(0,0,0,0);
    }
}

