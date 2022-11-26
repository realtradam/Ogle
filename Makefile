
CXX ?= g++
EXE := game
BUILD_DIR := build

INC_FLAGS := -Isrc -Iglfw/build/include -Iglad/include -Istb -Iglm
LINK_FLAGS := -lGL -lX11 -lpthread -lXrandr -lXi -ldl

GLFW_LIB := glfw/build/src/libglfw3.a
EXTERNAL_LIBS := $(GLFW_LIB)

PROJ_SYSTEMS := input shader batch texture window random
PROJ_OBJ_NAMES := $(addsuffix .o, $(PROJ_SYSTEMS))
OBJ_NAMES := glad.o $(PROJ_OBJ_NAMES)
OBJ_FILES := $(addprefix $(BUILD_DIR)/, $(OBJ_NAMES))

# --- Main ---
$(BUILD_DIR)/$(EXE): src/main.cpp $(EXTERNAL_LIBS) $(OBJ_FILES)
	@echo --- main ---
	@mkdir -p $(BUILD_DIR)
	$(CXX) -o $(BUILD_DIR)/$(EXE) src/main.cpp $(OBJ_FILES) $(INC_FLAGS) $(EXTERNAL_LIBS) $(LINK_FLAGS)

# --- Systems ---
$(BUILD_DIR)/%.o: src/*.cpp src/*.hpp
	@echo ---$*---
	@mkdir -p $(BUILD_DIR)
	$(CXX) -o $(BUILD_DIR)/$*.o -c src/$*.cpp $(INC_FLAGS) $(LINK_FLAGS)

# --- External Libs ---
$(BUILD_DIR)/glad.o: glad/src/glad.c
	@echo ---glad---
	@mkdir -p $(BUILD_DIR)
	$(CXX) -o $(BUILD_DIR)/glad.o -c glad/src/glad.c $(INC_FLAGS) $(LINK_FLAGS)

$(GLFW_LIB):
	@echo ---glfw---
	 cmake -S glfw -B glfw/build && cd glfw/build && make;

# --- Utility ---
.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

.PHONY: deep_clean
deep_clean: clean
	rm -r glfw/build

.PHONY: run
run: $(BUILD_DIR)/$(EXE)
	$(BUILD_DIR)/$(EXE)
