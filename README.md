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

You have to manually download dlib sources from here https://github.com/davisking/dlib/tree/master/dlib. Put it in https://github.com/oleg-sta/commonLibMask/tree/master/src/main/jni dlib dir. I didn't put sources to repository because there a lot of codes and didn't figured out how to use it as dependency.

## How it works

Here you can find a explaining how this library works. It integrates a lot of different fields: working with camera, machine learning algorithms for finding face and points on it, mathematics - to find position in space and morphings and finally OpenGL to draw fastly on screen.

### Working with camera

Here you could find how to work with camera. Main class is [FastCameraView](https://github.com/oleg-sta/commonLibMask/blob/master/src/main/java/ru/flightlabs/masks/camera/FastCameraView.java)

### Finding face on frame

Here used OpenCV library with Haar Cascades. You could read about this [here](https://docs.opencv.org/3.4.1/d7/d8b/tutorial_py_face_detection.html)

### Finding points on face

Here is used [dlib](http://dlib.net/) library. I used method [shape_predictor](http://dlib.net/python/index.html#dlib.shape_predictor). It is based on article [One Millisecond Face Alignment with an Ensemble of Regression Trees by
Vahid Kazemi and Josephine Sullivan, CVPR 2014](http://www.nada.kth.se/~sullivan/Papers/Kazemi_cvpr14.pdf). 

### Calculate face position and blendshapes

There is 3d-model of face with blendshape, you could download this ...

### Draw by OpenGL

On Android you could use OpenGL for high performance 3d or 3d graphics. I used OpenGL 2.0 you could find examples in other project here ...

## How to use it

Example of use you could find by link: ...
