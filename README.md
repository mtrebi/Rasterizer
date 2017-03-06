# IN PROGRESS

# Introduction

In order to be able to understand how rendering work I decided to implement a forward/deferred renderer (based on my experience with OpenGL) in the CPU. The goal of this project is not to create a next generation renderer or a super efficient CPU renderer. This project is just to understand how the rendering algorithms transforms a set of vertices that make up a 3D World into a 2D image of that World. I tried to be clear in my code to make it readable and easy to understand.

I've implement some basic features that I consider relevant for any graphics programmer to understand:
* Camera and Object transformations using 4x4 homogeneous matrices
* Affine and Perspective corrected mapping for textures
* Orthographic and Perspective camera
* Phong and Blinn-Phong shading given material phong coefficients
* Phong and Blinn-Phong shading given material diffuse and specular textures
* Normal mapping
* Simple optimizations


* A depth-buffer to solve the visibility surface problem

* A forward and a deferred version of the renderer



## Features

### Camera and Object transformations

I've implemented the most basic transformations: rotations and translations. To do so, I've used 4x4 homogeneous matrices. Homogeneous matrices are very useful to perform affine transformations because they can represent a linear transformation (rotation, scale, skew...) and a translation in a single matrix.

To implement rotations and translation, I've added to each object a _Model matrix_ that stores the local transformations for each object. Due to the multiplication properties of this matrices, multiple transformation can be concatenated.

The model transform is applied to each of the vertices when the rasterizer asks for the Geometry. It is performed only once and is the first transformation performed that converts the vertices from Object Local Space to World Space.

###  Object translations using 4x4 homogeneous matrices

In the following image each cube is rotated 45º in roll, pitch or yaw; and translated a small amount in the X axis:

```c
redCube->rotate(45, 0, 0);					// 45º in roll
redCube->translate(Vector3D(-250, 0, 0));	// Slighlty to the left

greenCube->rotate(0, 45, 0);				// 45º in pitch

blueCube->rotate(0, 0, 45);					// 45º in yaw
blueCube->translate(Vector3D(250, 0, 0));	// Slightly to the right
```

![Rotations in each axis](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/rotations_each_axis.bmp "Rotations in each axis")


On the other hand, in the next image, the cube is rotated in all three euler angles: roll, pitch and yaw; and also translated:

```c
float roll = 45;
float pitch = 15;
float yaw = 30;
object->rotate(roll, pitch, yaw);		// Rotate using euler angles 45º roll, 15º pitch, 30º yaw
object->translate(Vector3D(10, 50, 20));	// Translate 10 units in X direction, 50 in Y and 20 in Z
```

![Rotations in all axis](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/rotations_all_axis.bmp "Rotations in all axis")


### Orthographic and Perspective camera

I implemented the two most common camera modes:

* _Ortographic camera_: produces an orthograpic projection using parallel projectors. This means that all projection lines are orthogonal to the projection plane and parallel lines remains (there is no foreshortening). As we can see in the next image, all cubes have the same size (even that some of them are further than others) and parallel lines remains:

![Render using an orthograpic camera](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/render_camera_orthograpic.bmp "Render using an orthograpic camera")


* _Perspectice camera_: produces a perspective projections using projectors to a center of projection or focal point. There's also a scaling factor that produces the foreshortening: closer objects seem bigger and further ones seem smaller. Parallel lines intersect.

![Render using a perspective camera](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/render_camera_perspective.bmp "Render using a perspective camera")

### Phong and Blinn-Phong shading

I'm not going to talk about how Phong or Blinn-Phong works because you can find it in [blog](https://gamesandgraphicsdev.blogspot.com.es/2017/01/the-phong-lighting-model.html).

In the next image:
* The Red cube is using _Flat shading_. This is the simple flat color of the object without taking into account lights.
* The Green cube is using _Phong shading.  We can see a huge difference with the flat shading because now we are able to see edges and this gives us this 3D feeling
* The Blue cube is using _Blinn-Phong shading. The difference between Phong and Blinn-Phong is very subtle and is only really noticeable when the angle between the View direction and the Reflected vector is greater than 90º

![Cubes with different shading](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/flat_phong_blinn.bmp "Cubes with different shading")

### Phong and Blinn-Phong shading using textures

Using textures is a simple modification in the program but it produces a huge quality increasement. The idea is to replace is basic color that we got previously by a color that we retrieve from a texture using _Texture Coordinates_. Texture coordinates are specifider per vertex (exaclty as colors are) and then, to get the color of a specific point in the triangle, an interpolation is performed across the vertices.

In my code I've used textures for the _diffuse and specular shading_. In the next image:
* The red cube uses flat shading
* The Box in the middle uses only a diffuse texture.
* The Box on the right uses a diffuse and a specular texture that makes the metalic borders of the box shinier. This looks much more realistic that the previous one

![Cubes with Blinn-Phong shading and textures](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/flat_phong_blinn_textured.bmp "Cubes with Blinn-Phong shading and textures")


### Normal mapping

The idea behind normal mapping is very similar to texture mapping but with a few differences. In texture mapping we used the texture to retrieve a color. In normal mapping, we use a texture to specify the direction of the normal vector instead. This provides a fine grained detail that produces realistic materials. The implementation is a little bit more complicated than diffuse/specular mapping because operations must be performed in something called _Tangent Space_ before getting the normal vector in World Space.

In the following image we can see:
* The Box on the left uses Blinn-Phong shading with diffuse and specular textures (as before). Quite good uh?
* The Box on the right uses Blinn-Phong shading with diffuse and specular textures BUT it also uses normal maps. It is very easy to see the differences. This box is more realistic, gives a sense of depth in the cracks and has some roughness. It doesn't look like a completely flat texture.

![Blinn-Phong shading and normal mapping](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/blinn_phong_textured_normal_map.bmp "Blinn-Phong shading and normal mapping")

### Affine and Perspective corrected mapping for textures

As I said before, when mapping textures we have to calculate an interpolation from the values of the vertices of the triangle. There are different ways to do it. I've implemented two:
* _Affine mapping_. Is the cheapest way to perform texture mapping. However, it can produce wrong results if there is perspective distorsion (due to foreshortening). In the next image, the first texture is mapped correctly because is flat: the distance to the camera is constant in all points of the plane so there is no persective distorsion. However, the second texture is notably mapped incorrectly.

![Affine texture mapping](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/texture_mapping_affine.bmp "Affine texture mapping")

* _Perspective corrected mapping_. Solves the previous problem taking into account the distance of the triangle to the camera into the mapping formula producing better results:

![Perspective corrected texture mapping](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/texture_mapping_perspective.bmp "Perspective corrected texture mapping")


### Simple optimizations

I've implemented some very common and simple optimizations to speed up the rendering process: 
* _Bounding box_ allow us to narrow the amount of pixels of the viewport that we have to iterate in order to color them. It is as simple as calculating the Bounding Box of the triangle in raster space and iterate that instead the whole screen. In the following image, in order to color the red triangle we iterated all the pixels inside the grey bounding box:

![Bounding Box optimization](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/bbox_optimization.bmp "Bounding Box optimization")


* _View frustrum culling_ allow us to avoid rendering some parts of the scene that we know for sure that are not inside the view frustrum so we can discard them beforehand.






### Depth-buffering

Render to depth buffer image

# Forward and deferred







# Rasterization

Checkout my blog posts about [rasterization](https://gamesandgraphicsdev.blogspot.com.es/2017/02/rasterization-i-overview.html) to understand step by step how it works.

# Gallery

These are only some images generated with this renderer.

This is the first image that I generated. Just a flat triangle. It may seem super simple but it was the start of this renderer. When it worked, I was really really happy.


![First triangle render](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/first_render.bmp "First triangle render")


This is the final render of a flat scene using Blinn-Phong shading:

![Flat scene render using blinn phong](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/render_flat_scene_blinn_phong.bmp "Flat scene render using blinn phong")


And this is the final render of a textured scene also using Blinn-Phong:

![Textured scene render using blinn phong](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/render_textured_scene_blinn_phong.bmp "Textured scene render using blinn phong")

Checkout the rest of the images at docs/images/gallery.

## Cool images

I've found interesting to take pictures when things go *terribly wrong* for two reasons: First, because after you solved the problem, you can understand why the image looked like that. Second, because some images are pretty cool. These are just some of the *terribly wrong but cool images* 

This is my favorite one: I was trying to draw a square (two triangles) with a texture of black and white squares. However, the indices of the triangles were not corrected and I ended up with something like this:

![Cool square with wrong indices](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/strange_things_6.bmp "Cool square with wrong indices")

In the following case, all pixels of the screen were shaded using some wrong calculation and the result was really cool:

![Cool image with wrong shading](https://github.com/mtrebi/Rasterizer/blob/master/docs/images/strange_things_2.bmp "Cool image with wrong shading")

Checkout the rest of cool images at docs/images with the suffix strange.


# Future work
* Shadow maps
* Point lights with omnidirectional shadows (using cubemaps) and attenuation
* Alpha blending
* Sky boxes
* .OBJ files model loading
* Render to a window using some external library to achieve real time rendering (SFML)

# References

Fletcher Dunn, Ian Parberry: “3D Math Primer for Graphics and Game Development"
Scratchapixel, Rasterization: [Practical implementation](https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/overview-rasterization-algorithm)

