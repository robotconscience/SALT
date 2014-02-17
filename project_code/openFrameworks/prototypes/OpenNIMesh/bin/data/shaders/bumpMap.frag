varying vec4 pos;

void main(){
    if ( pos.z < 1.0 ){
        discard;
    } else {
        gl_FragColor = gl_Color;
    }
}
