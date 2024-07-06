# Vector Graphics Refresher

This project is intended to serve as a refresh for myself on vector graphics.

## Building and Running

Each example program is self-contained in a single C file. A shell script is included to build and run the examples on macOS:

```sh
# Syntax: ./build-and-run.sh <example file without .c extension>
./build-and-run.sh core_title_screen
```

These examples should also work fine on Windows and Linux, but you will need to build them manually for now. I will add build scripts for these platforms in the future.

## Dependencies

[Raylib](https://www.raylib.com/) is used for all graphics rendering. It is included in the project as 
a submodule. The build script will build raylib from source as needed for you.
