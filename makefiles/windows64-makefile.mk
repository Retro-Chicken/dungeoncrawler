# Paths
SRC_PATH := src
TARGET_PATH := bin/windows64
TARGET := windows64-build
# Directories of sfml libraries
SFML_INCLUDE := sfml/include
SFML_LIB := sfml/lib-windows64
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
all: $(TARGET_PATH)/.stamp $(OBJ_DIR)/.stamp $(TARGET_PATH)/$(TARGET).exe

#Directory creation handling with stamps
%/.stamp:
	-mkdir $(subst /,\,$(@D))
	type nul > $@

# Compilation commands (Compiles all files in source directory)
$(TARGET_PATH)/$(TARGET).exe: $(OBJECTS) $$(@D)/.stamp
	$(CXX) $(OBJECTS) -o $(TARGET_PATH)/$(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_PATH)/%.cpp $$(@D)/.stamp
	$(CXX) -c $< -o $@ -I$(SFML_INCLUDE)
