# commonLibMask

> I created submodule for android application. It could be used as a tutorial to find interesting information how to implement specific things.

## What is it?

This submodule for android application. It works with android camera stream, find on every frame face by OpenCv library,
then find special points on face by dlib library. Then use 3d model of face with moving parts to find position of the face with blend
shape coefficients. Then it is used android glsl to create 3d effect on camera stream and it shows on screen.

# Table of Contests

- [What is it?](#what-is-it)
- [Settings](#settings)
- [How it works?](#how-it-works)
    - [Working with camera](#working-with-camera)
    - [Finding face on frame](#finding-face-on-frame)
    - [Finding points on face](#finding-points-on-face)
    - [Calculate face position and blendshapes](#calculate-face-position-and-blendshapes)
    - [Draw by OpenGL](#how-to-use-it)
- [How to use it?](#how-to-use-it)

## Settings

You have to manually download dlib sources from here https://github.com/davisking/dlib/tree/master/dlib. Put it in https://github.com/oleg-sta/commonLibMask/tree/master/src/main/jni dlib dir. I didn't put sources to repository because there a lot of codes and didn't figure out how to use it as dependency. Yes, it's bad, but I made simple bad solution.

## How it works

Here you can find an explaining how this library works. It integrates a lot of different fields: working with camera, machine learning algorithms for finding face and points on it, mathematics (SVD decomposition) - to find position in space and morphings and finally OpenGL to draw it fastly on a screen.

### Working with camera

First start with camera. Main class is [FastCameraView](https://github.com/oleg-sta/commonLibMask/blob/master/src/main/java/ru/flightlabs/masks/camera/FastCameraView.java). 

### Finding face on frame

Here used OpenCV library with Haar Cascades. You could read about this [here](https://docs.opencv.org/3.4.1/d7/d8b/tutorial_py_face_detection.html).

### Finding points on face

Here is used [dlib](http://dlib.net/) library. I used method [shape_predictor](http://dlib.net/python/index.html#dlib.shape_predictor). It is based on article [One Millisecond Face Alignment with an Ensemble of Regression Trees by
Vahid Kazemi and Josephine Sullivan, CVPR 2014](http://www.nada.kth.se/~sullivan/Papers/Kazemi_cvpr14.pdf). 

### Calculate face position and blendshapes

When we have points on face on 2d model we need to calculate position and blends coefficient (e.g. opened jaw) on 3d model. All main magic is in [DetectionBasedTracker_jni](https://github.com/oleg-sta/commonLibMask/blob/master/src/main/jni/DetectionBasedTracker_jni.cpp) method Java_ru_flightlabs_masks_DetectionBasedTracker_morhpFace. We calculate approximate position of 3d model by solving equation:<br/>
dst=argminX∥src1⋅X−src2∥ by SVD decomposition, you could find [here](https://docs.opencv.org/3.1.0/d2/de8/group__core__array.html#ga12b43690dbd31fed96f213eefead2373)

Then we have to find coefficient for morphing face also solving almost the same equation dst=argminX∥src1⋅X−src2∥ by SVD decomposition.
By the output you have 3d model with position in space, with blends coefficient.

### Draw by OpenGL

Al least you have to draw all on the screen. Here I use OpenGL.

## How to use it

Example of use you could find [here](https://github.com/oleg-sta/Masks)
