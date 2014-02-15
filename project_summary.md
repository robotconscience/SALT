# SALT
(tentative Title)

## Authors
- [Brett Renfer](http://www.robotconscience.com): @robotconscience
- [Shobun Baile](http://shobunbaile.com/)

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

![Salt sensing](./project_images/salt_exp_01.png?raw=true)

### Output
Two concentric rings of [peristaltic pumps](http://www.adafruit.com/products/1150) sit above the sculpture. If visitors approach the scuplture, the pump nearest to them in the outer ring begins to emit water. As they get closer, the stream intensifies.

Each pump on the inner ring is connected to a range of APIs, creating a semi-constant stream of varying intensity.

![Output](./project_images/salt_exp_02.png?raw=true)
![Output](./project_images/salt_exp_03.png?raw=true)

### Salt Sculptures
The sculptural elements of the salt installation are built using basic non-iodized table salt and small amounts of soy wax. The salt is ground into a fine powder, and then heated with water and a small amount of soy wax, forming a paste. The paste is rapidly formed into small unit blocks, then cooled and dried at room temperature. These smaller units are used to form the larger structures used for the installation, bound by another salt paste mixture. Once these final objects have dried, they are sanded into their final shapes.

## Link to Prototype

[System Prototype 1](https://vimeo.com/78356704)

## Example Code
Coming soon!

## Links to External Libraries

* [openFrameworks](https://github.com/openframeworks/openFrameworks "openFrameworks")
* [ofxCv](https://github.com/kylemcdonald/ofxCv "ofxCv")
* [ofxNI2](https://github.com/satoruhiga/ofxNI2 "ofxNI2")
* [ofxCamaraLucida](https://github.com/chparsons/ofxCamaraLucida)
* Prototypes will most likely use [KinectProjectorToolkit](https://github.com/genekogan/KinectProjectorToolkit)
* [RGBDemo](https://github.com/rgbdemo/rgbdemo)


## Images & Videos

![SALT](http://farm4.staticflickr.com/3703/9571458893_666d613ec1_b.jpg "Salt Image 1")

https://vimeo.com/78356704
