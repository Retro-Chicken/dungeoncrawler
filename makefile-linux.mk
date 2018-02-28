CXX := g++

# Linking commands
linux-build: main.o $(shell find "sfml-linux/lib" -type f)
	$(CXX) builds/main.o -o builds/linux-build -L "sfml-linux/lib" -lsfml-graphics -lsfml-window -lsfml-system

# Compilation commands
main.o: $(shell find "sfml-linux/include" -type f)
	$(CXX) -c game/main.cpp -o builds/main.o -I "sfml-linux/include"
