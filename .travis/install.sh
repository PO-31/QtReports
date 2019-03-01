#!/bin/bash

cd /c/
"$HOME/packages/7z.exe" x "$HOME/packages/qtbase-build.7z"

if [[ $? -ne 0 ]]; then
	exit 1
fi

export QTDIR="/c/qtbase-build"
export PATH="$QTDIR/bin:$PATH"

cd "$TRAVIS_BUILD_DIR"
