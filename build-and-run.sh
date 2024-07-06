#!/bin/bash

# Build raylib first
RAYLIB_SRC="./raylib/src"
export MACOSX_DEPLOYMENT_TARGET=10.9
cd "${RAYLIB_SRC}" || exit
make
cp libraylib.a ../../libraylib.a
cd ../../


MAIN_FILENAME=${1:-core_simple_window}
OUTDIR="./bin"

# Create output directory if it doesn't exist
if [ ! -d "$OUTDIR" ]; then
    mkdir "$OUTDIR"
fi

clang \
    -framework CoreVideo \
    -framework IOKit \
    -framework Cocoa \
    -framework GLUT \
    -framework OpenGL \
    -I"${RAYLIB_SRC}" \
    -Wall \
    libraylib.a "${MAIN_FILENAME}".c -o "${OUTDIR}"/"${MAIN_FILENAME}"

# Run the program
"$OUTDIR/$MAIN_FILENAME"
 
 
