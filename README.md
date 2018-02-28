# Dungeon Crawler

This is a the repository for our turn and tile based dungeon crawler. The project is being made for Advanced Computer Science at LASA High School by Will Fisher, Zayan Vohra, Andy Mueller, Dodie Robison, and Nelson Barnes.

![Retro Chicken](rclogo.PNG)

# Building
### Linux ###
For linux systems you can build and run the program by executing
```
cd <project directory>
./run-linux.sh
```
To solely build the program simply execute
```
cd <project directory>
make -f makefile-linux.mk linux-build
```
This will build the application to `<project directory>/builds/linux-build` which can be run using
```
export LD_LIBRARY_PATH="sfml-linux/lib" && builds/linux-build
```
