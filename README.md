# Dungeon Crawler

This is a the repository for our turn and tile based dungeon crawler. The project is being made for Advanced Computer Science at LASA High School by Will Fisher, Zayan Vohra, Andy Mueller, Dodie Robison, and Nelson Barnes.

![Retro Chicken](rclogo.PNG)

# Building
### Linux ###
For linux systems you can build and run the program by executing
```
$ cd <project-directory>
$ ./run-linux.sh
```
To solely build the program simply execute
```
$ cd <project-directory>
$ make -f makefile.mk linux-build
```
This will build the application to `<project-directory>/builds/linux-build` which can be run using
```
$ export LD_LIBRARY_PATH="sfml/lib-linux" && builds/linux-build
```
*Note: For linux systems SFML's dependencies must first be installed. The easiest way to do this is to install SFML from the package manager to auto-install dependencies. On Ubuntu this is* `sudo apt-get install libsfml-dev`*.*

### Windows ###
For windows system you will need to install `MinGW` and make sure you have `g++` and `mingw32-make` installed. Upon doing this you can build and run the program by executing in cmd
```
$ cd <project-directory>
$ run-windows.bat
```
To solely build the program simply execute
```
$ cd <project-directory>
$ mingw32-make -f makefile.mk windows-build
```
This will build the application to `<project-directory>/builds/windows-build` which can be run using
```
$ start builds/windows-build
```
