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
include lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/depend.make

# Include the progress variables for this target.
include lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/progress.make

# Include the compile flags for this target's objects.
include lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/flags.make

lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/defaults.c.o: lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/flags.make
lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/defaults.c.o: lib/glfw-3.1.1/tests/defaults.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/defaults.c.o"
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/defaults.dir/defaults.c.o   -c /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests/defaults.c

lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/defaults.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/defaults.dir/defaults.c.i"
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests/defaults.c > CMakeFiles/defaults.dir/defaults.c.i

lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/defaults.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/defaults.dir/defaults.c.s"
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests/defaults.c -o CMakeFiles/defaults.dir/defaults.c.s

lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/defaults.c.o.requires:
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/defaults.c.o.requires

lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/defaults.c.o.provides: lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/defaults.c.o.requires
	$(MAKE) -f lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/build.make lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/defaults.c.o.provides.build
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/defaults.c.o.provides

lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/defaults.c.o.provides.build: lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/defaults.c.o

# Object files for target defaults
defaults_OBJECTS = \
"CMakeFiles/defaults.dir/defaults.c.o"

# External object files for target defaults
defaults_EXTERNAL_OBJECTS =

lib/glfw-3.1.1/tests/bin/defaults: lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/defaults.c.o
lib/glfw-3.1.1/tests/bin/defaults: lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/build.make
lib/glfw-3.1.1/tests/bin/defaults: lib/glfw-3.1.1/src/libglfw3.a
lib/glfw-3.1.1/tests/bin/defaults: /usr/lib/x86_64-linux-gnu/libX11.so
lib/glfw-3.1.1/tests/bin/defaults: /usr/lib/x86_64-linux-gnu/libXrandr.so
lib/glfw-3.1.1/tests/bin/defaults: /usr/lib/x86_64-linux-gnu/libXinerama.so
lib/glfw-3.1.1/tests/bin/defaults: /usr/lib/x86_64-linux-gnu/libXi.so
lib/glfw-3.1.1/tests/bin/defaults: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
lib/glfw-3.1.1/tests/bin/defaults: /usr/lib/x86_64-linux-gnu/librt.so
lib/glfw-3.1.1/tests/bin/defaults: /usr/lib/x86_64-linux-gnu/libm.so
lib/glfw-3.1.1/tests/bin/defaults: /usr/lib/x86_64-linux-gnu/libXcursor.so
lib/glfw-3.1.1/tests/bin/defaults: /usr/lib/x86_64-linux-gnu/libGL.so
lib/glfw-3.1.1/tests/bin/defaults: lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable bin/defaults"
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/defaults.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/build: lib/glfw-3.1.1/tests/bin/defaults
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/build

lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/requires: lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/defaults.c.o.requires
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/requires

lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/clean:
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests && $(CMAKE_COMMAND) -P CMakeFiles/defaults.dir/cmake_clean.cmake
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/clean

lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/depend:
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/defaults.dir/depend

