#!/bin/bash

cd "$HOME"
./packages/7z* x ./packages/qtbase-build.7z

if [[ $? -ne 0 ]]; then
	exit 1
fi

export QTDIR="$HOME/qtbase-build"
export PATH="$QTDIR/bin:$PATH"

cd "$TRAVIS_BUILD_DIR"
