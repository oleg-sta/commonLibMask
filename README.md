# commonLibMask

> I created submodule for android application. It could be used as a tutorial to find interesting information how to implement specific things.

## What is it?

This submodule for android application. It works with android camera stream, find on every frame face by OpenCv library,
then special points on face by dlib library. Then use 3d model of face with moving parts to find position of the face with blend
shape coefficients. Then it is used android glsl to create 3d effect on camera stream and it is shows on screen.

# Table of Contests

- [What is it?](#what-is-it)
- [How it works?](#how-it-works)
    - [Working with camera](#working-with-camera)
    - [Finding face on frame](#finding-face-on-frame)
- [How to use it?](#how-to-use-it)

## How it works

### Working with camera

Here you could find how to work with camera 

### Finding face on frame

Here used OpenCV library with Haar Cascades. You could read about this here 

### Finding points on face

Here is used dlib library http://dlib.net/. I used method http://dlib.net/python/index.html#dlib.shape_predictor. It is based on article One Millisecond Face Alignment with an Ensemble of Regression Trees by
Vahid Kazemi and Josephine Sullivan, CVPR 2014. 

### Use 3d model to get position and blendshapes

There is 3d-model of face with blendshape, you could download this ...

### Draw 3d picture by glsl

On Android you could use OpenGL for high performance 3d or 3d graphics. I used OpenGL 2.0 you could find examples in other project here ...

## How to use it

Example of use you could find by link: ...
