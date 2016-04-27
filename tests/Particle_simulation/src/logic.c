
/* ---- System Headers ---- */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


/* ----  Headers---- */
#include "logic.h"
#include "vector.h"
#include "scene.h"
#include "types.h"

/** Mouse zoom/move/none */
MouseInterpretType G_Mouse;
/** Camera position */
CGVector3D G_CameraPosition = {CAMERA_X,CAMERA_Y,CAMERA_Z};
/** Mouse Position  */
Movement G_MouseMove = {0.0,0.0,0.0};
/** Starting point of the mouse movement*/
CGVector3D G_LastMouseCenter = {0.0,0.0,0.0};

/** Add particles? */
int G_UpDownKeys[2] = {0,0};
/** FPS */
int G_FPS = 0;
/** FPS counter */
double G_Counter = 0.0-EPS;

/* ------- GETTER / SETTER ------- */

int getFPS(void)
{
	return G_FPS;
}
double getCameraPosition (int axis)
{
    if (axis >= 0 && axis < 3)
        return G_CameraPosition[axis];
        
    return 0.0;
}

/**
 * Moves the camera on a spherical radius around the center of scenes.
 */
void setCameraMovement(int x,int y)
{
	CGVector3D tmp;
	double factor, radius = vectorLength3D(G_CameraPosition);
	
	tmp[0] = G_CameraPosition[0];
	tmp[1] = G_CameraPosition[1];
	tmp[2] = G_CameraPosition[2];
	
	G_MouseMove[0] = x-G_LastMouseCenter[0];
	G_MouseMove[2] = y-G_LastMouseCenter[2];
	
	G_LastMouseCenter[0] = x;
	G_LastMouseCenter[2] = y;
	
	/* Movement around the Y axis: */
	G_CameraPosition[0] = cos(-G_MouseMove[0]*PI/180.0/CAMERA_MOVEMENT_SPEED)*tmp[0] + sin(-G_MouseMove[0]*PI/180.0/CAMERA_MOVEMENT_SPEED)*tmp[2];
	G_CameraPosition[2] = -sin(-G_MouseMove[0]*PI/180.0/CAMERA_MOVEMENT_SPEED)*tmp[0] + cos(-G_MouseMove[0]*PI/180.0/CAMERA_MOVEMENT_SPEED)*tmp[2];
	
	/* BMoving up / down */
	G_CameraPosition[1] += G_MouseMove[2]/(CAMERA_MOVEMENT_SPEED/2)*(vectorLength3D(G_CameraPosition)/100.0);
	factor = 1.0 / (vectorLength3D(G_CameraPosition) / radius);
	multiplyVectorScalar (G_CameraPosition, factor, &G_CameraPosition);
		
}

/**
 * Extends / shortening the vector to the camera.
 */
void setCameraZoom(int x,int y)
{
	double factor = 1.0 + (CAMERA_ZOOM_SPEED / 1000.0) * ((G_MouseMove[2] < 0.0) ? -1.0 : 1.0);
	
	G_MouseMove[0] = x-G_LastMouseCenter[0];
	G_MouseMove[2] = y-G_LastMouseCenter[2];
	
	G_LastMouseCenter[0] = x;
	G_LastMouseCenter[2] = y;
	
	G_CameraPosition[0] *= factor;
	G_CameraPosition[1] *= factor;
	G_CameraPosition[2] *= factor;
}

/* ------- CALCULATIONS ------- */

/* Calculates all the functions that are dependent on the interval */
void calcTimeRelatedStuff (double interval)
{
    G_Counter += interval;
    
    if (G_Counter >= 1.0)
		G_Counter = 0.0 -EPS;
    
    if (G_Counter <= 0.0)
		G_FPS = (int) 1.0/interval;
}

/* ------- INIT ------- */

/**
 * Initializes the camera
 */
void initCameraPosition ()
{
    G_CameraPosition[0] = CAMERA_X;
    G_CameraPosition[1] = CAMERA_Y;
    G_CameraPosition[2] = CAMERA_Z;
}

/**
 * Here is the complete initialization of the entire game takes place.
 * Includes data management 
 */
void initGame ()
{   
    initCameraPosition();
    /*setRandomize();*/
}

