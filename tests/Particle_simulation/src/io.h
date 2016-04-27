#ifndef __IO_H__
#define __IO_H__
#define __DEBUG_GL_H__

#include <stdio.h>
#include <stdarg.h>

int initAndStartIO (char *title, int width, int height);

void mainLoop (GLFWwindow * window);

#endif
