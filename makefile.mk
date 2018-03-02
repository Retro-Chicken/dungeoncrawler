# Paths
SRC_PATH := src/
TARGET_PATH := bin/
# Directories of sfml libraries
SFML_INCLUDE := sfml/include
SFML_LINUX_LIB := sfml/lib-linux
SFML_WINDOWS_LIB := sfml/lib-windows
# Modules currently being used in game (linking command)
SFML_ACTIVE_MODULES := -lsfml-graphics -lsfml-window -lsfml-system
SFML_ACTIVE_FRAMEWORKS := -framework sfml-system -framework sfml-graphics -framework sfml-window

# Linking commands
linux-build: TARGET := linux-build
linux-build: CXX := g++
linux-build: TARGET_PATH := $(TARGET_PATH)linux/
linux-build: $(TARGET_PATH)main.o $(shell find $(SFML_LINUX_LIB) -type f)
	$(CXX) $(TARGET_PATH)main.o -o $(TARGET_PATH)$(TARGET) -L$(SFML_LINUX_LIB) $(SFML_ACTIVE_MODULES)

windows-build: TARGET := windows-build
windows-build: CXX := g++
windows-build: TARGET_PATH := $(TARGET_PATH)windows/
windows-build: $(TARGET_PATH)main.o $(shell find $(SFML_WINDOWS_LIB) -type f)
	$(CXX) $(TARGET_PATH)main.o -o $(TARGET_PATH)$(TARGET) -L$(SFML_WINDOWS_LIB) $(SFML_ACTIVE_MODULES)

mac-build: TARGET := mac-build
mac-build: CXX := g++
mac-build: TARGET_PATH := $(TARGET_PATH)mac/
mac-build: $(TARGET_PATH)main.o
	$(CXX) $(TARGET_PATH)main.o -o $(TARGET_PATH)$(TARGET) $(SFML_ACTIVE_FRAMEWORKS)

# Compilation commands
$(TARGET_PATH)main.o: $(SRC_PATH)main.cpp $(shell find $(SFML_INCLUDE) -type f)
	$(CXX) -c $(SRC_PATH)main.cpp -o $(TARGET_PATH)main.o -I$(SFML_INCLUDE)
