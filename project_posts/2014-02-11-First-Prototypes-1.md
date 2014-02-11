#History, Part I

We figured we'd start the project with a quick survey of where we're at. 

In the repo right now is all of the code we used to create our first prototype, results of which you can see [here](https://vimeo.com/78356704). 

Shobun and I began our project with a set of prototypes:
* Initial salt sculptures by Shobun
* Testing water output
* Building a simple projector<->depth camera prototype
	* This included testing a few existing projector to camera calibration setups, including ofxCameraLucida

Our first water output prototype looked like this:
![Water Prototype](http://farm8.staticflickr.com/7360/12460968424_33a1d943ae_o.jpg)
It was built in Shobun's bathtub using a pretty simple setup:
* Arduino + Breadboard (in a handy plastic bag)
	* Please don't try this at home...
* A 12V Solenoid valve from [Sparkfun](https://www.sparkfun.com/products/10456)
	* We needed a separate [12V adaptor](https://www.sparkfun.com/products/9442) and a nice little [barrel adaptor](https://www.sparkfun.com/products/10288) to connect it to our breadboard 
	* We also needed a [transistor](http://www.radioshack.com/product/index.jsp?productId=2062618) to control the solenoid's power
* A garden hose
* A hose to sink adaptor (pretty useful!)
* A hose nozzle for a nice spray
* Some very, very simple [code](https://raw.github.com/robotconscience/devart-template/master/project_code/Arduino/SolenoidControl_001/SolenoidControl_001.ino)

It was really fun to use, so we tried a few different ways of interacting with it:
* [Serial to Solenoid](http://www.flickr.com/photos/robotconscience/12460628573/)
* [Optical flow to Solenoid](http://www.flickr.com/photos/robotconscience/12460458005/)
* [Sound to Solenoid](https://mtc.cdn.vine.co/v/videos/C39A5CEC-F150-45F0-A5ED-7F0C9A7FF5B7-1199-000000B225CB1E2A_1.1.1.mp4?versionId=qogH9TPzW1HkuU.mm7NWRBLbrFaHUA1w)

As you can see in the videos, the solenoid is really, really powerful. It requires a lot of pressure to even open, and so it gives off a lot of pressure when opened... Which would blast our poor sculptures to bits pretty much immediately. So, we went back to the drawing board on our water output (though we saved the solenoids for a future Steve Reich-inspired phasing experiment based on the amazing sound they make...).

In the interest of brevity, I'll be posting about our next prototypes in the following post!
