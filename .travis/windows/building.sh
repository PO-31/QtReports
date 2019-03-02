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
echo "Library has been built"


export REPORT_LIB="/c/qtreports"

mkdir "$REPORT_LIB"
cp ../build/lib/* "$REPORT_LIB"
export PATH="$REPORT_LIB:$PATH"
ls "$REPORT_LIB"

cd "$TRAVIS_BUILD_DIR"

