BIN = compute
CC = g++
FLAGS = -Wall -pedantic
INC = -I ../common/include
LOC_LIB = ../common/linux_x86_64/libGLEW.a ../common/linux_x86_64/libglfw3.a
SYS_LIB = -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi
SRC = main.cpp gl_utils.cpp

all:
	${CC} ${FLAGS} -o ${BIN} ${SRC} ${INC} ${LOC_LIB} ${SYS_LIB}

clean:
	rm compute
