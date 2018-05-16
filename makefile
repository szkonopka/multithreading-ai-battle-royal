Program: Program.o UIBar.o Player.o GameObject.o ShapeBuilder.o
	g++ -pthread Program.o UIBar.o Player.o GameObject.o ShapeBuilder.o -o Program -lglfw3 -lGLEW -lGLU -lGL -lglut -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lXcursor

clean:
	rm *.o
