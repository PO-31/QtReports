#!/bin/bash

echo
echo "Building Library"

cd "$TRAVIS_BUILD_DIR/qtreports"
qmake -spec ${USING_QT_MKSPEC} "CONFIG+=${BUILD_TYPE}" qtreports.pro

if [ "$CC" = "gcc" ]; then
	mingw32-make.exe -j$(nproc)
else
	echo "Detected using unsupported compiler"
	exit 1
fi

if [[ $? -ne 0 ]]; then
	echo
	echo "Building Library FAILED"
	exit 1
fi

echo
echo "Library has built"

cp ../build/lib/* ../../build/
export PATH="$TRAVIS_BUILD_DIR/../build:$PATH"

cd "$TRAVIS_BUILD_DIR"

