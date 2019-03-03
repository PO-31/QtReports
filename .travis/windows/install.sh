#!/bin/bash

cd /c/

if [ "$CC" = "gcc" ]; then
	7z x "$HOME/packages/qtbase-mingw.7z"
	if [[ $? -ne 0 ]]; then
		exit 1
	fi

	export QTDIR="/c/qtbase-mingw"
	export USING_QT_MKSPEC="win32-g++"
else
	echo "Detected using unsupported compiler"
	exit 1
fi

export PATH="$QTDIR/bin:$PATH"

cd "$TRAVIS_BUILD_DIR"