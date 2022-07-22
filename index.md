# Arduino Midi Controller
A midi controller is a device with buttons and knobs that mimic that of a real instrument, but instead make no sound and send signals to your computer's midi software, playing sounds through your speakers. The difference between midi and real instruments is that you can mimic different instruments from different controllers, like a trombone from a piano controller, or a harp from a guitar controller.

| **Engineer** | **School** | **Area of Interest** | **Grade** |
|:--:|:--:|:--:|:--:|
| Shashank | Monta Vista High School | Game Design | Incoming Senior

![Headstone Image](https://lh3.googleusercontent.com/pw/AM-JKLUAkC9phMFWO-M6XI3-yLgs6uXtQueA0Dsje7uUV5icQ2FD9q339wvN3TNKMwkSLDNE_EP8jKJ7deakIn_tduXOjK-PhGXl9_4G6zPutxFA27blU9xTUcbTD5S96e-zon6CKf39v3PXXFxBO5x-ZdU=s1720-no?authuser=0)
  
# Final Milestone

For my final milestone, I added an LED neopixel strip to the side of the midi controller, which sent a light pulse around it whenever I recieved a note signal from my computer. To do this, I needed to add an alternate power source, so I took a 9volt power source, regulated it to 5volt, and connected just my neopixels to it, so that I could choose whether I wanted them on or off. I drilled another 2 holes in order to fit the pixel strip and the 9volt power wire through. It can also accept midi signals and send a color corresponding to the note down the strip. I also added 4 buttons and changed one knob to change octave.

[![Milestone 3](https://res.cloudinary.com/marcomontalbano/image/upload/v1657829481/video_to_markdown/images/youtube--I6Ldl7sl8_s-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://www.youtube.com/watch?v=I6Ldl7sl8_s "Milestone 3")

**[Link To Schematic](https://user-images.githubusercontent.com/88253938/180550267-e88a3bac-b0cd-44e0-9c1e-c5c0917d4654.png)**

# Second Milestone!

My second milestone was soldering all the componenets to a perfboard and putting everything in a box. I soldered wires to every componenet and haphazardly stuck them in the perfboard, connecting ground with ground and 5volt with 5volt with large amounts of solder. I also drilled circular holes in the top of the box to put the buttons and knobs in, as well as a circular hole that I spent half an hour filing into a rectangle for the USB that powered the arduino. after stuffing everything into the box, I hooked it up to my computer and played around with it, making a demo song with Delay Lama.

[![Milestone 2](https://res.cloudinary.com/marcomontalbano/image/upload/v1657829440/video_to_markdown/images/youtube--3B9JGQWBSp0-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://www.youtube.com/watch?v=3B9JGQWBSp0 "Milestone 2")
# First Milestone
  
My first milestone was finishing the code and prototype of the midi machine. I searched online for the libraries I needed and yoinked the code I needed from several websites. Then, I wired a single button and a single poteminator to the breadboard with test code in order to figure out how they worked. After realizing that I can add as many buttons as I want because it doesn't use voltage, I chose to have 8 buttons and 4 knobs. I chose not to use sliders and stuck to knobs, because the sliders heated up when I wired them. After fully wiring everything, I downloaded some software that was compatible with arduino, and made sure the componenets worked.

[![First Milestone](https://res.cloudinary.com/marcomontalbano/image/upload/v1656741203/video_to_markdown/images/youtube--uNW3vx6xUfY-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://www.youtube.com/watch?v=uNW3vx6xUfY "First Milestone")

# Starter Project - Arduino 8x8 Neopixel Matrix
  
For my starter project, I built an 8x8 pixel matrix. To do this, I had to wire the matrix to the arduino. This was really easy, so I added a button to it. I only had 2 components, so I didn't need to use a breadboard. I searched up the libraries I needed and added them, then wrote a couple of lines of code that made the matrix glow red when I pressed the button, then switch to green and fade away when I release it.

[![Starter Project](https://res.cloudinary.com/marcomontalbano/image/upload/v1656741169/video_to_markdown/images/youtube--PZVI2LNtGMw-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://www.youtube.com/watch?v=PZVI2LNtGMw "Starter Project")
