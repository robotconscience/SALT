#Second Prototype

This week was a big week: we finished building and testing our second prototype for the installation.

For the second prototype, we secured a studio space to build a "beta" version; that is, some working version of each piece. That included:
* Pedestal for the salt objects
* Reservoir for circulating water
* Prototype rig for water tubing and Kinect
* Two interactive peristaltic pumps   
  * Pump 1: connected to web-based inputs (Google+ for this prototype)
  * Pump 2: connected to number of people in the space (via [TSPS](http://openTSPS.com))
* Projection and software running off of a single computer

## Pedestal and Reservoir

We constructed a simple wood frame that we stretched some fiberglass screen over to build a platform that our dissolving salt could fall through. We stuck a bucket under it, which will function as the reservoir for our salt solution as well as our water source. We're avoiding the desalination process until we absolutely have to do it.

![Wood Frame  and Bucket](https://raw.github.com/robotconscience/devart-template/master/project_images/prototype_2/Prototype2_5.JPG)  

## Camera and Tubing Rig

We built a small ring out of PVC that hangs above the salt object for holding the output for the water and the Kinect camera. The tubes fit through holes drilled through the PVC keep tubing in place

![PVC](https://raw.github.com/robotconscience/devart-template/master/project_images/prototype_2/Prototype2_3.JPG)  

![Kinect and Tubes](https://raw.github.com/robotconscience/devart-template/master/project_images/prototype_2/Prototype2_11.JPG)  

## Peristaltic Pumps

Also hanging from the ceiling of the studio were two peristaltic pumps and the Arduino setup.  We built a separate swing for them since the motors make the whole apparatus move around a bit (and it’s imperative that our Kinect rig moves very little, if at all). From there the tubes connect down to the reservoir and pump water up to be dropped down onto the salt.

![Peristaltic Pump](https://raw.github.com/robotconscience/devart-template/master/project_images/prototype_2/Prototype2_7.JPG) 

![Basic Setup](https://raw.github.com/robotconscience/devart-template/master/project_images/prototype_2/Prototype2_11.JPG)

## Projection

For time and ease of installation, we projected onto the salt object from the side. Of course, this introduced issues with obfuscation (both from visitors as well as the opposite side of the salt itself). It also required we change the calibration setup: since the projector and Kinect were not parallel, we could not use our calibration process. So, we created a simple interface to take the existing calibration and rotate, scale, and translate the 3D mesh from the Kinect into place. It’s definitely too finicky for production, but worked well for the prototype.

![Calibration](https://raw.github.com/robotconscience/devart-template/master/project_images/prototype_2/Prototype2_screenshot_calibration.png)

Once we had the calibration worked out and the projection mapped onto our salt object, we began running the peristaltic pumps and connected our inputs (G+ API and TSPS) to our installation via Spacebrew. Our Spacebrew server is running in the cloud via Compute Engine so, though we are using a single machine now, we are free to split our processing and output across multiple machines. And, we can access and store our data on the web for future exploration.

## Color

![Projection](https://raw.github.com/robotconscience/devart-template/master/project_images/prototype_2/Prototype2_projection.jpg)

![Projection](https://raw.github.com/robotconscience/devart-template/master/project_images/prototype_2/Prototype2_projection.gif)

We worked on a number of systems for the color, and settled on what you see above (systemically, not the colors themselves). We’re affectionately calling it the “gobstopper” system: it’s a series of colors arranged in concentric spheres. Colors are revealed abruptly as the salt dissolves, making clear the changes across its surface.

# Prototype #3

We’re building our final prototype over the next week. It will be a slightly more polished update to #2. This next prototype will include:

* Ceiling mounted projector: will allow us to use the calibration system, eliminate obfuscation issues
* Closed pedestal: hiding our armature and preventing the huge mess we made this time…
* Multiple APIs: YouTube, Google+, and Twitter
* Ceiling mounted camera: tracking people with a single camera mounted above the installation
* New pump layout: our water output was too focused this week, so we’re working on a servo motor-based solution to move the output over time for more even dissolution


