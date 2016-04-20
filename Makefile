INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/lib

FLAGS = -Wall
CC = g++
CFLAGS = $(FLAGS) $(INCLUDE)
LIBS =  -lGL -lGLU -lglfw

All: simple

simple: simple.o
	    $(CC) simple.o -o simple $(LIBS)

clean:
	        rm simple
		    rm *.o

#g++ simple.cpp -o simple -lGL -lGLU -lglut

