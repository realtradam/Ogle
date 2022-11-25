
EXE := game
BUILD_DIR := build
INC_FLAGS := -Isrc -Iglfw/build/include -Iglad/include -Istb -Iglm
LINK_FLAGS := -lGL -lX11 -lpthread -lXrandr -lXi -ldl
OBJ_NAMES := glad.o input.o shader.o batch.o texture.o window.o random.o
OBJ_FILES := $(addprefix $(BUILD_DIR)/, $(OBJ_NAMES))


$(BUILD_DIR)/$(EXE): src/main.cpp $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	g++ -o $(BUILD_DIR)/$(EXE) src/main.cpp $(OBJ_FILES) $(INC_FLAGS) glfw/build/lib/libglfw3.a $(LINK_FLAGS)

$(BUILD_DIR)/glad.o: glad/src/glad.c
	@mkdir -p $(BUILD_DIR)
	g++ -o $(BUILD_DIR)/glad.o -c glad/src/glad.c $(INC_FLAGS) $(LINK_FLAGS)
$(BUILD_DIR)/input.o: src/input.cpp src/input.hpp
	@mkdir -p $(BUILD_DIR)
	g++ -o $(BUILD_DIR)/input.o -c src/input.cpp $(INC_FLAGS) $(LINK_FLAGS)
$(BUILD_DIR)/shader.o: src/shader.cpp src/shader.hpp
	@mkdir -p $(BUILD_DIR)
	g++ -o $(BUILD_DIR)/shader.o -c src/shader.cpp $(INC_FLAGS) $(LINK_FLAGS)
$(BUILD_DIR)/batch.o: src/batch.cpp src/batch.hpp
	@mkdir -p $(BUILD_DIR)
	g++ -o $(BUILD_DIR)/batch.o -c src/batch.cpp $(INC_FLAGS) $(LINK_FLAGS)
$(BUILD_DIR)/texture.o: src/texture.cpp src/texture.hpp
	@mkdir -p $(BUILD_DIR)
	g++ -o $(BUILD_DIR)/texture.o -c src/texture.cpp $(INC_FLAGS) $(LINK_FLAGS)
$(BUILD_DIR)/window.o: src/window.cpp src/window.hpp
	@mkdir -p $(BUILD_DIR)
	g++ -o $(BUILD_DIR)/window.o -c src/window.cpp $(INC_FLAGS) $(LINK_FLAGS)
$(BUILD_DIR)/random.o: src/random.cpp src/random.hpp
	@mkdir -p $(BUILD_DIR)
	g++ -o $(BUILD_DIR)/random.o -c src/random.cpp $(INC_FLAGS) $(LINK_FLAGS)

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

.PHONY: run
run: $(BUILD_DIR)/$(EXE)
	$(BUILD_DIR)/$(EXE)
