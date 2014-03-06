#version 120
#extension GL_ARB_texture_rectangle: enable

uniform sampler2DRect depth_tex;
uniform vec3 center;
uniform vec3 colors[10];
varying vec4 pos;

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
    
    float dist = distance(pos.xyz, center);
    int c = int(ofMap(dist, 0., 1000.0, 0., 9, true) );
    
    gl_FragColor = vec4(colors[c].rgb, 1.0);//color.r > 0.0 ? vec4(colors[c].rgb, 1.0) : vec4(0,0,0,0);
}

