default: src/main.cpp glad.o
	g++ -o build/game src/main.cpp build/glad.o -Iglfw/build/include -Iglad/include glfw/build/lib/libglfw3.a -lGL -lX11 -lpthread -lXrandr -lXi -ldl

glad.o: glad/src/glad.c
	g++ -o build/glad.o -c glad/src/glad.c -Iglfw/build/include -Iglad/include -lGL -lX11 -lpthread -lXrandr -lXi -ldl

.PHONY: run
run: default
	./build/game
