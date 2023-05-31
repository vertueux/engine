<h1 align="center">Opticus</h1>

Opticus is a new multi-dimensional rendering engine, oriented towards virtual reality and mixed reality. Its goal is to succeed in creating a raytracing-like rendering, as well as to have a modular architecture, allowing to save storage on the user's computer. Note that for now, I am mainly focusing on building a renderer that can run through a window.

> History & background for context: I started developing game engines since I was 12 or 13 years old (as you can see with the [3D Rendering (3D Space)](https://github.com/vertueux/3D-Space) project, as an example. Unfortunately I wasted most of my time learning and not producing results (especially with the Unity Engine and game development since I was 12). This game engine is therefore the assembly of several of my old engines that I made before, either by source code or learning. 

## Installing Tools 
For now, Opticus has a few dependencies such as the [development kit for Windows](https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/), [LunarG's Vulkan software development kit](https://vulkan.lunarg.com/) and the [CMake build system](https://cmake.org/download/).
* Follow all instructions on the specific sites to install the dependencies.
## Clone the Project
You can clone and run this package by copying the command below :
```bash
git clone --recursive https://github.com/vertueux/opticus.git
```

## Build the Project
These commands should be able to build the project on any platform that CMake supports, otherwise follow the instructions for each platform from the [CMake website](https://cmake.org).
```bash
cmake --build
make 
```
![DISCORD](https://img.shields.io/badge/Contact%20me%20on%20Discord-now%239470-informational)