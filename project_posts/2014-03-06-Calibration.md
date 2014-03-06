#Camera to Kinect Calibration

A big technical challenge of our project is calibrating a projector and depth camera. Luckily, people much better at math have tackled this challenge in a number of toolkits:
* [Gene Kogan's KinectProjectorToolkit for Processing](https://github.com/genekogan/KinectProjectorToolkit)
* [Christian Parsons' ofxCamaraLucida](https://github.com/chparsons/ofxCamaraLucida)
* [Nicolas Burrus' amazing RGBDemo](http://labs.manctl.com/rgbdemo/)
* Many others (work by Kyle McDonald, Elliot Woods, and others comes to mind)

Gene Kogan's is among the easiest to use, but we're going to use Christian Parson's toolkit because a) I have experience with it and b) we're using openFrameworks to drive visuals in our project. We <3 OF.

## Setting up
This step-by-step is based on Christian's guide [on his site](http://chparsons.com.ar/#camara_lucida/tutorials/calib)
* I began a detailed tutorial of compiling RGBDemo for 10.9, but it was a nightmare. Save yourself some trouble and [download the binaries](http://labs.manctl.com/rgbdemo/index.php/Main/Download)
* Open Christian's tutorial and download + print his checkerboard
	* Open Christian's checkerboard on your projector
* Open the RGBDemo rgbd-viewer
	* Grab A LOT of frames with the checkerboard in multiple poses (in OS X, grab with CMD + g)
	* Make sure you project the above-mentioned projected chessboard onto the center of your board
* Here's where things get weird: running the calibration app
	* First: copy all of your captures (RGBDemo/grab1/XXXXX/viewXXX folders) UP ONE LEVEL
		* Now you should have a folder called grab1 with a bunch of sub-folders named something like "view0000-1.072000" and so on.
	* in Terminal:
		* cd to where the calibration app lives (e.g. RGBDemo/)
		* copy a kinect_calibration.yml file into the RGBDemo directory (there's one in each ofxCamaraLucida example bin folder)
		* run the app from the command line: calibrate-projector.app/Contents/MacOS/calibrate-projector grab1 --kinect kinect_calibration.yml --output projector_calibration.yml --projector-width 800 --projector-height 600
			* Change the last two params if you have a higher res projector!
		* Watch the magic unfold
* Time to test! 
	* Download openframeworks...
	* Clone ofxCamaraLucida into of/addons
	* Copy your new projector_calibration.yml to addons/ofxCamaraLucida/example_freenect/bin/data/camara_lucida
	* (Optional) edit addons/ofxCamaraLucida/example_freenect/bin/data/camara_lucida/config.xml IF your projector is not 1024x868
	* open and run the Xcode project
		* I had some trouble with the example based off it using the old GLUT windows; changing main.cpp to the most basic code fixed that:
		```
		int main() {
			ofSetupOpenGL(800, 600, OF_WINDOW);
			ofRunApp(new testApp());
		}
		```

That's it! We had to run the whole process a few times to ensure we had good images... You'll notice pretty quickly if your stuff isn't calibrated well. And do keep in mind: you need to recalibrate any time you move your projector and camera. Next steps for us: make a permanent rig for the two, since that's the worst!

# Next Up: Putting it together with our visual prototypes

- Brett

