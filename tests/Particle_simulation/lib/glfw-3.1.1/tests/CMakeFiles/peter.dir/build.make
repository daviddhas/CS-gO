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
include lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/depend.make

# Include the progress variables for this target.
include lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/progress.make

# Include the compile flags for this target's objects.
include lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/flags.make

lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/peter.c.o: lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/flags.make
lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/peter.c.o: lib/glfw-3.1.1/tests/peter.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/peter.c.o"
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/peter.dir/peter.c.o   -c /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests/peter.c

lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/peter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/peter.dir/peter.c.i"
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests/peter.c > CMakeFiles/peter.dir/peter.c.i

lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/peter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/peter.dir/peter.c.s"
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests/peter.c -o CMakeFiles/peter.dir/peter.c.s

lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/peter.c.o.requires:
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/peter.c.o.requires

lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/peter.c.o.provides: lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/peter.c.o.requires
	$(MAKE) -f lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/build.make lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/peter.c.o.provides.build
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/peter.c.o.provides

lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/peter.c.o.provides.build: lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/peter.c.o

# Object files for target peter
peter_OBJECTS = \
"CMakeFiles/peter.dir/peter.c.o"

# External object files for target peter
peter_EXTERNAL_OBJECTS =

lib/glfw-3.1.1/tests/bin/peter: lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/peter.c.o
lib/glfw-3.1.1/tests/bin/peter: lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/build.make
lib/glfw-3.1.1/tests/bin/peter: lib/glfw-3.1.1/src/libglfw3.a
lib/glfw-3.1.1/tests/bin/peter: /usr/lib/x86_64-linux-gnu/libX11.so
lib/glfw-3.1.1/tests/bin/peter: /usr/lib/x86_64-linux-gnu/libXrandr.so
lib/glfw-3.1.1/tests/bin/peter: /usr/lib/x86_64-linux-gnu/libXinerama.so
lib/glfw-3.1.1/tests/bin/peter: /usr/lib/x86_64-linux-gnu/libXi.so
lib/glfw-3.1.1/tests/bin/peter: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
lib/glfw-3.1.1/tests/bin/peter: /usr/lib/x86_64-linux-gnu/librt.so
lib/glfw-3.1.1/tests/bin/peter: /usr/lib/x86_64-linux-gnu/libm.so
lib/glfw-3.1.1/tests/bin/peter: /usr/lib/x86_64-linux-gnu/libXcursor.so
lib/glfw-3.1.1/tests/bin/peter: /usr/lib/x86_64-linux-gnu/libGL.so
lib/glfw-3.1.1/tests/bin/peter: lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable bin/peter"
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/peter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/build: lib/glfw-3.1.1/tests/bin/peter
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/build

lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/requires: lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/peter.c.o.requires
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/requires

lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/clean:
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests && $(CMAKE_COMMAND) -P CMakeFiles/peter.dir/cmake_clean.cmake
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/clean

lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/depend:
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/peter.dir/depend

