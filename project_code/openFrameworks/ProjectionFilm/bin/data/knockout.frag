
uniform sampler2DRect tex;
uniform sampler2DRect alphaTex;

void main (void) {
    vec4 color = texture2DRect(tex, gl_TexCoord[0].st);
    float alpha = texture2DRect(alphaTex, gl_TexCoord[0].st).r;
    if ( alpha == 0.0 ){
        color.r = color.g = color.b = 0.0;
    }
    color.a = alpha;
    gl_FragColor = color;
    
}