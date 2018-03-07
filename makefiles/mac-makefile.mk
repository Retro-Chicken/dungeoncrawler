# Paths
SRC_PATH := src
TARGET_PATH := bin/mac
TARGET := mac-build
# Directories of sfml libraries
SFML_INCLUDE := sfml/include
# Modules currently being used in game (linking command)
SFML_ACTIVE_FRAMEWORKS := -framework sfml-system -framework sfml-graphics -framework sfml-window

CXX := clang++
LDFLAGS := $(SFML_ACTIVE_FRAMEWORKS)
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
SOURCES := $(call rwildcard,,*.cpp)
OBJ_DIR := $(TARGET_PATH)/objects
OBJECTS := $(SOURCES:$(SRC_PATH)/%.cpp=$(OBJ_DIR)/%.o)

.SECONDEXPANSION:
.PRECIOUS: %/.stamp
.PHONY: all

# Linking commands
all: $(TARGET_PATH)/.stamp $(OBJ_DIR)/.stamp $(TARGET_PATH)/$(TARGET)

#Directory creation handling with stamps
%/.stamp:
	-mkdir -p $(@D)
	touch $@

# Compilation commands (Compiles all files in source directory)
$(TARGET_PATH)/$(TARGET): $(OBJECTS) $$(@D)/.stamp
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_PATH)/%.cpp $$(@D)/.stamp
	$(CXX) -c $< -o $@ -I$(SFML_INCLUDE)
