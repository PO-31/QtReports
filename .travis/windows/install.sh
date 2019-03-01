#!/bin/bash

cd "$HOME"
./packages/7z.exe x ./packages/qtbase-build-win32.zip

if [[ $? -ne 0 ]]; then
	exit 1
fi

export PATH="$HOME/qtbase-build/bin:$PATH"

cd "$TRAVIS_BUILD_DIR"
