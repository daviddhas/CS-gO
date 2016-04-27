
#ifdef _WIN32
#include <windows.h>
#endif

/* ---- System Header ---- */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* ---- User Header files ---- */
#include "types.h"


/**
 * Printing the vector
 */
void printVector (CGVector3D a)
{
    int i;
    printf("\nprintVector:\n");
    for (i=0;i<3;i++)
        printf("%.1f\n", a[i]);
    printf("\n");
}

/**
 * Conversion function,
 * Converts three coordinates in the corresponding vector to
 */
void toVector3D(CGVector3D vector, GLfloat x, GLfloat y, GLfloat z)
{
  vector[0] = x;
  vector[1] = y;
  vector[2] = z;
}

/**
 * Calculates the length of the vector
 */
float vectorLength3D(CGVector3D vector)
{
  return sqrt((vector[0]*vector[0])+
              (vector[1]*vector[1])+
              (vector[2]*vector[2]));
}

/*
  * Normalized a vector
 */
void normVector3D(CGVector3D vector)
{
  float l = vectorLength3D(vector);
  if (l != .0f)
    toVector3D(vector, vector[0]/l, vector[1]/l, vector[2]/l);
}

/**
 * Calculates the cross product of two vectors
 */
void crossProduct3D(CGVector3D product, CGVector3D a, CGVector3D b)
{
  toVector3D(product, (a[1]*b[2] - a[2]*b[1]),
                      (a[2]*b[0] - a[0]*b[2]),
                      (a[0]*b[1] - a[1]*b[0]));
}


double multiplyVectorVector (CGVector3D a, CGVector3D b)
{
    int i;
    double res = 0.0;
    for (i=0;i<3;i++)
        res += a[i]*b[i];
    return res;
}

void multiplyVectorScalar (CGVector3D a, double s, CGVector3D * res)
{
    int i;
    for (i=0;i<3;i++)
        (*res)[i] = a[i]*s;
}

double scalarProduct (CGVector3D a, CGVector3D b)
{
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

void subtractVectorVector (CGVector3D a, CGVector3D b, CGVector3D * res)
{
    int i;
    for (i=0;i<3;i++)
        (*res)[i] = a[i] - b[i];
}

void divideVectorScalar (CGVector3D a, double s, CGVector3D * res)
{
    int i;
    for (i=0;i<3;i++)
        (*res)[i] = a[i] / s;
}

void addVectorVector (CGVector3D a, CGVector3D b, CGVector3D * res)
{
    int i;
    for (i=0;i<3;i++)
        (*res)[i] = a[i] + b[i];
}

double degToRad (double deg)
{
    return deg*PI/180.0;
}

double radToDeg (double rad)
{
    return rad*180.0/PI;
}

double angleVectorVector (CGVector3D a, CGVector3D b)
{
    return radToDeg (acos (multiplyVectorVector (a, b) / (vectorLength3D(a)*vectorLength3D(b))));
}
















