# Paths
SRC_PATH := src
TARGET_PATH := bin/windows
TARGET := windows32-build
# Directories of sfml libraries
SFML_INCLUDE := sfml/include
SFML_LIB := sfml/lib-windows
# Modules currently being used in game (linking command)
SFML_ACTIVE_MODULES := -lsfml-graphics -lsfml-window -lsfml-system

CXX := g++
LDFLAGS := -L$(SFML_LIB) $(SFML_ACTIVE_MODULES)
SOURCES = $(wildcard $(SRC_PATH)/*.cpp)
OBJ_DIR := $(TARGET_PATH)/objects
OBJECTS := $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

.PHONY: all build

# Linking commands
all: build $(TARGET_PATH)/$(TARGET)

build:
	-mkdir $(subst /,\,$(TARGET_PATH))
	-mkdir $(subst /,\,$(OBJ_DIR))
#--------------------------------------- END OF LINKING -------------------------------------------------
# Compilation commands
$(TARGET_PATH)/$(TARGET): $(OBJECTS)
	-mkdir $(subst /,\,$(@D))
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	-mkdir $(subst /,\,$(@D))
	$(CXX) -c $< -o $@ -I$(SFML_INCLUDE)
