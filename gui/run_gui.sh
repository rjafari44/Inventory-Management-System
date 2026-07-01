#!/bin/bash

# GUI build script. Qt/CMake equivalent of the CLI run.sh
# this script lives in gui/, builds into gui/build, runs the program,
# then deletes gui/build afterward (even if you Ctrl+C out of it)

BUILD_DIR="build"
EXEC="InventoryGUI"

# capture the FULL absolute path to build/ BEFORE we cd into it --
# otherwise cleanup() runs later from inside build/, and "build"
# would point to a nonexistent build/build instead of build/ itself
BUILD_DIR_ABS="$(pwd)/$BUILD_DIR"

# cleanup function -- runs no matter how the script exits
# (normal exit, Ctrl+C, or kill signal)
cleanup() {
    echo
    echo "Cleaning up..."
    rm -rf "$BUILD_DIR_ABS"
}

# trap catches script exit (EXIT), Ctrl+C (INT), and termination (TERM)
# and runs cleanup() before the script actually closes
trap cleanup EXIT INT TERM

echo "Building..."
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit 1

cmake .. && cmake --build .

if [[ $? -eq 0 ]]; then
    echo "Build successful: ./$EXEC"
    echo
    ./$EXEC
else
    echo "Build failed!"
    exit 1
fi