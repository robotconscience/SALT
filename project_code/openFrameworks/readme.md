#Folder breakdown
* addons/
	* All addons we're using in our projects/prototypes
* CalibrationAssets
	* Assets for camaralucida-based calibration. Only valid for our setup, sorry!
* prototypes
	* ColorPrototype
		* First tests for coloring our projection based on amount of salt dissolved
	* flowSerial
		* Very early prototype that sent translated optical flow-based activity to activate a solenoid over serial (very basic!)
	* OpenNIMesh
		* Simple example we created that uses a shader to extrude an arbitrary mesh from an openNI-capable camera
	* ProjectionFilm
		* First prototype: connecting camara lucida and a film Shobun made
		* Uses openNI camera data to reveal a portion of the video on a 3D object
		* At this point, all Arduino pieces (e.g. the pump) were separate!
	* ProjectionPrototype_001
		* Outdated/incomplete early prototype using ofxCamaraLucida and a mesh. Old and grey, this project..
* SALT
	* Ongoing "main" project
	* Setting up:
		* Download/clone openFrameworks
		* copy content of "addons" int openFrameworks/addons
		* copy SALT folder to openFrameworks/apps/myApps or a similar folder level (e.g. openFrameworks/apps/devArt)
		* open, compile, run!
	* Requirements
		* Kinect camera connected
		* An Arduino
			* name of arduino 