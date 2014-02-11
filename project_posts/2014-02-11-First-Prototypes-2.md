#History, Part II

Continuing our cataloging of our process to-date, we moved in parallel to our water prototypes to build/test a series of Kinect to projector calibration systems.

A toolkit I'd been wanting to try for a while (and where we started) is called [ofxCamaraLucida](http://chparsons.com.ar/#camara_lucida). It is based on the pretty mature set of depth camera tools called [RGBDemo](https://github.com/rgbdemo/rgbdemo). The latter was among the hardest parts to set up and will require its own post if we do indeed end up using it. Until then, the above-linked calibration tool is the place to start in this area!

I did start a branch of ofxCamaraLucida with support for OpenNI2, in hopes for a bit faster/cleaner lookup of depth/world data. It's a bit cobbled together, but can be found [here](https://github.com/robotconscience/ofxCamaraLucida/tree/feature-openni2).

Once I had a reasonable calibration set up, I set up a very simple shader to start testing visuals:

```
//knockout.vert
void main() {
    gl_Position   = gl_ModelViewProjectionMatrix * gl_Vertex;
}
```

```
//knockout.frag
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
```

What this does is allow me to pass in a 'draw' texture (video content produced by Shobun) and a mask texture (depth image from openNI). Anywhere the openNI2 image is black, we set the alpha of our draw texture to 0. So, what is sent out by the projector is only data that the Kinect/depth camera sees. The next step to make this work for our scale is to change the near/far range of our depth image. This adjusts how values from the depth camera are mapped to a grayscale image. By mapping a narrower range, we get a more accurate depth map, and can differentiate between much finder details.

It ended up looking like this, which we were really happy with: [Prototype](http://www.flickr.com/photos/robotconscience/12460979684/in/set-72157640835519934)
