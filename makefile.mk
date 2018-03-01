# Compiler
CXX := g++
# Directories of sfml libraries
SFML_INCLUDE := sfml/include
SFML_LINUX_LIB := sfml/lib-linux
SFML_WINDOWS_LIB := sfml/lib-windows
# Modules currently being used in game (linking command)
SFML_ACTIVE_MODULES := -lsfml-graphics -lsfml-window -lsfml-system

# Linking commands
linux-build: main.o $(shell find $(SFML_LINUX_LIB) -type f)
	$(CXX) builds/main.o -o builds/linux-build -L$(SFML_LINUX_LIB) $(SFML_ACTIVE_MODULES)

windows-build: main.o $(shell find $(SFML_WINDOWS_LIB) -type f)
	$(CXX) builds/main.o -o builds/windows-build -L$(SFML_WINDOWS_LIB) $(SFML_ACTIVE_MODULES)

# Compilation commands
main.o: game/main.cpp $(shell find $(SFML_INCLUDE) -type f)
	$(CXX) -c game/main.cpp -o builds/main.o -I$(SFML_INCLUDE)
