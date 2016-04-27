
/* ---- System Headers ---- */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#include <GLFW/glfw3.h>

/* ---- User Headers ---- */
#include "io.h"
#include "scene.h" 
#include "types.h"

/**
 * Error-Callback-Function
 */
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

int main (int argc, char **argv)
{
	srand (time (0));
	
	glfwSetErrorCallback(error_callback);

	
	if (!initAndStartIO ("Lots and Lots of Particles ..YAY ... :-)", 1920, 1080))
	{
		fprintf (stderr, "Initialization failed!\n");
		glfwTerminate();
		return 1;
	} 
	
	glfwTerminate();
	
	return 0;
}
