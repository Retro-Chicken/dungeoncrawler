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
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
SOURCES := $(call rwildcard,,*.cpp)
OBJ_DIR := $(TARGET_PATH)/objects
OBJECTS := $(SOURCES:$(SRC_PATH)/%.cpp=$(OBJ_DIR)/%.o)

.SECONDEXPANSION:
.PRECIOUS: %/.stamp
.PHONY: all

# Linking commands
all: $(TARGET_PATH)/.stamp $(OBJ_DIR)/.stamp $(TARGET_PATH)/$(TARGET)
	export LD_LIBRARY_PATH="sfml/lib-linux"

#Directory creation handling with stamps
%/.stamp:
	-mkdir -p $(@D)
	touch $@

# Compilation commands (Compiles all files in source directory)
$(TARGET_PATH)/$(TARGET): $(OBJECTS) $$(@D)/.stamp
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_PATH)/%.cpp $$(@D)/.stamp
	$(CXX) -c $< -o $@ -I$(SFML_INCLUDE)
