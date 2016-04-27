#ifndef __TYPES_H__
#define __TYPES_H__

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

/**
 * PHYSICS!
 */
#define PARTICLE_COUNT	6000000
#define RAND_COUNT		(PARTICLE_COUNT*100)
#define ATTRACTOR_COUNT	8



#define GROUND_HEIGHT	0.3

#define CAMERA_X        -50.1
#define CAMERA_Y        50.0
#define CAMERA_Z        75.0
#define CAMERA_SPEED    15.0

#define CAMERA_MOVEMENT_SPEED	4.0
#define CAMERA_ZOOM_SPEED 10.0

#define WORLD_SIZE 150

#define E			2.71828183
#define PI             3.14159265  
#define EPS		0.0001

/** Number of calls to the timer function per second */
#define TIMER_CALLS_PS      1920

#define RED                     0.7, 0.0, 0.0
#define BLUE                    0.0, 0.0, 0.7
#define GREEN                   0.0, 0.7, 0.0
#define BLACK                   0.0, 0.0, 0.0
#define WHITE                   1.0, 1.0, 1.0
#define GREY                    0.4, 0.4, 0.4 
#define YELLOW                  0.7, 0.7, 0.0

#define ESC     27

#define SPACE   32


enum e_MouseInterpretType
{ NONE, MOVE, ZOOM};

typedef enum e_MouseInterpretType MouseInterpretType;

/** Point in 3D space (homogeneous coordinates) */
typedef GLfloat CGPoint4f[4];
typedef GLfloat CGPoint3f[3];
typedef CGPoint3f CGColor;

/** Data type for a vector */
typedef double Vector4D[4];
typedef Vector4D Punkt4D;

/** Vector in 3D space*/
typedef GLfloat CGVector3D[3];

typedef int Movement[3];

typedef struct {
	GLfloat x,y,z,w;
} Vec4;

typedef struct {
	GLfloat x,y,z;
} Vec3;

typedef Vec4 Attractor[ATTRACTOR_COUNT]; /* xyz = Position, w = Mass */

typedef float AttractorMass[ATTRACTOR_COUNT];

#endif
