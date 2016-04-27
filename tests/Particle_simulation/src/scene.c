#ifdef _WIN32
#include <windows.h>
#endif

/* ---- System Header files ---- */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

/* ---- User Headers ---- */
#include "scene.h"
#include "logic.h"
#include "types.h"
#include "vector.h"

/*
 * Sets Global color
 */
void setColor (float color1, float color2, float color3, float alpha, float shininess, int emission)
{
    float tmp[] = {0.0, 0.0, 0.0};
    tmp[0] = color1;
    tmp[1] = color2;
    tmp[2] = color3;

    {
        /* Material */
        float matAmbient[] = {0.0, 0.0, 0.0, 0.0};
        float matBlack[]= {0.0, 0.0, 0.0, 0.0};
        float matDiffuse[] = {0.0, 0.0, 0.0, 0.0};
        float matSpecular[] = {0.0, 0.0, 0.0, 0.0};
        float matShininess[] = { 0.0 };

        matShininess[0] = shininess;

        matAmbient[0] = tmp[0];
        matAmbient[1] = tmp[1];
        matAmbient[2] = tmp[2];
        matAmbient[3] = alpha;

        matSpecular[0] = tmp[0];
        matSpecular[1] = tmp[1];
        matSpecular[2] = tmp[2];
        matSpecular[3] = alpha;

        matDiffuse[0] = tmp[0] - 0.7;
        matDiffuse[1] = tmp[1] - 0.7;
        matDiffuse[2] = tmp[2] - 0.7;
        matDiffuse[3] = alpha;

        /* Assigning Material-Parameter */
        glMaterialfv (GL_FRONT, GL_AMBIENT, matAmbient);
        glMaterialfv (GL_FRONT, GL_DIFFUSE, matDiffuse);
        glMaterialfv (GL_FRONT, GL_SPECULAR, matSpecular);
        glMaterialfv (GL_FRONT, GL_SHININESS, matShininess);
        if (emission)
            glMaterialfv (GL_FRONT, GL_EMISSION, matSpecular);
        else
            glMaterialfv (GL_FRONT, GL_EMISSION, matBlack);
    }
}

void drawFPS (void)
{
    /*GLfloat textColor[3] = { 1.0f, 1.0f, 1.0f };
    char * string = calloc ((strlen ("FPS = ") + 4), sizeof(char));
    sprintf(string, "FPS = %d", getFPS());

    drawString (0.6, 0.1, textColor, string);

    free (string);*/
}


/**
 * Initialization of the light sources.
  * Sets properties of light sources (color, opening angle, ...)
 */
static void initLight (void)
{

    /* Color of the second light source */
    CGPoint4f lightColor1[3] =
    { {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f,
                                                           1.0f}
    };

    /* Color of the first light source */
    CGPoint4f lightColor2[3] =
    { {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f,
                                                           1.0f}
    };

    /* Opening angle of the second light source */
    GLdouble lightCutoff1 = 90.0f;
    /* Light distribution in the light beam of the second light source */
    GLdouble lightExponent1 = 20.0f;

    float globalAmbientLight[] = {0.3, 0.3, 0.3, 1.0};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);

    /* Set color of the second light source */
    glLightfv (GL_LIGHT1, GL_AMBIENT, lightColor1[0]);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, lightColor1[1]);
    glLightfv (GL_LIGHT1, GL_SPECULAR, lightColor1[2]);

    /* Set Spotlight properties of the second light source */
    glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, lightCutoff1);
    glLightf (GL_LIGHT1, GL_SPOT_EXPONENT, lightExponent1);

    /* set color of the second light source */
    glLightfv (GL_LIGHT2, GL_AMBIENT, lightColor2[0]);
    glLightfv (GL_LIGHT2, GL_DIFFUSE, lightColor2[1]);
    glLightfv (GL_LIGHT2, GL_SPECULAR, lightColor2[2]);

    /* Set Spotlight properties of the second light source */
    glLightf (GL_LIGHT2, GL_SPOT_CUTOFF, lightCutoff1);
    glLightf (GL_LIGHT2, GL_SPOT_EXPONENT, lightExponent1);
}

/**
 * When the game starts, the game is fully initialized 
 * with a background, a character color, line width. 
 * In addition, the data storage is initialized (see init field (), 
 *  init stones ()). @return Whether an error has occurred.
 */
int initScene (void)
{
    glEnable (GL_DEPTH_TEST);
    glCullFace (GL_BACK);
    glEnable (GL_CULL_FACE);
    glEnable (GL_NORMALIZE);
    glEnable (GL_LIGHTING);
    initLight ();

    return 1;
}



/**
 * Disables the wireframe mode
 */
void
toggleWireframeMode (void)
{
    /* Flag: Wireframe: yes / no */
    static GLboolean wireframe = GL_FALSE;

    /* Switch mode */
    wireframe = !wireframe;

    if (wireframe)
        glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
}

