
EXE := game
BUILD_DIR := build
INC_FLAGS := -Isrc -Iglfw/build/include -Iglad/include
LINK_FLAGS := -lGL -lX11 -lpthread -lXrandr -lXi -ldl
OBJ_NAMES := glad.o input.o shader.o
OBJ_FILES := $(addprefix $(BUILD_DIR)/, $(OBJ_NAMES))


default: src/main.cpp $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	g++ -o $(BUILD_DIR)/$(EXE) src/main.cpp $(OBJ_FILES) $(INC_FLAGS) glfw/build/lib/libglfw3.a $(LINK_FLAGS)

glad.o: glad/src/glad.c
	@mkdir -p $(BUILD_DIR)
	g++ -o $(BUILD_DIR)/glad.o -c glad/src/glad.c $(INC_FLAGS) $(LINK_FLAGS)
input.o: src/input.cpp src/input.h
	@mkdir -p $(BUILD_DIR)
	g++ -o $(BUILD_DIR)/input.o -c src/input.cpp $(INC_FLAGS) $(LINK_FLAGS)
shader.o: src/shader.cpp src/shader.hpp
	@mkdir -p $(BUILD_DIR)
	g++ -o $(BUILD_DIR)/shader.o -c src/shader.cpp $(INC_FLAGS) $(LINK_FLAGS)

.PHONY: run
run: default
	$(BUILD_DIR)/$(EXE)
