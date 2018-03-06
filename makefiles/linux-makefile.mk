# Paths
SRC_PATH := src
TARGET_PATH := bin/linux
TARGET := linux-build
# Directories of sfml libraries
SFML_INCLUDE := sfml/include
SFML_LIB := sfml/lib-linux
# Modules currently being used in game (linking command)
SFML_ACTIVE_MODULES := -lsfml-graphics -lsfml-window -lsfml-system

CXX := g++
LDFLAGS := -L$(SFML_LIB) $(SFML_ACTIVE_MODULES)
SOURCES = $(wildcard $(SRC_PATH)/*.cpp)
OBJ_DIR := $(TARGET_PATH)/objects
OBJECTS := $(SOURCES:$(SRC_PATH)/%.cpp=$(OBJ_DIR)/%.o)

.PHONY: all build

# Linking commands
all: build $(TARGET_PATH)/$(TARGET)
	export LD_LIBRARY_PATH="sfml/lib-linux"

build:
	-mkdir -p $(TARGET_PATH)
	-mkdir -p $(OBJ_DIR)
#--------------------------------------- END OF LINKING -------------------------------------------------
# Compilation commands
$(TARGET_PATH)/$(TARGET): $(OBJECTS)
	-mkdir -p $(@D)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_PATH)/%.cpp
	-mkdir -p $(@D)
	$(CXX) -c $< -o $@ -I$(SFML_INCLUDE)
