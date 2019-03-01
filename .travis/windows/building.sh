#!/bin/bash

cd "$TRAVIS_BUILD_DIR/qtreports"
qmake -spec ${USING_QT_MKSPEC} "CONFIG+=${BUILD_TYPE}" qtreports.pro
"$HOME/mingw32/bin/mingw32-make.exe" -j$(nproc)
if [[ $? -ne 0 ]]; then
	exit 1
fi
mingw32-make install

cd "$TRAVIS_BUILD_DIR"
