#!/bin/bash

echo
echo "Building Library"

cd "$TRAVIS_BUILD_DIR/qtreports"
qmake -spec ${USING_QT_MKSPEC} "CONFIG+=${BUILD_TYPE}" qtreports.pro

if [ "$CC" = "gcc" ]; then
	mingw32-make.exe -j$(nproc)
fi

if [[ $? -ne 0 ]]; then
	echo
	echo "Building Library FAILED"
	exit 1
fi

echo
echo "Library has been built"

cd "$TRAVIS_BUILD_DIR"

