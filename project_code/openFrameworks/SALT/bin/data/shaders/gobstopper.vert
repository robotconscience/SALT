#version 120
#extension GL_ARB_texture_rectangle: enable

varying vec4 pos;

void main(){
    vec4 vert = gl_Vertex;
    vert.z *= .1;
    pos = gl_Vertex;
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vert;
}