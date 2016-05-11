INCLUDEDIR = -I/usr/include/ -I../include -I../vendor/glfw/include -I../vendor/glm
LIBDIR  = -L/usr/lib -L/usr/local/lib

FLAGS =
CC = g++
CFLAGS = $(FLAGS) $(INCLUDEDIR)
CFLAGS += -std=c++14
LIBS =  -lGL -lGLU -lglfw
#LIBS += -lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread

All:
	$(CC) $(CFLAGS) main.cpp ../source/gl/gl_4_5.core.cpp $(LIBDIR) $(LIBS) -o main

clean:
	rm  main

attempt:
	$(CC) -std=c++14 function_based.cpp main.cpp ../source/gl/gl_4_5.core.cpp -I../include -I../vendor/glfw/include -I../vendor/glm -lX11 -lglfw3 -o main  $(LIBS)




