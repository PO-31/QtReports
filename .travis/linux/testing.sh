#!/bin/bash

echo
echo "Building and passing tests"

cd "$TRAVIS_BUILD_DIR/qtreports-tests"
qmake -spec ${USING_QT_MKSPEC} "CONFIG+=${BUILD_TYPE}" qtreports-tests.pro
make -j$(nproc)
if [[ $? -ne 0 ]]; then
	echo
	echo "Building tests program FAILED"
	exit 1
fi

echo
echo "Tests program has been built"

./qtreports-tests
if [[ $? -ne 0 ]]; then
	echo "Some of the tests FAILED"
	exit 1
fi
echo "Tests PASSED"

cd "$TRAVIS_BUILD_DIR"
