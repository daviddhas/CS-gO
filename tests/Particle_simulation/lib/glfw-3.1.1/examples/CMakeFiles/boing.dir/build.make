# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU

# Include any dependencies generated for this target.
include lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/depend.make

# Include the progress variables for this target.
include lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/progress.make

# Include the compile flags for this target's objects.
include lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/flags.make

lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/boing.c.o: lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/flags.make
lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/boing.c.o: lib/glfw-3.1.1/examples/boing.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/boing.c.o"
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/examples && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/boing.dir/boing.c.o   -c /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/examples/boing.c

lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/boing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/boing.dir/boing.c.i"
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/examples && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/examples/boing.c > CMakeFiles/boing.dir/boing.c.i

lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/boing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/boing.dir/boing.c.s"
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/examples && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/examples/boing.c -o CMakeFiles/boing.dir/boing.c.s

lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/boing.c.o.requires:
.PHONY : lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/boing.c.o.requires

lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/boing.c.o.provides: lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/boing.c.o.requires
	$(MAKE) -f lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/build.make lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/boing.c.o.provides.build
.PHONY : lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/boing.c.o.provides

lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/boing.c.o.provides.build: lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/boing.c.o

# Object files for target boing
boing_OBJECTS = \
"CMakeFiles/boing.dir/boing.c.o"

# External object files for target boing
boing_EXTERNAL_OBJECTS =

lib/glfw-3.1.1/examples/bin/boing: lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/boing.c.o
lib/glfw-3.1.1/examples/bin/boing: lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/build.make
lib/glfw-3.1.1/examples/bin/boing: lib/glfw-3.1.1/src/libglfw3.a
lib/glfw-3.1.1/examples/bin/boing: /usr/lib/x86_64-linux-gnu/libGLU.so
lib/glfw-3.1.1/examples/bin/boing: /usr/lib/x86_64-linux-gnu/libX11.so
lib/glfw-3.1.1/examples/bin/boing: /usr/lib/x86_64-linux-gnu/libXrandr.so
lib/glfw-3.1.1/examples/bin/boing: /usr/lib/x86_64-linux-gnu/libXinerama.so
lib/glfw-3.1.1/examples/bin/boing: /usr/lib/x86_64-linux-gnu/libXi.so
lib/glfw-3.1.1/examples/bin/boing: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
lib/glfw-3.1.1/examples/bin/boing: /usr/lib/x86_64-linux-gnu/librt.so
lib/glfw-3.1.1/examples/bin/boing: /usr/lib/x86_64-linux-gnu/libm.so
lib/glfw-3.1.1/examples/bin/boing: /usr/lib/x86_64-linux-gnu/libXcursor.so
lib/glfw-3.1.1/examples/bin/boing: /usr/lib/x86_64-linux-gnu/libGL.so
lib/glfw-3.1.1/examples/bin/boing: lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable bin/boing"
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/boing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/build: lib/glfw-3.1.1/examples/bin/boing
.PHONY : lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/build

lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/requires: lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/boing.c.o.requires
.PHONY : lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/requires

lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/clean:
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/examples && $(CMAKE_COMMAND) -P CMakeFiles/boing.dir/cmake_clean.cmake
.PHONY : lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/clean

lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/depend:
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/examples /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/examples /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/glfw-3.1.1/examples/CMakeFiles/boing.dir/depend
