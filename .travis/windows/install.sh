#!/bin/bash

cd "$HOME"
./packages/7z.exe x ./packages/qtbase-build-win32.zip

# powershell
# Expand-Archive qtbase-build-win32.zip -DestinationPath ..\ -Force
# exit

export PATH="$HOME/qtbase-build/bin:$PATH"

ls "$HOME"

cd "$TRAVIS_BUILD_DIR"