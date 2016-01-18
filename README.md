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
###Project Files
A project file consists of internal includes (from the library), your own includes, textures and a main shader, which should contain a main function.
Sample project file:
```
internal-includes:
    - util
    - sphere
    - lighting
external-includes:
    settings: settings.frag
textures:
    normals: normals.png
    depth: depth.png
main: main.frag
```
###Accessible Uniforms
The textures are accessible by the names given to them in the project file. Additionally the following variables can be used:
* ivec2 windowSize
* float time (in seconds)
