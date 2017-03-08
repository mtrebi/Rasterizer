# Introduction

In order to be able to understand how rendering work I decided to implement a forward/deferred renderer (based on my experience with OpenGL) in the CPU. The goal of this project is not to create a next generation renderer or an efficient CPU renderer. This project aims to understand how the rendering algorithms transforms a set of vertices that make up a 3D World into a 2D image of that World. I tried to be clear in my code to make it readable and easy to understand.

I've implement some basic features that I consider relevant for any graphics programmer to understand:
* Camera and Object transformations using 4x4 homogeneous matrices
* Affine and Perspective corrected mapping for textures
* Orthographic and Perspective camera
* Phong and Blinn-Phong shading given material phong coefficients
* Phong and Blinn-Phong shading given material diffuse and specular textures
* Normal mapping
* Simple optimizations
* A depth-buffer to solve the visibility surface problem
* Two rendering paths: Forward and deferred

# Rasterization

Checkout my blog posts about [rasterization](https://gamesandgraphicsdev.blogspot.com.es/2017/02/rasterization-i-overview.html) to understand step by step how it works.

# Features (in detail)

## Camera and Object transformations

I've implemented the most basic transformations: rotations and translations. To do so, I've used 4x4 homogeneous matrices. Homogeneous matrices are very useful to perform affine transformations because they can represent a linear transformation (rotation, scale, skew...) and a translation in a single matrix.

To implement rotations and translation, I've added to each object a __Model matrix__ that stores the local transformations for each object. Due to the multiplication properties of this matrices, multiple transformation can be concatenated.

The model transform is applied to each of the vertices when the rasterizer asks for the Geometry. It is performed only once and is the first transformation performed that converts the vertices from Object Local Space to World Space.

##  Object translations using 4x4 homogeneous matrices

In the following image each cube is rotated 45º in roll, pitch or yaw; and translated a small amount in the X axis:

```c
redCube->rotate(45, 0, 0);					// 45º in roll
redCube->translate(Vector3D(-250, 0, 0));	// Slighlty to the left

greenCube->rotate(0, 45, 0);				// 45º in pitch

blueCube->rotate(0, 0, 45);					// 45º in yaw
blueCube->translate(Vector3D(250, 0, 0));	// Slightly to the right
```

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/rotations_each_axis.bmp"> </p>

On the other hand, in the next image, the cube is rotated in all three euler angles: roll, pitch and yaw; and also translated:

```c
float roll = 45;
float pitch = 15;
float yaw = 30;
object->rotate(roll, pitch, yaw);		// Rotate using euler angles 45º roll, 15º pitch, 30º yaw
object->translate(Vector3D(10, 50, 20));	// Translate 10 units in X direction, 50 in Y and 20 in Z
```

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/rotations_all_axis.bmp"> </p>

## Orthographic and Perspective camera

I implemented the two most common camera modes:

* __Ortographic camera__: produces an orthograpic projection using parallel projectors. This means that all projection lines are orthogonal to the projection plane and parallel lines remains (there is no foreshortening). As we can see in the next image, all cubes have the same size (even that some of them are further than others) and parallel lines remains:

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/camera_orthograpic.bmp"> </p>

* __Perspectice camera__: produces a perspective projections using projectors to a center of projection or focal point. There's also a scaling factor that produces the foreshortening: closer objects seem bigger and further ones seem smaller. Parallel lines intersect.

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/camera_perspective.bmp"> </p>

## Phong and Blinn-Phong shading

I'm not going to talk about how Phong or Blinn-Phong works because you can find it in [blog](https://gamesandgraphicsdev.blogspot.com.es/2017/01/the-phong-lighting-model.html).

In the next image:
* The Red cube is using __Flat shading__. This is the simple flat color of the object without taking into account lights.
* The Green cube is using __Phong shading__.  We can see a huge difference with the flat shading because now we are able to see edges and this gives us this 3D feeling
* The Blue cube is using __Blinn-Phong shading__. The difference between Phong and Blinn-Phong is very subtle and is only really noticeable when the angle between the View direction and the Reflected vector is greater than 90º

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/flat_phong_blinn.bmp"> </p>

## Phong and Blinn-Phong shading using textures

Using textures is a simple modification in the program but it produces a huge quality increasement. The idea is to replace is basic color that we got previously by a color that we retrieve from a texture using __Texture Coordinates__. Texture coordinates are specifider per vertex (exaclty as colors are) and then, to get the color of a specific point in the triangle, an interpolation is performed across the vertices.

In my code I've used textures for the __diffuse and specular shading__ in the Phong and Blinn-Phong shading models. In the next image, all cubes use Blinn-Phong but:
* The red cube uses a flat color.
* The Box in the middle uses a diffuse texture for the color calculation.
* The Box on the right uses a diffuse and a specular texture for the color calculation. That makes the metalic borders of the box shinier. This looks much more realistic that the previous one.

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/flat_phong_blinn_textured.bmp"> </p>

## Normal mapping

The idea behind normal mapping is very similar to texture mapping but with a few differences. In texture mapping we used the texture to retrieve a color. In normal mapping, we use a texture to specify the direction of the normal vector instead. This provides a fine grained detail that produces realistic materials. The implementation is a little bit more complicated than diffuse/specular mapping because operations must be performed in something called __Tangent Space__ before getting the normal vector in World Space.

In the following image we can see:
* The Box on the left uses Blinn-Phong shading with diffuse and specular textures (as before). Quite good uh?
* The Box on the right uses Blinn-Phong shading with diffuse and specular textures BUT it also uses normal maps. It is very easy to see the differences. This box is more realistic, gives a sense of depth in the cracks and has some roughness. It doesn't look like a completely flat texture.

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/blinn_phong_textured_normal_map.bmp"> </p>

## Affine and Perspective corrected mapping for textures

As I said before, when mapping textures we have to calculate an interpolation from the values of the vertices of the triangle. There are different ways to do it. I've implemented two:
* __Affine mapping__. Is the cheapest way to perform texture mapping. However, it can produce wrong results if there is perspective distorsion (due to foreshortening). In the next image, the first texture is mapped correctly because is flat: the distance to the camera is constant in all points of the plane so there is no perspective distorsion. However, the second texture is mapped incorrectly:

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/texture_mapping_affine.bmp"> </p>

* __Perspective corrected mapping__. Solves the previous problem taking into account the distance of the triangle to the camera into the mapping formula producing better results:

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/texture_mapping_perspective.bmp"> </p>

## Simple optimizations

I've implemented some very common and simple optimizations to speed up the rendering process: 
* __Bounding box__ allow us to narrow the amount of pixels of the viewport that we have to iterate in order to color them. It is as simple as calculating the Bounding Box of the triangle in raster space and iterate that instead the whole screen. In the following image, in order to color the red triangle we iterated all the pixels inside the grey bounding box:

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/bbox_optimization.PNG"> </p>

* __View frustrum culling__ allows us to avoid rendering some parts of the scene that we know for sure that are not inside the view frustrum so we can discard them beforehand.

## Depth-buffering

When in a scene we have multiple objects overlapping in one single pixel, in order to calculate the color of the pixel, we must find which object is closer to the camera. The best way to do it is using a __depth buffer__. Very briefly, a depth-buffer is just a buffer that has the same size of the image and stores the distance between the camera and the object that has been redered last. This way, everytime we render we can compare the distance of the current object with the previous one and only render if the distance is smaller.

The next image is a render without depth-buffering. As you can see, there is an area where the two triangles overlap. Here, the decision of which triangle is shown is arbitrary. In this case, the blue triangle is further but it is displayed first.

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/render_no_depth_buffer.bmp"> </p>

On the other hand, the next image uses depth-buffering and thus, the red triangle is displayed first because it is closer to the camera.

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/render_depth_buffer.bmp"> </p>

If we take the depth buffer and we export it as a texture, it looks like in the next image. Black means that the object is close to the camera and white means that it is far. As we can see, the depth-color of the red triangle is darker than the blue triangle and thus it is closer and should be displayed first.

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/render_depth_buffer_depth_buffer.bmp"> </p>

The next image is a render without depth-buffering. As you can see, there is an area where the two triangles overlap. Here, the decision of which triangle is shown is arbitrary. In this case, the blue triangle is further but it is displayed first.

## Rendering paths

To render an image  we can use [RayTracing](https://github.com/mtrebi/Raytracer) or Rasterization. In the latter, depending on the order of how operations are performed we can talk about __Forward Rendering__ or __Deferred Rendering__. The result is always the same, the only thing that changes is the order of the operations.

*To read more about this, checkout the references, there is a very good article about forward and defered rendering*

### Forward rendering

This is the most common way of rendering and when we simply talk about rendering people usually mean forward rendering. The idea is that you set up the data in the GPU, project into the screen and split it into fragments or pixels and then you calculate the final color of each pixel. As you may guess, this process is called forward rendering because is linear and always goes forward.

This is the a complete scene rendered using forward rendering

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/forward_textured_scene.bmp"> </p>

And this is the resulting depth buffer

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/forward_textured_scene_depth.bmp"> </p>

### Deferred rendering

As opposed to forward rendering it exists deferred rendering. First of all, let's analyze what's the problem with Forward Rendering. The problem is that a pixel that has been shaded previously can be shaded again if an object that is closer to the camera is found. Shading is usually an expensive process because it may take into account multiple lights, indirect lighting, direct lighting, shadows and so on. For this reason, this is a waste of resources because we're shading each pixel many times since the order of how the geometry is evaluated is arbitrary. 

Deferred rendering solves this problem. The idea is that shading/lighting calculations are __deferred__ until the end. First of all, the visible surface is determined and only when this process has finished, the lighting calculations are being performed. This is very smart because shading is performed only when we know the geometry and this allows to do pixel shading is exactly once. This produces notably speed up in time execution but also increases the memory needed to render a scene. This happens because, along with the visible surface, we have to store also the other the properties used for lighting calculations: colors, specularity, normals and so on. Storing this may be quite expensive but it is usually worth.

To generate the same scene as before but using a deferred render we had to use additional buffers along with the depth buffer:

* Depth buffer: Same as before

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/deferred_textured_scene_depth.bmp"> </p>

* Diffuse buffer: Store diffuse colors of the geometry

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/deferred_textured_scene_diffuse.bmp"> </p>

* Specular buffer: Store specular colors of the geometry

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/deferred_textured_scene_specular.bmp"> </p>

* Normal buffer: Store normals vectors of the geometry

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/deferred_textured_scene_normals.bmp"> </p>

Then, to calculate shading we just have to combine all these different buffers and perform the calculation.

*As a side note, there is another interesting rendering algorithm usually used in hand-held devices called TBDF (Tile Based Deferred Rendering) that uses deferred rendering but, in order to reduce the memory needed, it splits up the screen in smaller tiles having the benefits of deferred rendering without the excessive memory usage*

# Gallery

These are just some samples. 

It all began here with the first render:

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/gallery/first_render.PNG"> </p>

And it end up here:

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/gallery/render_flat_scene_blinn_phong.bmp"> </p>

And here using textures:

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/readme/forward_textured_scene.bmp"> </p>

Triangle render with RGB color interpolation using barycentric coordinates

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/gallery/triangle_color_interpolation.PNG"> </p>

The same principle as before but applied to a Cube to create a color palette

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/gallery/cube_color_palette.PNG"> </p>

Checkout the rest of the images in the repository at [docs/images/gallery](https://github.com/mtrebi/Rasterizer/tree/master/docs/images/gallery).

## Cool images

I've found interesting to take pictures when things go *terribly wrong* for two reasons: First, because after you solved the problem, you can understand why the image looked like that. Second, because some images are pretty cool. These are just some of the *terribly wrong but cool images* 

This is my favorite one: I was trying to draw a square (two triangles) with a texture of black and white squares. However, the indices of the triangles were not corrected and I ended up with something like this:

<p align="center">  <img src="https://github.com/mtrebi/Rasterizer/blob/master/docs/images/gallery/cool_but_wrong/strange_things_6.bmp"> </p>

Checkout the rest of cool images at [docs/images/gallery/cool_but_wrong](https://github.com/mtrebi/Rasterizer/tree/master/docs/images/gallery/cool_but_wrong).

# Future work

* Shadow maps
* Use Quaternions for rotations to avoid gimbal lock
* Point lights with omnidirectional shadows (using cubemaps) and attenuation
* Alpha blending
* Sky boxes
* Model loading using .OBJ files
* Render to a window using some external library to achieve real time rendering (SFML)

# References

Fletcher Dunn, Ian Parberry: “3D Math Primer for Graphics and Game Development"

Scratchapixel, Rasterization: [Practical implementation](https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/overview-rasterization-algorithm)

Brent Owens, [Forward Rendering vs. Deferred Rendering](https://gamedevelopment.tutsplus.com/articles/forward-rendering-vs-deferred-rendering--gamedev-12342)
