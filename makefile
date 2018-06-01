Program: Program.o GameEngine.o UIBar.o Player.o Armory.o Weapon.o Bullet.o GameObject.o helpers/Game.o helpers/ShapeBuilder.o
	g++ -g -pthread Program.o GameEngine.o UIBar.o Player.o Armory.o Weapon.o Bullet.o GameObject.o helpers/Game.o helpers/ShapeBuilder.o -o Program -lglfw3 -lGLEW -lGLU -lGL -lglut -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lXcursor -std=c++11 -ggdb -O0

clean:
	rm *.o
