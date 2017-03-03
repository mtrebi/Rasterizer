# IN PROGRESS

# Introduction

In order to be able to understand how rendering work I decided to implement a forward/deferred renderer (based on my experience with OpenGL) in the CPU. The goal of this project is not to create a next generation renderer or a super efficient CPU renderer. This project is just to understand how the rendering algorithms transforms a set of vertices that make up a 3D World into a 2D image of that World. I tried to be clear in my code to make it readable and easy to understand.

I've implement some basic features that I consider relevant for any graphics programmer to understand:
* Camera and Object rotations using Euler angles (roll, pitch, yaw)
* Object translations using 4x4 homogeneous matrices
* A depth-buffer to solve the visibility surface problem
* Phong and Blinn-Phong shading given material phong coefficients
* Phong and Blinn-Phong shading given material diffuse and specular textures
* Normal mapping
* Affine and Perspective corrected mapping for textures
* Bounding box optimization
* View frustrum clipping
* Orthographic and Perspective camera
* A forward and a deferred version of the renderer
* (TODO) Alpha blending
* (TODO) Back-face culling
* (TODO) Shadow maps

# Gallery

These are only some images generated with this renderer.

This is the first image that I generated. Just a flat triangle. It may seem super simple but it was the start of this renderer. When it worked, I was really really happy.
![First triangle render](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/first_render.bmp "First triangle render")



![Flat scene render using blinn phong](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/render_flat_scene_blinn_phong.bmp "Flat scene render using blinn phong")

![Textured scene render using blinn phong](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/render_textured_scene_blinn_phong.bmp "Textured scene render using blinn phong")


I've found funny to take pictures even when things go terribly wrong. First of all, because after you solved the problem, you can see why the image looked like that. Secondly, because some images are pretty cool. These are just some of the _terribly wrong but cool images* 


[Cool images followed by bug]






Checkout all the images at docs/images. 

## Features

### Camera and Object rotations using Euler angles (roll, pitch, yaw)

[IMAGE - Object rotated in all different axis]

Object.rotate(roll, pitch, yaw)

###  Object translations using 4x4 homogeneous matrices

[IMAGE - Object translation]

Object.translate()


### A depth-buffer to solve the visibility surface problem

Render to depth buffer image


### Orthographic and Perspective camera

[COMPARING IMAGE - Perspective vs orthographic]

### Affine and Perspective corrected mapping for textures

[COMPARING IMAGE - Affine vs Perspective corrected mapping]

# Rasterization

Checkout my blog posts about [rasterization](https://gamesandgraphicsdev.blogspot.com.es/2017/02/rasterization-i-overview.html) to understand step by step how it works.

# Future work

* Point lights with omnidirectional shadows (using cubemaps) and attenuation
* Sky boxes
* OBJ model loading
* Render to a window using some external library to achieve real time rendering

# References

Fletcher Dunn, Ian Parberry: “3D Math Primer for Graphics and Game Development"
Scratchapixel, Rasterization: [Practical implementation](https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/overview-rasterization-algorithm)
