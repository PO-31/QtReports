#!/bin/bash

cd "$HOME/packages"
powershell -Command "& {Expand-Archive qtbase-build-win32.zip -DestinationPath $HOME}"
if [[ $? -ne 0 ]]; then
	echo "Error in qtbase extraction"
	exit 1
fi

ls "$HOME/qtbase-build/"

export PATH=$HOME/qtbase-build/bin:$PATH

cd "$TRAVIS_BUILD_DIR"