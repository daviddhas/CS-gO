#ifndef __IMAGE_H__
#define __IMAGE_H__
#define __DEBUG_GL_H__

/* ---- System Header for different Operating systems---- */
#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <stdio.h>
#include <stdarg.h>

typedef struct {
	long unsigned int sizeX, sizeY;
	unsigned char * data;
} Image;

int imageLoad(char *filename, Image *image);

#endif

