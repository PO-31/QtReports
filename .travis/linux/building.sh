#!/bin/bash

echo
echo "Building Library"

cd "$TRAVIS_BUILD_DIR/qtreports"
qmake -spec ${USING_QT_MKSPEC} "CONFIG+=${BUILD_TYPE}" qtreports.pro

make -j$(nproc)
if [[ $? -ne 0 ]]; then
	echo
	echo "Building Library FAILED"
	exit 1
fi

echo
echo "Library has been built"

sudo make install

cd "$TRAVIS_BUILD_DIR"