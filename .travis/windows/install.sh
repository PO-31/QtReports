#!/bin/bash

cd "$HOME/packages"
powershell -Command {Expand-Archive qtbase-build-win32.zip -DestinationPath "$HOME" -Force} -Version 5.0

# powershell
# Expand-Archive qtbase-build-win32.zip -DestinationPath ..\ -Force
# exit

export PATH="$HOME/qtbase-build/bin:$PATH"

ls "$HOME"

cd "$TRAVIS_BUILD_DIR"