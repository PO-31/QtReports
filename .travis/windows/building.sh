#!/bin/bash

cd "$TRAVIS_BUILD_DIR/qtreports"
qmake -spec ${USING_QT_MKSPEC} "CONFIG+=${BUILD_TYPE}" qtreports.pro
mingw32-make -j$(nproc)
if [[ $? -ne 0 ]]; then
	exit 1
fi
mingw32-make install

cd "$TRAVIS_BUILD_DIR"
