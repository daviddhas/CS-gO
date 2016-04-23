INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/lib

FLAGS = -Wall
CC = g++
CFLAGS = $(FLAGS) $(INCLUDE)
CFLAGS += -std=c++14
LIBS =  -lGL -lGLU -lglfw
LIBS += -L/usr/local/lib -lglfw3 -lrt -lXrandr -lXinerama -lXi -lXcursor -lGL -lm -ldl -lXrender -ldrm -lXdamage -lX11-xcb -lxcb-glx -lxcb-dri2 -lxcb-dri3 -lxcb-present -lxcb-sync -lxshmfence -lXxf86vm -lXfixes -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp

All:
	g++ -std=c++14 function_based.cpp main.cpp ../source/gl/gl_4_5.core.cpp -lglfw -lGL -lGLU -I../include -I../vendor/glfw/include -I../vendor/glm -lX11 -o main -L/usr/local/lib -lglfw3 -lrt -lXrandr -lXinerama -lXi -lXcursor -lGL -lm -ldl -lXrender -ldrm -lXdamage -lX11-xcb -lxcb-glx -lxcb-dri2 -lxcb-dri3 -lxcb-present -lxcb-sync -lxshmfence -lXxf86vm -lXfixes -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp  -o main

clean:
	        rm main
		    rm *.o

attempt:
	$(CC) -std=c++14 function_based.cpp main.cpp ../source/gl/gl_4_5.core.cpp -I../include -I../vendor/glfw/include -I../vendor/glm -lX11 -o main  $(LIBS)




