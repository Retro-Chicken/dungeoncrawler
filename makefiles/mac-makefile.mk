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
SOURCES = $(wildcard $(SRC_PATH)/*.cpp)
OBJ_DIR := $(TARGET_PATH)/objects
OBJECTS := $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

.PHONY: all build

# Linking commands
all: build $(TARGET_PATH)/$(TARGET)

build:
	-mkdir -p $(TARGET_PATH)
	-mkdir -p $(OBJ_DIR)
#--------------------------------------- END OF LINKING -------------------------------------------------
# Compilation commands
$(TARGET_PATH)/$(TARGET): $(OBJECTS)
	-mkdir -p $(@D)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	-mkdir -p $(@D)
	$(CXX) -c $< -o $@ -I$(SFML_INCLUDE)
