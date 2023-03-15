# Getting Started with the MongoDB C Driver

Some simple examples using the [MongoDB C driver](https://www.mongodb.com/docs/drivers/c/)

## Build and run

These examples are built using GCC on macOS, but they should compile anywhere that has a C compiler

- clone this repo
- create a file called `URI.h` that contains your MongoDB Connection String, with this content:
```c
// URI.h
#define MY_MONGODB_URI "mongodb+srv://<your connection string, including user + password>" 
```

- Make the build script executable `chmod a+x build-all.sh`
- `./build-all.sh`

In macOS you need to install Xcode first (free on the Mac App Store)