Program: Program.o GameObject.o 
	g++ -pthread Program.o GameObject.o -o Program -lglfw3 -lGLEW -lGLU -lGL -lglut -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lXcursor
