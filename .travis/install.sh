#!/bin/bash

cd /c/
"$HOME/packages/7z.exe" x "$HOME/packages/qtbase-build.7z"

if [[ $? -ne 0 ]]; then
	exit 1
fi

cd "$HOME"
"$HOME/packages/7z.exe" x "$HOME/packages/mingw-w64.7z"

export QTDIR="/c/qtbase-build"
export PATH="$QTDIR/bin:$HOME/mingw32/bin:$PATH"

cd "$TRAVIS_BUILD_DIR"
