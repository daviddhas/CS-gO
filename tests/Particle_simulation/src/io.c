
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/* ---- System Header files--- */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* ---- User header files ---- */
#include "io.h"
#include "scene.h"
#include "logic.h"
#include "vector.h"
#include "imageLoader.h"


/* Shader-ID's */
GLuint G_ShaderColor, G_ComputeShader;

/* Shader-Variables */
GLuint G_Velocity_buffer_loc, G_Position_buffer_loc;
Attractor G_Attractor;
// AttractorMass G_Attractor_Mass;
GLuint G_Position_buffer_tex, G_Velocity_buffer_tex;

/* Geometry-Buffer */
GLuint G_ObjectsBuffer, G_Compute_Buffers, G_Position_buffer, G_Velocity_buffer, G_Attractor_buffer, G_AttractorMass_buffer, G_Life_buffer;

GLuint G_Dispatch_buffer;

static const struct
{
    GLuint num_groups_x;
    GLuint num_groups_y;
    GLuint num_groups_z;
} G_Dispatch_params = {16, 16, 1};

Vec3 * G_ComputePositions;
Vec4 * G_ComputeVelocities;
Vec4 * G_ComputeAttractors;
float * G_ComputeAttractorMass;
float * G_ComputeLife;

int G_Width = 1920;
int G_Height = 1080;
int G_FullScreen = 1;
char* G_WindowTitle = "";
GLFWwindow * G_Window = NULL;
float G_Interval = 0;
float G_ThisCallTime = 0;

int G_FPS_Count = 0;
double G_FPS_All = 0;


GLfloat G_Objects[] = {
    -15.0, -15.0, -15.0,
    15.0, -15.0, -15.0,
    15.0, 15.0, -15.0,
    -15.0, -15.0, -15.0,
    15.0, 15.0, -15.0,
    -15.0, 15.0, -15.0
};

/**
 * Timer-Callback.
 *  Initiated calculating the current position and color and subsequent
  * Redraw sets itself again as a timer callback.
  * @param Last call time point at which the function as a timer function
 */
double cbTimer (int lastCallTime)
{
    /* Starting the program elapsed time in seconds*/
    G_Interval = glfwGetTime();
    glfwSetTime(0.0);

    G_FPS_Count++;
    G_FPS_All += G_Interval;

    if (G_FPS_Count >= 1000) {
        printf ("fps: %i\n", (int) (1.0 / ((double)G_FPS_All / (double)G_FPS_Count)));
        G_FPS_All = 0.0;
        G_FPS_Count = 0;
    }

    /*printf ("dt: %f\n", G_Interval);*/

    calcTimeRelatedStuff(G_Interval);
    return G_Interval;
}

/**
 * Setting the projection matrix.
  * Sets the projection matrix taking into account the Seitenverhaeltnisses
  * The display window so that the Seitenverhaeltnisse the scene unchanged
  * Remains while either in x- or y-direction of the range of -1
  * Can be seen to +1.
  * @param Aspect Seitenverhaeltnis the display window
 */
static void
setProjection (GLdouble aspect)
{
  /* Subsequent operations affect projection matrix*/
  glMatrixMode (GL_PROJECTION);
  /* Matrix back set - Load unit matrix */
  glLoadIdentity ();

  {
      /* perspective projection */
      gluPerspective (90.0,     
                      aspect,   
                      0.5,      
                      10000.0);
  }
}

/**
 * Sign callback. 
 * Clears the buffer, calls on the character of the scene and exchanged the front 
 * and BackBuffer.
 */
static void cbDisplay (GLFWwindow * window)
{
    int i;
    int modValue = 3000;
    double difValue = 10.0;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);

    glDisable(GL_CULL_FACE);

    glViewport (0, 0, G_Width, G_Height);
    setProjection ((double)G_Width/G_Height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (getCameraPosition(0), getCameraPosition(1), getCameraPosition(2),
         0.0, 0.0, 0.0,
         0.0, 1.0, 0.0);

    G_ComputeAttractors = (Vec4*)glMapBufferRange(GL_ARRAY_BUFFER, 0, ATTRACTOR_COUNT*sizeof(Vec4), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    for (i = 0; i < ATTRACTOR_COUNT; i++) {
        G_ComputeAttractors[i].x = sinf(G_FPS_All) * (rand()%500)/10.0;
        G_ComputeAttractors[i].y = cosf(G_FPS_All) * (rand()%500)/10.0;
        G_ComputeAttractors[i].z = tanf(G_FPS_All);
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

    glGenBuffers(1, &G_Attractor_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, G_Attractor_buffer);
    glBufferData(GL_ARRAY_BUFFER, ATTRACTOR_COUNT * sizeof(Vec4), G_ComputeAttractors, GL_DYNAMIC_COPY);

    if (1) {
        glUseProgram(G_ComputeShader);

        /* Time Interval history */
        glUniform1fv(glGetUniformLocation(G_ComputeShader, "dt"), 1, &G_Interval);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, G_Position_buffer);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, G_Velocity_buffer);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, G_Attractor_buffer);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, G_Life_buffer);

        glDispatchCompute(PARTICLE_COUNT / 128, 1, 1);
        glMemoryBarrier(GL_ALL_BARRIER_BITS);
        glUseProgram(0);
    }

    glDeleteBuffers(1, &G_Attractor_buffer);

    glUseProgram(G_ShaderColor);

    GLfloat mp[16], mv[16];
    glGetFloatv(GL_PROJECTION_MATRIX, mp);
    glGetFloatv(GL_MODELVIEW_MATRIX, mv);
    glUniformMatrix4fv(glGetUniformLocation(G_ShaderColor, "projMatrix"),  1, GL_FALSE, &mp[0]);
    glUniformMatrix4fv(glGetUniformLocation(G_ShaderColor, "viewMatrix"),  1, GL_FALSE, &mv[0]);

    /* Vertex buffers to render the positions */
    glBindBuffer (GL_ARRAY_BUFFER, G_Position_buffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
    glBindBuffer (GL_ARRAY_BUFFER, G_Life_buffer);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), 0);

    glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);

    glEnable(GL_CULL_FACE);
    glUseProgram(0);



    /* fuer DoubleBuffering */
    glfwSwapBuffers(window);

    glfwSwapInterval(0);
}

/**
 * Creating a window in a fullscreen-Mode.
 */
int createWindow(void)
{
    if (G_Window)
        glfwDestroyWindow(G_Window);

    glfwDefaultWindowHints();

    if (G_FullScreen)
        G_Window = glfwCreateWindow(1920, 1080, G_WindowTitle, glfwGetPrimaryMonitor(), NULL);
    else
        G_Window = glfwCreateWindow(G_Width, G_Height, G_WindowTitle, NULL, NULL);

    if (G_Window) {
        glfwMakeContextCurrent(G_Window);
        glfwGetFramebufferSize(G_Window, &G_Width, &G_Height);
    } else {
        return 0;
    }

    return 1;
}

int readFile (char * name, GLchar ** buffer) {
    FILE *f = fopen(name, "rb");
    fseek(f, 0, SEEK_END);
    int pos = ftell(f);
    fseek(f, 0, SEEK_SET);

    (*buffer) = malloc(pos+1);
    fread(*buffer, pos-1, 1, f);
    (*buffer)[pos-1] = '\0';
    fclose(f);
}

GLuint loadComputeShader(char * computeShader)
{
      /* Create the shaders */
    GLuint computeShaderID = glCreateShader(GL_COMPUTE_SHADER);

    GLint result = GL_FALSE;
    int infoLogLength;

    /* Compile Vertex Shader */
    printf("Compiling Compute shader\n");
    char * computeSourcePointer = NULL;
    readFile(computeShader, &computeSourcePointer);

    glShaderSource(computeShaderID, 1, (const GLchar **)&computeSourcePointer , NULL);
    glCompileShader(computeShaderID);

    /* Check Vertex Shader */
    glGetShaderiv(computeShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(computeShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    char * computeShaderErrorMessage = calloc(infoLogLength, sizeof(char));
    glGetShaderInfoLog(computeShaderID, infoLogLength, NULL, &(computeShaderErrorMessage[0]));
    fprintf(stdout, "computeShaderErrorMessage: %s\n", computeShaderErrorMessage);

    /*  Link the program */
    GLuint programID = glCreateProgram();

    glAttachShader(programID, computeShaderID);

    printf ("Compute Shader ID: %d\n", computeShaderID);

    glLinkProgram(programID);

    /* Check the program */
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    char * programErrorMessage = calloc(infoLogLength, sizeof(char));
    glGetProgramInfoLog(programID, infoLogLength, NULL, &(programErrorMessage[0]));
    fprintf(stdout, "programErrorMessage: %s\n", programErrorMessage);

    glDeleteShader(computeShaderID);

    printf ("Compute Shader Program ID: %d\n", programID);

    return programID;
}

GLuint loadShaders(char * vertexShader, char * fragmentShader){

    /* Create the shaders */
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    /* Compile Vertex Shader */
    printf("Compiling Vertex shader\n");
    char * VertexSourcePointer = NULL;
    readFile(vertexShader, &VertexSourcePointer);

    glShaderSource(VertexShaderID, 1, (const GLchar **)&VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    /* Check Vertex Shader */
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    char * vertexShaderErrorMessage = calloc(InfoLogLength, sizeof(char));
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &(vertexShaderErrorMessage[0]));
    fprintf(stdout, "vertexShaderErrorMessage: %s\n", vertexShaderErrorMessage);

    /* Compile Fragment Shader */
    printf("Compiling Fragment shader\n");
    char * FragmentSourcePointer = NULL;
    readFile(fragmentShader, &FragmentSourcePointer);

    glShaderSource(FragmentShaderID, 1, (const GLchar **)&FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    /* Check Fragment Shader */
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    char * fragmentShaderErrorMessage = calloc(InfoLogLength, sizeof(char));
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &(fragmentShaderErrorMessage[0]));
    fprintf(stdout, "fragmentShaderErrorMessage: %s\n", fragmentShaderErrorMessage);

    /*  Link the program */
    GLuint ProgramID = glCreateProgram();

    glAttachShader(ProgramID, VertexShaderID);

    glAttachShader(ProgramID, FragmentShaderID);

    glLinkProgram(ProgramID);

    /* Check the program */
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    char * programErrorMessage = calloc(InfoLogLength, sizeof(char));
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &(programErrorMessage[0]));
    fprintf(stdout, "programErrorMessage: %s\n", programErrorMessage);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

/**
 * Main loop with callback, if the window should be closed.
 */
void mainLoop (GLFWwindow * window)
{
    double lastCallTime = cbTimer(0.0);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    while (!glfwWindowShouldClose(window))
    {
        cbDisplay (window);
        lastCallTime = cbTimer (lastCallTime);
        glfwPollEvents();
    }

}

/* Initializes the program (incl. I / O and OpenGL) and starts*/
int initAndStartIO (char *title, int width, int height)
{

    G_Width = width;
    G_Height = height;
    /*G_WindowTitle = malloc(sizeof(title)*sizeof(char));*/
    G_WindowTitle = title;
    G_FullScreen = 0;

    if (!glfwInit())
        return 0;

    if (createWindow())
    {
        GLenum err = glewInit();
        if (err != GLEW_OK)
        {
          /* Problem: glewInit failed, something is seriously wrong. */
          printf("Error: %s\n", glewGetErrorString(err));
          glfwDestroyWindow(G_Window);
          exit(1);
        }
        printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
        /* Background is initialized (colors) */
        if (initScene ())
        {
            int i;
            printf ("--> Shader are on!...\n"); fflush(stdout);

            G_ShaderColor = loadShaders("colorVertexShader.vert", "colorFragmentShader.frag");
            G_ComputeShader = loadComputeShader("particlesComputeShader.comp");

            printf ("--> Shaders are loaded.\n"); fflush(stdout);

           // registerCallBacks (G_Window);

            glGenBuffers(1, &G_ObjectsBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, G_ObjectsBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(G_Objects), G_Objects, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            /* Physics-Simulation! ==================================================*/

            /* Position */
            G_ComputePositions = calloc(PARTICLE_COUNT, sizeof(Vec3));
            for (i = 0; i < PARTICLE_COUNT; i++) {
                Vec3 vec;
                vec.x = (rand() % 2000) / (500.0);
                vec.y = (rand() % 2000) / (500.0);
                vec.z = (rand() % 2000) / (500.0);
                G_ComputePositions[i] = vec;
            }

            glGenBuffers    (1, &G_Position_buffer);
            glBindBuffer    (GL_ARRAY_BUFFER, G_Position_buffer);
            glBufferData    (GL_ARRAY_BUFFER, PARTICLE_COUNT * sizeof(Vec3), G_ComputePositions, GL_DYNAMIC_COPY);

            /* Lifespan */
            G_ComputeLife = calloc(PARTICLE_COUNT, sizeof(float));
            for (i = 0; i < PARTICLE_COUNT; i++) {
                G_ComputeLife[i] = rand() / (double)RAND_MAX;
            }

            glGenBuffers    (1, &G_Life_buffer);
            glBindBuffer    (GL_ARRAY_BUFFER, G_Life_buffer);
            glBufferData    (GL_ARRAY_BUFFER, PARTICLE_COUNT * sizeof(float), G_ComputeLife, GL_DYNAMIC_COPY);

            /* Speed */
            G_ComputeVelocities = calloc(PARTICLE_COUNT, sizeof(Vec4));
            for (i = 0; i < PARTICLE_COUNT; i++) {
                Vec4 vec;
                vec.x = (rand() % 100) / 500.0 - (rand() % 100) / 500.0;
                vec.y = (rand() % 100) / 500.0 - (rand() % 100) / 500.0;
                vec.z = (rand() % 100) / 500.0 - (rand() % 100) / 500.0;
                vec.w =  0.0;
                G_ComputeVelocities[i] = vec;
            }

            glGenBuffers    (1, &G_Velocity_buffer);
            glBindBuffer    (GL_ARRAY_BUFFER, G_Velocity_buffer);
            glBufferData    (GL_ARRAY_BUFFER, PARTICLE_COUNT * sizeof(Vec4), G_ComputeVelocities, GL_DYNAMIC_COPY);

            /* Attractions */
            G_ComputeAttractors = calloc(ATTRACTOR_COUNT, sizeof(Vec4));
            for (i = 0; i < ATTRACTOR_COUNT; i++) {
                Vec4 vec;
                vec.x = (rand() % 500) / 30.0 - (rand() % 500) / 30.0;
                vec.y = (rand() % 500) / 30.0 - (rand() % 500) / 30.0;
                vec.z = (rand() % 500) / 30.0 - (rand() % 500) / 30.0;
                vec.w = 0;
                G_ComputeAttractors[i] = vec;
            }
            glGenBuffers(1, &G_Attractor_buffer);
            glBindBuffer(GL_ARRAY_BUFFER, G_Attractor_buffer);
            glBufferData(GL_ARRAY_BUFFER, ATTRACTOR_COUNT * sizeof(Vec4), G_ComputeAttractors, GL_DYNAMIC_COPY);

            printf ("--> Initialization.\n"); fflush(stdout);

            mainLoop (G_Window);


        } else {
            glfwDestroyWindow(G_Window);
            return 0;
        }
    } else {
        return 0;
    }

    glDeleteBuffers(1, &G_Position_buffer);
    glDeleteBuffers(1, &G_Velocity_buffer);

    glfwDestroyWindow(G_Window);

    return 1;
}
