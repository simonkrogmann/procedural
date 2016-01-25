# procedural [![Build Status](https://travis-ci.org/simonkrogmann/procedural.svg?branch=master)](https://travis-ci.org/simonkrogmann/procedural)
A lbrary of procedural textures written in glsl and a viewer to display them.

##Library

##Viewer
###Dependencies:
* [utilgpu](https://github.com/simonkrogmann/utilgpu) (Sublibraries: cpp, gl, qt)
* [glbinding](https://github.com/cginternals/glbinding)
* Qt5

###Usage
The viewer can be started with either a project file (.glsl-project) or a fragment shader (.frag):

`./procedural-viewer <file> [options]`

Key | Action
--- | ---
 S  | screenshot (using offscreen rendering, the framebuffers of the other stages are also saved to files)
 R  | reload shaders
 F  | toggle frame time display

Shaders and textures will also automatically be reloaded on file changes.

###Project Files
A project file consists of internal includes (from the library), your own includes, textures and stages, each of which should include a main function. All stages are rendered to textures, except the last stage, which is rendered to the default framebuffer.
Here is a sample project file:
```
internal-includes:
    util
    sphere
    lighting
external-includes:
    settings: settings.frag
textures:
    normals: normals.png
    depth: depth.png
stages:
    base: image.frag
    final: blur.frag
```
###Accessible Variables
The textures and the results of all previous stages are accessible (as `uniform sampler2D` using the format GL_RGBA8)  by the names given to them in the project file. Additionally the following variables can be used:

* `in vec2 position`
* `out vec4 color`
* `uniform ivec2 windowSize`
* `uniform float time` (in seconds)
