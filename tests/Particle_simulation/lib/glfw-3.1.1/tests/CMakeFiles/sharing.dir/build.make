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
include lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/depend.make

# Include the progress variables for this target.
include lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/progress.make

# Include the compile flags for this target's objects.
include lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/flags.make

lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/sharing.c.o: lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/flags.make
lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/sharing.c.o: lib/glfw-3.1.1/tests/sharing.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/sharing.c.o"
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/sharing.dir/sharing.c.o   -c /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests/sharing.c

lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/sharing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sharing.dir/sharing.c.i"
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests/sharing.c > CMakeFiles/sharing.dir/sharing.c.i

lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/sharing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sharing.dir/sharing.c.s"
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests/sharing.c -o CMakeFiles/sharing.dir/sharing.c.s

lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/sharing.c.o.requires:
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/sharing.c.o.requires

lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/sharing.c.o.provides: lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/sharing.c.o.requires
	$(MAKE) -f lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/build.make lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/sharing.c.o.provides.build
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/sharing.c.o.provides

lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/sharing.c.o.provides.build: lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/sharing.c.o

# Object files for target sharing
sharing_OBJECTS = \
"CMakeFiles/sharing.dir/sharing.c.o"

# External object files for target sharing
sharing_EXTERNAL_OBJECTS =

lib/glfw-3.1.1/tests/bin/sharing: lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/sharing.c.o
lib/glfw-3.1.1/tests/bin/sharing: lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/build.make
lib/glfw-3.1.1/tests/bin/sharing: lib/glfw-3.1.1/src/libglfw3.a
lib/glfw-3.1.1/tests/bin/sharing: /usr/lib/x86_64-linux-gnu/libX11.so
lib/glfw-3.1.1/tests/bin/sharing: /usr/lib/x86_64-linux-gnu/libXrandr.so
lib/glfw-3.1.1/tests/bin/sharing: /usr/lib/x86_64-linux-gnu/libXinerama.so
lib/glfw-3.1.1/tests/bin/sharing: /usr/lib/x86_64-linux-gnu/libXi.so
lib/glfw-3.1.1/tests/bin/sharing: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
lib/glfw-3.1.1/tests/bin/sharing: /usr/lib/x86_64-linux-gnu/librt.so
lib/glfw-3.1.1/tests/bin/sharing: /usr/lib/x86_64-linux-gnu/libm.so
lib/glfw-3.1.1/tests/bin/sharing: /usr/lib/x86_64-linux-gnu/libXcursor.so
lib/glfw-3.1.1/tests/bin/sharing: /usr/lib/x86_64-linux-gnu/libGL.so
lib/glfw-3.1.1/tests/bin/sharing: lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable bin/sharing"
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sharing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/build: lib/glfw-3.1.1/tests/bin/sharing
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/build

lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/requires: lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/sharing.c.o.requires
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/requires

lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/clean:
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests && $(CMAKE_COMMAND) -P CMakeFiles/sharing.dir/cmake_clean.cmake
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/clean

lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/depend:
	cd /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests /home/david/Desktop/Computeshaders/Partikel_accelleration_on_GPU/lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/glfw-3.1.1/tests/CMakeFiles/sharing.dir/depend

