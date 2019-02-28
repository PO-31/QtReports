#!/bin/bash

cd "$TRAVIS_BUILD_DIR/qtreports-viewer"
qmake -spec ${USING_QT_MKSPEC} "CONFIG+=${BUILD_TYPE}" qtreports-viewer.pro
make -j$(nproc)
if [[ $? -ne 0 ]]; then
	exit 1
fi

cd "$TRAVIS_BUILD_DIR"
