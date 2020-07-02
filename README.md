ModulerMadness
|__________________external          (External code, GoogleTest cmake)
|__________________include           (Header files to be included in src .cpp files)
|__________________scripts           (contain scripts to build and clean the project)
|__________________src               (source file containing .cpp files of the solution) 
|__________________test              (source files for unit testing)
|__________________CMakeLists.txt     (Parent CMakeLists.txt)

After building the project using the steps mentioned below, following additional directory "dist" will be created

ModuleMadness
    |
    |______dist
    |        |____________________bin  (relese/debug) (containe source and test binaries corresponding to build type)
    |        |____________________lib  (release/debug) (source library)
    |
    |________build (Contain Makefiles and other files created by cmake corresponding to folders with CMakeLists.txt)

Also the project can be configured and build in VS code.
The .vscode directory has tasks.json for build configs and launch.json for debugging 
(NOTE: Change compiler and debugger from clang/lldb to g++/gdb if required) 
    


## Requirements
``` bash
# Following tools need to be installed
>> cmake (3.5 or above)
>> clang or g++ compiler
```
## Build and Run
The script folder contains all the scripts that are needed to automatically build (and run) the project with cmake
``` bash
>> cd scripts

# Build project with specified build type (default=debug) and create executable to folder: dist/BUILD_TYPE
>> ./build.sh --build_type=release

# cd to executable and run it
>> cd ../dist/release
>> ./ModuleMadness

# Remove all generated folders (build and dist)
>> ./clean.sh 
```
# Build Tests and Run Unit Test
``` bash
>> cd scripts

# Build project with specified build tests ON (default=OFF)
>> ./build.sh --build_type=release --build_tests=ON

#cd to executable to run the tests
>> cd ../dist/bin/release
>> ./testModulerMadness
```
