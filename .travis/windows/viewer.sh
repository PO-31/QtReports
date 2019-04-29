#!/bin/bash

echo
echo "Building Viewer"

cd "$TRAVIS_BUILD_DIR/qtreports-viewer"

qmake -spec ${USING_QT_MKSPEC} "CONFIG+=${BUILD_TYPE}" qtreports-viewer.pro
mingw32-make -j$(nproc)
if [[ $? -ne 0 ]]; then
	echo
	echo "Building Viewer FAILED"
	exit 1
fi

echo
echo "Viewer has built"

cd "$TRAVIS_BUILD_DIR"
