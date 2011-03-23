
all : ingenious-hovercraft

ingenious-hovercraft : main.cpp graphics.cpp terrain.cpp physics.cpp common.cpp
	gcc -Wall -o ingenious-hovercraft -lGL -lGLU -lglut -ljpeg main.cpp graphics.cpp terrain.cpp physics.cpp common.cpp

clean :
	rm ingenious-hovercraft

