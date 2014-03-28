# SALT

## Authors
- [Brett Renfer](http://www.robotconscience.com): @robotconscience
- [Shobun Baile](http://shobunbaile.com/)
- (More on us below!)

## Description
### Overview
SALT is a physical, digital, and sonic sculpture that is gradually destroyed by direct and indirect human interaction, with the goal of making global-scale ecological concerns compelling and accessible to a wide audience. 

The sculpture is centered around a single salt-based sculpture that slowly dissolves at a rate controlled by the physical presence of visitors at the installation, as well as virtual influences coming from a range of data harvested from online activity.

Live programatic visuals will be directly mapped onto the salt object as it dissolves and will be accompanied by multi-channel audio output. The visual and audio elements will degrade as a direct result of the salt dissolving, creating a visceral connection between the physical and the digital.

### Interaction
We are attempting to describe climate change at the systemic level from a factual, ambivalent perspective. Through interaction we are giving visitors a choice: do they approach the sculpture, marvel at the process of its decay, and in doing so guarantee future visitors will never get to see it in this same state, or perhaps never at all? However, those that choose to remove themselves from the process must watch as ambient sources (culled from online data) slowly continue to destroy the piece. 

Ostensibly, the visitor could take to the internet, pleading with people to halt their various activities. This process, albeit heculean, is not entirely impossible, but conveys the difficulty and complexities involved in halting processes of this scale and global influence (e.g. climate change). Of course, those with great influence could also be tapped as well to halt or pause this activity as well... But just as in the real-world system, this task proves as difficult as organizing a larger, distributed effort.

## Project Proposal

Please view our full project proposal at [Slideshare](http://www.slideshare.net/slideshow/embed_code/31085739)

### Sensing platform
A single depth camera (Kinect, ASUS Xtion, or similar) continously scans the salt sculpture. Multiple web cameras distributed around the sculpture sense the presence and proximity of visitors.

![Salt sensing](https://github.com/robotconscience/devart-template/raw/master/project_images/salt_exp_01.png?raw=true)

### Output
Two concentric rings of [peristaltic pumps](http://www.adafruit.com/products/1150) sit above the sculpture. As visitors approach the scuplture, the pump nearest to them in the outer ring begins to emit water. As they get closer, the stream intensifies.

Each pump on the inner ring is connected to a range of APIs, creating a semi-constant stream of varying intensity.

![Output](https://github.com/robotconscience/devart-template/raw/master/project_images/salt_exp_02.png?raw=true)
![Output](https://github.com/robotconscience/devart-template/raw/master/project_images/salt_exp_03.png?raw=true)

### Salt Sculptures
The sculptural elements of the salt installation are built using basic non-iodized table salt and small amounts of soy wax. The salt is ground into a fine powder, and then heated with water and a small amount of soy wax, forming a paste. The paste is rapidly formed into small unit blocks, then cooled and dried at room temperature. These smaller units are used to form the larger structures used for the installation, bound by another salt paste mixture. Once these final objects have dried, they are sanded into their final shapes.

![Sculpture](https://raw.githubusercontent.com/robotconscience/devart-template/master/project_images/saltobjects_1and2.jpg)

### Software + Hardware Breakdown

![Software Architecture](https://raw.githubusercontent.com/robotconscience/devart-template/master/project_images/diagrams/software_architecture.jpg)

![Hardware](https://raw.githubusercontent.com/robotconscience/devart-template/master/project_images/diagrams/hardware_architecture.jpg)

## Prototypes

[Video: Beta Prototype](https://www.youtube.com/watch?v=Uznlm7nx28U)

### Process Prototypes

[Video: Alpha Prototype](https://vimeo.com/78356704)
[Video: Depth color prototype](https://vimeo.com/87061029)

## Example Code
All example code is included in our project posts. Some important ones:
* [Calibrating a Kinect and projector with ofxCamaraLucida and RGBDemo](https://github.com/robotconscience/devart-template/blob/master/project_posts/2014-03-06-Calibration.md)
* [Connecting APIs to Spacebrew with Temboo](https://github.com/robotconscience/devart-template/blob/master/project_posts/2014-03-14-APIs.md)
* [Setting up Spacebrew with Google Compute Engine](https://github.com/robotconscience/devart-template/blob/master/project_posts/2014-03-21-Cloud.md)

## Links to External Libraries

### Core Frameworks
* [openFrameworks](https://github.com/openframeworks/openFrameworks "openFrameworks") 
* [Arduino](http://arduino.cc)
* [Spacebrew](http://docs.spacebrew.cc)
  * [spacebrew server](https://github.com/spacebrew/spacebrew) 
  * [ofxSpacebrew](https://github.com/spacebrew/ofxSpacebrew)
  * [ofxLibwebsockets](https://github.com/labatrockwell/ofxLibwebsockets)
  * [spacebrew.js](https://github.com/spacebrew/spacebrew.js)
* [TSPS](http://openTSPS.com)
* [Temboo](http://www.temboo.com)

### Libraries: Calibration and Sensing
* [ofxCamaraLucida](https://github.com/chparsons/ofxCamaraLucida)
* [RGBDemo](https://github.com/rgbdemo/rgbdemo)
* [ofxCv](https://github.com/kylemcdonald/ofxCv "ofxCv")

### Libraries: Utilities
* [ofxUI](https://github.com/rezaali/ofxUI/)

## About Us

Brett Renfer is an experience designer and maker. He has created architectural-scale interactive installations for ZER01, Intel, Google, JetBlue, the Cosmopolitan of Las Vegas, the Whitney Museum of Art, and the National Building Museum. He also develops and supports open source projects that lower the barrier of entry to interaction design, including [TSPS](http://github.com/labatrockwell/opentsps) and [Spacebrew](http://www.spacebrew.cc). Brett is director of experience design and Collins and adjunct faculty at the New School and New York University.
* http://www.robotconscience.com

Shobun Baile is a film/video artist  with a background in non-organic chemistry. His work deals with ecology, gender and sexual identity, and personal histories. He is the assistant editor of Framework Cinema & Media Journal, and a researcher in neuropathology at Columbia University.
* http://shobunbaile.com

Brett and Shobun have been working together since 2013. Salt is their first formal collaboration, and is first in a series of experiences centered around interaction, the environment, and ephermerality.

## Images & Videos

![Projection](https://raw.githubusercontent.com/robotconscience/devart-template/master/project_images/Prototype2_5/prototype_humanscale.jpg)

SALT Prototype 2.5

![Projection](https://raw.githubusercontent.com/robotconscience/devart-template/master/project_images/Prototype2_5/prototype_rig.jpg)

SALT Prototype 2.5: Tracking and output rig

![SALT](http://farm4.staticflickr.com/3703/9571458893_666d613ec1_b.jpg "Salt Image 1")
SALT Prototype 1: Aftermath

![Projection](https://raw.githubusercontent.com/robotconscience/devart-template/master/project_images/prototype_2/Prototype2_projection.jpg)
SALT Prototype 2: Projection

![Calibration](https://raw.githubusercontent.com/robotconscience/devart-template/master/project_images/prototype_2/Prototype2_8.JPG)
SALT Prototype 2: Calibration

![Rig](https://raw.githubusercontent.com/robotconscience/devart-template/master/project_images/prototype_2/Prototype2_11.JPG)
SALT Prototype 2: Process Rigging

![Pumps](https://raw.githubusercontent.com/robotconscience/devart-template/master/project_images/prototype_2/Prototype2_7.JPG)
SALT Prototype 2: Peristaltic Pumps + Arduino

