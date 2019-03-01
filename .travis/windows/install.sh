#!/bin/bash

source "$TRAVIS_BUILD_DIR/.travis/install.sh"

if [ "$CC" = "gcc" ]; then
	export USING_QT_MKSPEC="$QTDIR/mkspecs/win32-g++"
else
	echo "Detected using unsupported compiler"
	exit 1
fi
