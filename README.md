CS Go
Fast, portable GPU programming backed by OpenGL Compute Shaders

Project Overview

The Problem
GPU programming platforms such as CUDA and OpenCL tend to have very inconsistent
or no support between graphics cards from different vendors. OpenGL Compute
Shaders are better about this, but require a lot of boilerplate code to link C++
to the shader language, GLSL.

Our Solution
We want to create a C++ library for GPU programming that generates GLSL in the
backend. The user would create a program context, perform all the operations
they want, and close the context compile the GLSL and read the results.

The Metrics
Generated code should be as efficient as code written in native GLSL. The higher
the percentage of GLSL features we could support, the better. We would also like
to minimize compilation overhead.

The Dependencies
We will depend on OpenGL 4.3, when Compute Shaders became part of the core
library.
