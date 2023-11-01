# Getting Started with the MongoDB C Driver

Some simple examples using the [MongoDB C driver](https://www.mongodb.com/docs/drivers/c/)

## Build and run

These examples are built using GCC on macOS, but they should compile anywhere that has a C compiler

- Clone this repo
- Edit the file called `URI.h` and add your [MongoDB Connection String](https://www.mongodb.com/basics/mongodb-connection-string) inside the quotes:
```c
// URI.h
#define MY_MONGODB_URI "mongodb+srv://<your connection string, including user + password>" 
```

- Make the build script executable `chmod a+x build-all.sh`
- `./build-all.sh`

### Build and run with CMake
We can also use CMake to build the programs in this repo. After editing the `URI.h`, run below commands in the directory:
 ```c
mkdir build
cd build
cmake ..
cmake --build .
 ```

In macOS you need to install Xcode first (free on the Mac App Store)