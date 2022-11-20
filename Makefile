default: src/main.cpp glad.o input.o
	@mkdir -p build
	g++ -o build/game src/main.cpp build/glad.o build/input.o -Isrc -Iglfw/build/include -Iglad/include glfw/build/lib/libglfw3.a -lGL -lX11 -lpthread -lXrandr -lXi -ldl

input.o: src/input.cpp src/input.h
	@mkdir -p build
	g++ -o build/input.o -c src/input.cpp -Isrc -Iglfw/build/include -Iglad/include -lGL -lX11 -lpthread -lXrandr -lXi -ldl

glad.o: glad/src/glad.c
	@mkdir -p build
	g++ -o build/glad.o -c glad/src/glad.c -Isrc -Iglfw/build/include -Iglad/include -lGL -lX11 -lpthread -lXrandr -lXi -ldl

.PHONY: run
run: default
	./build/game
