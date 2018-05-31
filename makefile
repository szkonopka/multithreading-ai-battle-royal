Program: Program.o GameEngine.o UIBar.o Player.o Weapon.o Bullet.o GameObject.o helpers/ShapeBuilder.o
	g++ -pthread Program.o GameEngine.o UIBar.o Player.o Weapon.o Bullet.o GameObject.o helpers/ShapeBuilder.o -o Program -lglfw3 -lGLEW -lGLU -lGL -lglut -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lXcursor -std=c++11

clean:
	rm *.o
