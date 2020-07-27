
```bash
ModulerMadness/
├── CMakeLists.txt
├── README.md
├── external
│   ├── CMakeLists.txt
│   └── gtest.cmake
├── include
│   ├── BaseOperation.h
│   ├── DelayOperation.h
│   ├── EchoOperation.h
│   ├── Module.h
│   ├── ModuleNetwork.h
│   ├── NoopOperation.h
│   └── ReverseOperation.h
├── scripts
│   ├── build.sh
│   └── clean.sh
├── src
│   ├── CMakeLists.txt
│   ├── DelayOperation.cpp
│   ├── EchoOperation.cpp
│   ├── Module.cpp
│   ├── ModuleNetwork.cpp
│   ├── NoopOperation.cpp
│   ├── ReverseOperation.cpp
│   └── main.cpp
└── test
    ├── CMakeLists.txt
    ├── main.cpp
    └── testSuit.cpp
   
```

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
